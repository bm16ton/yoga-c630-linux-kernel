#include <sys/socket.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "gpsd.h"
#include "libgps.h"

#if defined(PDS_ENABLE)
#include "driver_pds.h"

#include <linux/qrtr.h>

#define QMI_PDS_SERVICE_ID	0x10
#define QMI_PDS_VERSION		0x2

struct qmi_header {
	uint8_t type;
	uint16_t txn;
	uint16_t msg;
	uint16_t len;
} __attribute__((__packed__));

struct qmi_tlv {
	uint8_t key;
	uint16_t len;
	uint8_t value[];
} __attribute__((__packed__));

#define QMI_REQUEST			0
#define QMI_INDICATION			4

#define QMI_LOC_REG_EVENTS		0x21
#define QMI_TLV_EVENT_MASK		1
#define QMI_EVENT_MASK_NMEA		4

#define QMI_LOC_START			0x22
#define QMI_LOC_STOP			0x23
#define QMI_TLV_SESSION_ID		1

#define QMI_LOC_EVENT_NMEA		0x26
#define QMI_TLV_NMEA			1

static ssize_t qmi_pds_get(struct gps_device_t *session)
{
	struct sockaddr_qrtr sq;
	socklen_t sl = sizeof(sq);
	struct qmi_header *hdr;
	struct qmi_tlv *tlv;
	size_t buflen = sizeof(session->lexer.inbuffer);
	size_t offset;
	void *buf = session->lexer.inbuffer;
	int ret;

	ret = recvfrom(session->gpsdata.gps_fd, buf, buflen, 0,
		       (struct sockaddr *)&sq, &sl);
	if (ret < 0 && errno == EAGAIN) {
		session->lexer.outbuflen = 0;
		return 1;
	} else if (ret < 0) {
		gpsd_log(&session->context->errout, LOG_ERROR,
			 "QRTR get: Unable to receive packet.\n");
		return -1;
	}

	/* TODO: Validate sq to be our peer */

	session->lexer.type = QMI_PDS_PACKET;

	hdr = buf;
	if (hdr->type != QMI_INDICATION ||
	    hdr->msg != QMI_LOC_EVENT_NMEA) {
		session->lexer.outbuflen = 0;
		return ret;
	}

	offset = sizeof(*hdr);
	while (offset < (size_t)ret) {
		tlv = (struct qmi_tlv *)((char*)buf + offset);

		if (offset + sizeof(*tlv) + tlv->len > (size_t)ret)
			break;

		if (tlv->key == QMI_TLV_NMEA) {
			memcpy(session->lexer.outbuffer, tlv->value, tlv->len);
			session->lexer.outbuffer[tlv->len] = 0;
			session->lexer.outbuflen = tlv->len;
			break;
		}

		offset += tlv->len;
	}

	return ret;
}

static gps_mask_t qmi_pds_parse_input(struct gps_device_t *session)
{
	return nmea_parse((char *)session->lexer.outbuffer, session);
}

static void qmi_pds_event_hook(struct gps_device_t *session, event_t event)
{
	struct qmi_header *hdr;
	struct qmi_tlv *tlv;
	static int txn_id;
	char buf[128];
	char *ptr;
	int sock = session->gpsdata.gps_fd;
	int ret;

	switch (event) {
	case event_deactivate:
		ptr = buf;
		hdr = (struct qmi_header *)ptr;
		hdr->type = QMI_REQUEST;
		hdr->txn = txn_id++;
		hdr->msg = QMI_LOC_STOP;
		hdr->len = sizeof(*tlv) + sizeof(uint8_t);
		ptr += sizeof(*hdr);

		tlv = (struct qmi_tlv *)ptr;
		tlv->key = QMI_TLV_SESSION_ID;
		tlv->len = sizeof(uint8_t);
		*(uint8_t*)tlv->value = 1;
		ptr += sizeof(*tlv) + sizeof(uint8_t);

		ret = send(sock, buf, ptr - buf, 0);
		if (ret < 0) {
			gpsd_log(&session->context->errout, LOG_ERROR,
				 "QRTR event_hook: failed to send STOP request.\n");
			return;
		}
		break;
	case event_reactivate:
		ptr = buf;
		hdr = (struct qmi_header *)ptr;
		hdr->type = QMI_REQUEST;
		hdr->txn = txn_id++;
		hdr->msg = QMI_LOC_REG_EVENTS;
		hdr->len = sizeof(*tlv) + sizeof(uint64_t);
		ptr += sizeof(*hdr);

		tlv = (struct qmi_tlv *)ptr;
		tlv->key = QMI_TLV_EVENT_MASK;
		tlv->len = sizeof(uint64_t);
		*(uint64_t*)tlv->value = QMI_EVENT_MASK_NMEA;
		ptr += sizeof(*tlv) + sizeof(uint64_t);

		ret = send(sock, buf, ptr - buf, 0);
		if (ret < 0) {
			gpsd_log(&session->context->errout, LOG_ERROR,
				 "QRTR event_hook: failed to send REG_EVENTS request.\n");
			return;
		}

		ptr = buf;
		hdr = (struct qmi_header *)ptr;
		hdr->type = QMI_REQUEST;
		hdr->txn = txn_id++;
		hdr->msg = QMI_LOC_START;
		hdr->len = sizeof(*tlv) + sizeof(uint8_t);
		ptr += sizeof(*hdr);

		tlv = (struct qmi_tlv *)(buf + sizeof(*hdr));
		tlv->key = QMI_TLV_SESSION_ID;
		tlv->len = sizeof(uint8_t);
		*(uint8_t*)tlv->value = 1;
		ptr += sizeof(*tlv) + sizeof(uint8_t);

		ret = send(sock, buf, ptr - buf, 0);
		if (ret < 0) {
			gpsd_log(&session->context->errout, LOG_ERROR,
				 "QRTR event_hook: failed to send START request.\n");
			return;
		}
		break;
	default:
		break;
	}
}

