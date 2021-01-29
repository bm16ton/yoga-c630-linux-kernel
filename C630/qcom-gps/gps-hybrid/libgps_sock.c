/* libgps_sock.c -- client interface library for the gpsd daemon
 *
 * This file is Copyright (c) 2010 by the GPSD project
 * SPDX-License-Identifier: BSD-2-clause
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <locale.h>
#include <assert.h>
#include <sys/time.h>	 /* expected to have a select(2) prototype a la SuS */
#include <sys/types.h>
#include <sys/stat.h>
#include "gpsd_config.h"
#ifdef HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif /* HAVE_SYS_SELECT_H */
#include <unistd.h>

#ifndef USE_QT
#ifdef HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif /* HAVE_SYS_SOCKET_H */
#ifdef HAVE_WINSOCK2_H
#include <winsock2.h>
#endif /* HAVE_WINSOCK2_H */
#else
#include <QTcpSocket>
#endif /* USE_QT */

#include "gps.h"
#include "gpsd.h"
#include "libgps.h"
#include "strfuncs.h"
#ifdef SOCKET_EXPORT_ENABLE
#include "gps_json.h"

struct privdata_t
{
    bool newstyle;
    /* data buffered from the last read */
    ssize_t waiting;
    char buffer[GPS_JSON_RESPONSE_MAX * 2];
#ifdef LIBGPS_DEBUG
    int waitcount;
#endif /* LIBGPS_DEBUG */
};

#ifdef HAVE_WINSOCK2_H
static bool need_init = TRUE;
static bool need_finish = TRUE;

static bool windows_init(void)
/* Ensure socket networking is initialized for Windows. */
{
    WSADATA wsadata;
    /* request access to Windows Sockets API version 2.2 */
    int res = WSAStartup(MAKEWORD(2, 2), &wsadata);
    if (res != 0) {
      libgps_debug_trace((DEBUG_CALLS, "WSAStartup returns error %d\n", res));
    }
    return (res == 0);
}

static bool windows_finish(void)
/* Shutdown Windows Sockets. */
{
  int res = WSACleanup();
  if (res != 0) {
    libgps_debug_trace((DEBUG_CALLS, "WSACleanup returns error %d\n", res));
  }
  return (res == 0);
}
#endif /* HAVE_WINSOCK2_H */

int gps_sock_open(const char *host, const char *port,
		  struct gps_data_t *gpsdata)
{
    if (!host)
	host = "localhost";
    if (!port)
	port = DEFAULT_GPSD_PORT;

    libgps_debug_trace((DEBUG_CALLS, "gps_sock_open(%s, %s)\n", host, port));

#ifndef USE_QT
#ifdef HAVE_WINSOCK2_H
	if (need_init) {
	  need_init != windows_init();
	}
#endif
	if ((gpsdata->gps_fd =
	    netlib_connectsock(AF_UNSPEC, host, port, "tcp")) < 0) {
	    errno = gpsdata->gps_fd;
	    libgps_debug_trace((DEBUG_CALLS, "netlib_connectsock() returns error %d\n", errno));
	    return -1;
        }
	else
	    libgps_debug_trace((DEBUG_CALLS, "netlib_connectsock() returns socket on fd %d\n", gpsdata->gps_fd));
#else /* HAVE_WINSOCK2_H */
	QTcpSocket *sock = new QTcpSocket();
	gpsdata->gps_fd = sock;
	sock->connectToHost(host, QString(port).toInt());
	if (!sock->waitForConnected())
	    qDebug() << "libgps::connect error: " << sock->errorString();
	else
	    qDebug() << "libgps::connected!";
#endif /* USE_QT */

    /* set up for line-buffered I/O over the daemon socket */
    gpsdata->privdata = (void *)malloc(sizeof(struct privdata_t));
    if (gpsdata->privdata == NULL)
	return -1;
    PRIVATE(gpsdata)->newstyle = false;
    PRIVATE(gpsdata)->waiting = 0;
    PRIVATE(gpsdata)->buffer[0] = 0;

#ifdef LIBGPS_DEBUG
    PRIVATE(gpsdata)->waitcount = 0;
#endif /* LIBGPS_DEBUG */
    return 0;
}

bool gps_sock_waiting(const struct gps_data_t *gpsdata, int timeout)
/* is there input waiting from the GPS? */
/* timeout is in uSec */
{
#ifndef USE_QT
    fd_set rfds;
    struct timeval tv;

    libgps_debug_trace((DEBUG_CALLS, "gps_waiting(%d): %d\n", timeout, PRIVATE(gpsdata)->waitcount++));
    if (PRIVATE(gpsdata)->waiting > 0)
	return true;

    /* we might want to check for EINTR if this returns false */
    errno = 0;

    FD_ZERO(&rfds);
    FD_SET(gpsdata->gps_fd, &rfds);
    tv.tv_sec = timeout / 1000000;
    tv.tv_usec = timeout % 1000000;
    /* all error conditions return "not waiting" -- crude but effective */
    return (select(gpsdata->gps_fd + 1, &rfds, NULL, NULL, &tv) == 1);
#else
    return ((QTcpSocket *) (gpsdata->gps_fd))->waitForReadyRead(timeout / 1000);
#endif
}

