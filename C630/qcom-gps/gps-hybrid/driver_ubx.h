/*
 * This file is Copyright (c) 2010 by the GPSD project
 * BSD terms apply: see the file COPYING in the distribution root for details
 */
#ifndef _GPSD_UBX_H_
#define _GPSD_UBX_H_

#define UBX_MESSAGE_BASE_SIZE 6
#define UBX_MESSAGE_DATA_OFFSET UBX_MESSAGE_BASE_SIZE

typedef enum {
    UBX_CLASS_NAV = 0x01,     /**< Navigation */
    UBX_CLASS_RXM = 0x02,     /**< Receiver Manager */
    UBX_CLASS_INF = 0x04,     /**< Informative text messages */
    UBX_CLASS_ACK = 0x05,     /**< (Not) Acknowledges for cfg messages */
    UBX_CLASS_CFG = 0x06,     /**< Configuration requests */
    UBX_CLASS_UPD = 0x09,     /**< Firmware updates */
    UBX_CLASS_MON = 0x0a,     /**< System monitoring */
    UBX_CLASS_AID = 0x0b,     /**< AGPS */
    UBX_CLASS_TIM = 0x0d,     /**< Time */
} ubx_classes_t;

#define UBX_MSGID(cls_, id_) (((cls_)<<8)|(id_))

typedef enum {
    UBX_NAV_POSECEF	= UBX_MSGID(UBX_CLASS_NAV, 0x01),
    UBX_NAV_POSLLH	= UBX_MSGID(UBX_CLASS_NAV, 0x02),
    UBX_NAV_STATUS	= UBX_MSGID(UBX_CLASS_NAV, 0x03),
    UBX_NAV_DOP		= UBX_MSGID(UBX_CLASS_NAV, 0x04),
    UBX_NAV_SOL		= UBX_MSGID(UBX_CLASS_NAV, 0x06),
    UBX_NAV_PVT	        = UBX_MSGID(UBX_CLASS_NAV, 0x07),
    UBX_NAV_POSUTM	= UBX_MSGID(UBX_CLASS_NAV, 0x08),
    UBX_NAV_VELECEF	= UBX_MSGID(UBX_CLASS_NAV, 0x11),
    UBX_NAV_VELNED	= UBX_MSGID(UBX_CLASS_NAV, 0x12),
    UBX_NAV_TIMEGPS	= UBX_MSGID(UBX_CLASS_NAV, 0x20),
    UBX_NAV_TIMEUTC	= UBX_MSGID(UBX_CLASS_NAV, 0x21),
    UBX_NAV_CLOCK	= UBX_MSGID(UBX_CLASS_NAV, 0x22),
    UBX_NAV_SVINFO	= UBX_MSGID(UBX_CLASS_NAV, 0x30),
    UBX_NAV_DGPS	= UBX_MSGID(UBX_CLASS_NAV, 0x31),
    UBX_NAV_SBAS	= UBX_MSGID(UBX_CLASS_NAV, 0x32),
    UBX_NAV_EKFSTATUS	= UBX_MSGID(UBX_CLASS_NAV, 0x40),

    UBX_RXM_RAW		= UBX_MSGID(UBX_CLASS_RXM, 0x10),
    UBX_RXM_SFRB	= UBX_MSGID(UBX_CLASS_RXM, 0x11),
    UBX_RXM_SVSI	= UBX_MSGID(UBX_CLASS_RXM, 0x20),
    UBX_RXM_ALM		= UBX_MSGID(UBX_CLASS_RXM, 0x30),
    UBX_RXM_EPH		= UBX_MSGID(UBX_CLASS_RXM, 0x31),
    UBX_RXM_POSREQ	= UBX_MSGID(UBX_CLASS_RXM, 0x40),

    UBX_INF_ERROR	= UBX_MSGID(UBX_CLASS_INF, 0X00),
    UBX_INF_WARNING	= UBX_MSGID(UBX_CLASS_INF, 0X01),
    UBX_INF_NOTICE	= UBX_MSGID(UBX_CLASS_INF, 0x02),
    UBX_INF_TEST	= UBX_MSGID(UBX_CLASS_INF, 0x03),
    UBX_INF_DEBUG	= UBX_MSGID(UBX_CLASS_INF, 0x04),
    UBX_INF_USER	= UBX_MSGID(UBX_CLASS_INF, 0x07),

    UBX_ACK_NAK		= UBX_MSGID(UBX_CLASS_ACK, 0x00),
    UBX_ACK_ACK		= UBX_MSGID(UBX_CLASS_ACK, 0x01),

    UBX_CFG_PRT		= UBX_MSGID(UBX_CLASS_CFG, 0x00),

    UBX_UPD_DOWNL	= UBX_MSGID(UBX_CLASS_UPD, 0x01),
    UBX_UPD_UPLOAD	= UBX_MSGID(UBX_CLASS_UPD, 0x02),
    UBX_UPD_EXEC	= UBX_MSGID(UBX_CLASS_UPD, 0x03),
    UBX_UPD_MEMCPY	= UBX_MSGID(UBX_CLASS_UPD, 0x04),

    UBX_MON_SCHED	= UBX_MSGID(UBX_CLASS_MON, 0x01),
    UBX_MON_IO		= UBX_MSGID(UBX_CLASS_MON, 0x02),
    UBX_MON_IPC		= UBX_MSGID(UBX_CLASS_MON, 0x03),
    UBX_MON_VER		= UBX_MSGID(UBX_CLASS_MON, 0x04),
    UBX_MON_EXCEPT	= UBX_MSGID(UBX_CLASS_MON, 0x05),
    UBX_MON_MSGPP	= UBX_MSGID(UBX_CLASS_MON, 0x06),
    UBX_MON_RXBUF	= UBX_MSGID(UBX_CLASS_MON, 0x07),
    UBX_MON_TXBUF	= UBX_MSGID(UBX_CLASS_MON, 0x08),
    UBX_MON_HW		= UBX_MSGID(UBX_CLASS_MON, 0x09),
    UBX_MON_USB		= UBX_MSGID(UBX_CLASS_MON, 0x0a),

    UBX_AID_REQ		= UBX_MSGID(UBX_CLASS_AID, 0x00),
    UBX_AID_INI		= UBX_MSGID(UBX_CLASS_AID, 0x01),
    UBX_AID_HUI		= UBX_MSGID(UBX_CLASS_AID, 0x02),
    UBX_AID_DATA	= UBX_MSGID(UBX_CLASS_AID, 0x10),
    UBX_AID_ALM		= UBX_MSGID(UBX_CLASS_AID, 0x30),
    UBX_AID_EPH		= UBX_MSGID(UBX_CLASS_AID, 0x31),

    UBX_TIM_TP		= UBX_MSGID(UBX_CLASS_TIM, 0x01),
    UBX_TIM_TM		= UBX_MSGID(UBX_CLASS_TIM, 0x02),
    UBX_TIM_TM2		= UBX_MSGID(UBX_CLASS_TIM, 0x03),
    UBX_TIM_SVIN	= UBX_MSGID(UBX_CLASS_TIM, 0x04),
} ubx_message_t;