int qmi_pds_open(struct gps_device_t *session)
{
	struct sockaddr_qrtr sq_ctrl;
	struct qrtr_ctrl_pkt pkt;
	struct sockaddr_qrtr sq;
	unsigned int pds_node = 0;
	unsigned int pds_port = 0;
	socklen_t sl = sizeof(sq_ctrl);
	char *hostname;
	char *endptr;
	int hostid;
	int flags;
	int sock;
	int ret;

	hostname = session->gpsdata.dev.path + 6;
	if (!strcmp(hostname, "any")) {
		hostid = -1;
	} else {
		hostid = (int)strtol(hostname, &endptr, 10);
		if (endptr == hostname) {
			gpsd_log(&session->context->errout, LOG_ERROR,
				 "QRTR open: Invalid node id.\n");
			return -1;
		}
	}


	sock = socket(AF_QIPCRTR, SOCK_DGRAM, 0);
	if (sock < 0) {
	        gpsd_log(&session->context->errout, LOG_ERROR,
			 "QRTR open: Unable to get QRTR socket.\n");
		return -1;
	}

	ret = getsockname(sock, (struct sockaddr *)&sq_ctrl, &sl);
	if (ret < 0 || sq_ctrl.sq_family != AF_QIPCRTR || sl != sizeof(sq_ctrl)) {
	        gpsd_log(&session->context->errout, LOG_ERROR,
			 "QRTR open: Unable to acquire local address.\n");
		close(sock);
		return -1;
	}

	memset(&pkt, 0, sizeof(pkt));
	pkt.cmd = QRTR_TYPE_NEW_LOOKUP;
	pkt.server.service = QMI_PDS_SERVICE_ID;
	pkt.server.instance = QMI_PDS_VERSION;

	sq_ctrl.sq_port = QRTR_PORT_CTRL;
	ret = sendto(sock, &pkt, sizeof(pkt), 0, (struct sockaddr *)&sq_ctrl, sizeof(sq_ctrl));
	if (ret < 0) {
	        gpsd_log(&session->context->errout, LOG_ERROR,
			 "QRTR open: Unable to send lookup request.\n");
		close(sock);
		return -1;
	}

	for (;;) {
		sl = sizeof(sq);

		ret = recvfrom(sock, &pkt, sizeof(pkt), 0, (struct sockaddr *)&sq, &sl);
		if (ret < 0) {
			gpsd_log(&session->context->errout, LOG_ERROR,
				 "QRTR open: Unable to receive lookup request.\n");
			close(sock);
			return -1;
		}

		if (sl != sizeof(sq) || sq.sq_node != sq_ctrl.sq_node ||
		    sq.sq_port != sq_ctrl.sq_port) {
			gpsd_log(&session->context->errout, LOG_ERROR,
				 "QRTR open: Received message is not ctrl message, ignoring.\n");
			continue;
		}

		if (pkt.cmd != QRTR_TYPE_NEW_SERVER)
			continue;

		/* All fields zero indicates end of lookup response */
		if (!pkt.server.service && !pkt.server.instance &&
		    !pkt.server.node && !pkt.server.port)
			break;

		/* Filter results based on specified node */
		if (hostid != -1 && hostid != (int)pkt.server.node)
			continue;

		pds_node = pkt.server.node;
		pds_port = pkt.server.port;
	}

	if (!pds_node && !pds_port) {
		gpsd_log(&session->context->errout, LOG_ERROR,
			 "QRTR open: No PDS service found.\n");
		close(sock);
		return -1;
	}

	flags = fcntl(sock, F_GETFL, 0);
	flags |= O_NONBLOCK;
	fcntl(sock, F_SETFL, flags);

	gpsd_log(&session->context->errout, LOG_INF,
		 "QRTR open: Found PDS at %d %d.\n", pds_node, pds_port);

	sq.sq_family = AF_QIPCRTR;
	sq.sq_node = pds_node;
	sq.sq_port = pds_port;
	ret = connect(sock, (struct sockaddr *)&sq, sizeof(sq));
	if (ret < 0) {
		gpsd_log(&session->context->errout, LOG_ERROR,
			 "QRTR open: Failed to connect socket.\n");
		close(sock);
		return -1;
	}

	gpsd_switch_driver(session, "Qualcomm PDS");
	session->gpsdata.gps_fd = sock;
	session->sourcetype = source_qrtr;
	session->servicetype = service_sensor;

	return session->gpsdata.gps_fd;
}

void qmi_pds_close(struct gps_device_t *session)
{
	if (!BAD_SOCKET(session->gpsdata.gps_fd)) {
		close(session->gpsdata.gps_fd);
		INVALIDATE_SOCKET(session->gpsdata.gps_fd);
	}
}

const struct gps_type_t driver_pds = {
    .type_name      = "Qualcomm PDS",       /* full name of type */
    .packet_type    = QMI_PDS_PACKET,	/* associated lexer packet type */
    .flags	    = DRIVER_STICKY,	/* remember this */
    .channels       = 12,		/* not an actual GPS at all */
    .get_packet     = qmi_pds_get,	/* how to get a packet */
    .parse_packet   = qmi_pds_parse_input,	/* how to interpret a packet */
    .event_hook	    = qmi_pds_event_hook,
};

#endif /* of defined(PDS_ENABLE) */