int gps_sock_close(struct gps_data_t *gpsdata)
/* close a gpsd connection */
{
    free(PRIVATE(gpsdata));
    gpsdata->privdata = NULL;
#ifndef USE_QT
    int status;
#ifdef HAVE_WINSOCK2_H
    status = closesocket(gpsdata->gps_fd);
    if (need_finish) {
      need_finish != windows_finish();
    }
#else
    status = close(gpsdata->gps_fd);
#endif /* HAVE_WINSOCK2_H */
    gpsdata->gps_fd = -1;
    return status;
#else
    QTcpSocket *sock = (QTcpSocket *) gpsdata->gps_fd;
    sock->disconnectFromHost();
    delete sock;
    gpsdata->gps_fd = NULL;
    return 0;
#endif
}

int gps_sock_read(struct gps_data_t *gpsdata)
/* wait for and read data being streamed from the daemon */
{
    char *eol;
    ssize_t response_length;
    int status = -1;

    gpsdata->set &= ~PACKET_SET;
    for (eol = PRIVATE(gpsdata)->buffer;
	 *eol != '\n' && eol < PRIVATE(gpsdata)->buffer + PRIVATE(gpsdata)->waiting; eol++)
	continue;
    if (*eol != '\n')
	eol = NULL;

    errno = 0;

    if (eol == NULL) {
#ifndef USE_QT
	/* read data: return -1 if no data waiting or buffered, 0 otherwise */
	status = (int)recv(gpsdata->gps_fd,
			   PRIVATE(gpsdata)->buffer + PRIVATE(gpsdata)->waiting,
			   sizeof(PRIVATE(gpsdata)->buffer) - PRIVATE(gpsdata)->waiting, 0);
#else
	status =
	    ((QTcpSocket *) (gpsdata->gps_fd))->read(PRIVATE(gpsdata)->buffer +
						     PRIVATE(gpsdata)->waiting,
						     sizeof(PRIVATE(gpsdata)->buffer) -
						     PRIVATE(gpsdata)->waiting);
#endif
#ifdef HAVE_WINSOCK2_H
	int wserr = WSAGetLastError();
#endif /* HAVE_WINSOCK2_H */
	/* if we just received data from the socket, it's in the buffer */
	if (status > -1)
	    PRIVATE(gpsdata)->waiting += status;
	/* buffer is empty - implies no data was read */
	if (PRIVATE(gpsdata)->waiting == 0) {
	    /*
	     * If we received 0 bytes, other side of socket is closing.
	     * Return -1 as end-of-data indication.
	     */
	    // cppcheck-suppress duplicateBranch
	    if (status == 0)
		return -1;
#ifndef USE_QT
	    /* count transient errors as success, we'll retry later */
#ifdef HAVE_WINSOCK2_H
	    else if (wserr == WSAEINTR || wserr == WSAEWOULDBLOCK)
		return 0;
#else
	    else if (errno == EINTR || errno == EAGAIN
		     || errno == EWOULDBLOCK)
		return 0;
#endif /* HAVE_WINSOCK2_H */
#endif
	    /* hard error return of -1, pass it along */
	    else
		return -1;
	}
	/* there's buffered data waiting to be returned */
	for (eol = PRIVATE(gpsdata)->buffer;
	     *eol != '\n' && eol < PRIVATE(gpsdata)->buffer + PRIVATE(gpsdata)->waiting; eol++)
	    continue;
	if (*eol != '\n')
	    eol = NULL;
	if (eol == NULL)
	    return 0;
    }

    assert(eol != NULL);
    *eol = '\0';
    response_length = eol - PRIVATE(gpsdata)->buffer + 1;
    gpsdata->online = timestamp();
    status = gps_unpack(PRIVATE(gpsdata)->buffer, gpsdata);
    memmove(PRIVATE(gpsdata)->buffer,
	    PRIVATE(gpsdata)->buffer + response_length, PRIVATE(gpsdata)->waiting - response_length);
    PRIVATE(gpsdata)->waiting -= response_length;
    gpsdata->set |= PACKET_SET;

    return (status == 0) ? (int)response_length : status;
}

int gps_unpack(char *buf, struct gps_data_t *gpsdata)
/* unpack a gpsd response into a status structure, buf must be writeable.
 * gps_unpack() currently returns 0 in all cases, but should it ever need to
 * return an error status, it must be < 0.
 */
{
    libgps_debug_trace((DEBUG_CALLS, "gps_unpack(%s)\n", buf));

    /* detect and process a JSON response */
    if (buf[0] == '{') {
	const char *jp = buf, **next = &jp;
	while (next != NULL && *next != NULL && next[0][0] != '\0') {
	    libgps_debug_trace((DEBUG_CALLS,"gps_unpack() segment parse '%s'\n", *next));
	    if (libgps_json_unpack(*next, gpsdata, next) == -1)
		break;
#ifdef LIBGPS_DEBUG
	    if (libgps_debuglevel >= 1)
		libgps_dump_state(gpsdata);
#endif /* LIBGPS_DEBUG */

	}
    }

#ifndef USE_QT
    libgps_debug_trace((DEBUG_CALLS, "final flags: (0x%04x) %s\n", gpsdata->set,gps_maskdump(gpsdata->set)));
#endif
    return 0;
}

