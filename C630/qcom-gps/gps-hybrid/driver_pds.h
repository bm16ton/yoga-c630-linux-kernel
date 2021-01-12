/*
 * PDS on QRTR.
 *
 * The entry points for driver_pds
 *
 * This file is Copyright (c) 2018 by the GPSD project
 * SPDX-License-Identifier: BSD-2-clause
 */

#ifndef _DRIVER_PDS_H_
#define _DRIVER_PDS_H_

#if defined(PDS_ENABLE)

int qmi_pds_open(struct gps_device_t *session);

void qmi_pds_close(struct gps_device_t *session);

#endif /* of defined(PDS_ENABLE) */
#endif /* of ifndef _DRIVER_PDS_H_ */