typedef enum {
    UBX_MODE_NOFIX  = 0x00,	/* no fix available */
    UBX_MODE_DR	    = 0x01,	/* Dead reckoning */
    UBX_MODE_2D	    = 0x02,	/* 2D fix */
    UBX_MODE_3D	    = 0x03,	/* 3D fix */
    UBX_MODE_GPSDR  = 0x04,	/* GPS + dead reckoning */
    UBX_MODE_TMONLY = 0x05,	/* Time-only fix */
} ubx_mode_t;

#define UBX_SOL_FLAG_GPS_FIX_OK 0x01
#define UBX_SOL_FLAG_DGPS 0x02
#define UBX_SOL_VALID_WEEK 0x04
#define UBX_SOL_VALID_TIME 0x08

#define UBX_TIMEGPS_VALID_TIME        0x01
#define UBX_TIMEGPS_VALID_WEEK        0x02
#define UBX_TIMEGPS_VALID_LEAP_SECOND 0x04

/* from UBX_NAV_SVINFO */
#define UBX_SAT_USED 0x01
#define UBX_SAT_DGPS 0x02
#define UBX_SAT_EPHALM 0x04
#define UBX_SAT_EPHEM 0x08
#define UBX_SAT_UNHEALTHY 0x10

#define UBX_SIG_IDLE 0
#define UBX_SIG_SRCH1 1
#define UBX_SIG_SRCH2 2
#define UBX_SIG_DETECT 3
#define UBX_SIG_CDLK 4
#define UBX_SIG_CDCRLK1 5
#define UBX_SIG_CDCRLK2 6
#define UBX_SIG_NAVMSG 7

#define UBX_NAV_PVT_VALID_DATE      0x01
#define UBX_NAV_PVT_VALID_TIME      0x02
#define UBX_NAV_PVT_VALID_DATE_TIME (UBX_NAV_PVT_VALID_DATE | UBX_NAV_PVT_VALID_TIME)

#define UBX_NAV_PVT_FLAG_GPS_FIX_OK 0x01
#define UBX_NAV_PVT_FLAG_DGPS       0x02

#endif /* _GPSD_UBX_H_ */