const char *gps_sock_data(const struct gps_data_t *gpsdata)
/* return the contents of the client data buffer */
{
    return PRIVATE(gpsdata)->buffer;
}

int gps_sock_send(struct gps_data_t *gpsdata, const char *buf)
/* send a command to the gpsd instance */
{
#ifndef USE_QT
#ifdef HAVE_WINSOCK2_H
    if (send(gpsdata->gps_fd, buf, strlen(buf), 0) == (ssize_t) strlen(buf))
#else
    if (write(gpsdata->gps_fd, buf, strlen(buf)) == (ssize_t) strlen(buf))
#endif /* HAVE_WINSOCK2_H */
	return 0;
    else
	return -1;
#else
    QTcpSocket *sock = (QTcpSocket *) gpsdata->gps_fd;
    sock->write(buf, strlen(buf));
    if (sock->waitForBytesWritten())
	return 0;
    else {
	qDebug() << "libgps::send error: " << sock->errorString();
	return -1;
    }
#endif
}

int gps_sock_stream(struct gps_data_t *gpsdata, unsigned int flags, void *d)
/* ask gpsd to stream reports at you, hiding the command details */
{
    char buf[GPS_JSON_COMMAND_MAX];

    if ((flags & (WATCH_JSON | WATCH_NMEA | WATCH_RAW)) == 0) {
	flags |= WATCH_JSON;
    }
    if ((flags & WATCH_DISABLE) != 0) {
	(void)strlcpy(buf, "?WATCH={\"enable\":false,", sizeof(buf));
	if (flags & WATCH_JSON)
	    (void)strlcat(buf, "\"json\":false,", sizeof(buf));
	if (flags & WATCH_NMEA)
	    (void)strlcat(buf, "\"nmea\":false,", sizeof(buf));
	if (flags & WATCH_RAW)
	    (void)strlcat(buf, "\"raw\":1,", sizeof(buf));
	if (flags & WATCH_RARE)
	    (void)strlcat(buf, "\"raw\":0,", sizeof(buf));
	if (flags & WATCH_SCALED)
	    (void)strlcat(buf, "\"scaled\":false,", sizeof(buf));
	if (flags & WATCH_TIMING)
	    (void)strlcat(buf, "\"timing\":false,", sizeof(buf));
	if (flags & WATCH_SPLIT24)
	    (void)strlcat(buf, "\"split24\":false,", sizeof(buf));
	if (flags & WATCH_PPS)
	    (void)strlcat(buf, "\"pps\":false,", sizeof(buf));
	str_rstrip_char(buf, ',');
	(void)strlcat(buf, "};", sizeof(buf));
	libgps_debug_trace((DEBUG_CALLS, "gps_stream() disable command: %s\n", buf));
	return gps_send(gpsdata, buf);
    } else {			/* if ((flags & WATCH_ENABLE) != 0) */
	(void)strlcpy(buf, "?WATCH={\"enable\":true,", sizeof(buf));
	if (flags & WATCH_JSON)
	    (void)strlcat(buf, "\"json\":true,", sizeof(buf));
	if (flags & WATCH_NMEA)
	    (void)strlcat(buf, "\"nmea\":true,", sizeof(buf));
	if (flags & WATCH_RARE)
	    (void)strlcat(buf, "\"raw\":1,", sizeof(buf));
	if (flags & WATCH_RAW)
	    (void)strlcat(buf, "\"raw\":2,", sizeof(buf));
	if (flags & WATCH_SCALED)
	    (void)strlcat(buf, "\"scaled\":true,", sizeof(buf));
	if (flags & WATCH_TIMING)
	    (void)strlcat(buf, "\"timing\":true,", sizeof(buf));
	if (flags & WATCH_SPLIT24)
	    (void)strlcat(buf, "\"split24\":true,", sizeof(buf));
	if (flags & WATCH_PPS)
	    (void)strlcat(buf, "\"pps\":true,", sizeof(buf));
	if (flags & WATCH_DEVICE)
	    str_appendf(buf, sizeof(buf), "\"device\":\"%s\",", (char *)d);
	str_rstrip_char(buf, ',');
	(void)strlcat(buf, "};", sizeof(buf));
	libgps_debug_trace((DEBUG_CALLS, "gps_stream() enable command: %s\n", buf));
	return gps_send(gpsdata, buf);
    }
}

int gps_sock_mainloop(struct gps_data_t *gpsdata, int timeout,
			 void (*hook)(struct gps_data_t *gpsdata))
/* run a socket main loop with a specified handler */
{
    for (;;) {
	if (!gps_waiting(gpsdata, timeout)) {
	    return -1;
	} else {
	    int status = gps_read(gpsdata);

	    if (status == -1)
		return -1;
	    if (status > 0)
		(*hook)(gpsdata);
	}
    }
    //return 0;
}

#endif /* SOCKET_EXPORT_ENABLE */

/* end */
