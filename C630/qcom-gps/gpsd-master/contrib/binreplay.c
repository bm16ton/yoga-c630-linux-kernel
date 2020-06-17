/*
 * Stuff the contents of a specified file into a specified tty.
 *
 * This file is Copyright (c) 2010-2018 by the GPSD project
 * SPDX-License-Identifier: BSD-2-clause
 */
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>  /* For nanosleep() */
#include <unistd.h>
#ifndef __GLIBC__
  #include <util.h>
#else
  #include <pty.h>
#endif


#define WRLEN 64
void spinner(int);
void usage(void);

int main( int argc, char **argv){
	struct stat sb;
	struct termios term;
	char *buf, tn[32];
	int ifd, ofd, sfd;
	int dflag = 0, c, sleeptime, len, speed = 0;
	struct timespec delay;

	while((c = getopt(argc, argv, "d:r:s:")) != -1) {
		switch(c){
		case 'd':
			dflag = 1;
			strncpy(tn, optarg, sizeof(tn)-1);
			break;
		case 's':
			speed = atoi(optarg);
			switch (speed) {
			case 230400:
			case 115200:
			case 57600:
			case 38400:
			case 28800:
			case 19200:
			case 14400:
			case 9600:
			case 4800:
				break;
			default:
				fprintf(stderr, "invalid port speed: %d\n", speed);
				return 1;
			}
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (argc != 1)
		usage();

	if (0 == speed)
		speed = 4800;

	printf("opening %s\n", argv[0]);
	if ((ifd = open(argv[0], O_RDONLY, 0444)) == -1)
		err(1, "open");

	if (fstat(ifd, &sb) == -1)
		err(1, "fstat");

	if ((buf = mmap(0, sb.st_size, PROT_READ, MAP_FILE | MAP_PRIVATE, ifd, 0)) == MAP_FAILED)
		err(1, "mmap");

	if (dflag){
		if ((ofd = open(tn, O_RDWR|O_NOCTTY, 0644)) == -1)
			err(1, "open");
		tcgetattr(ofd, &term);
		cfmakeraw(&term);
		cfsetispeed(&term, speed);
		cfsetospeed(&term, speed);
#if 0
		term.c_cflag &= ~(PARENB | PARODD | CRTSCTS);
        	term.c_cflag |= CREAD | CLOCAL;
        	term.c_iflag = term.c_oflag = term.c_lflag = (tcflag_t) 0;
#endif
		tcflush(ofd, TCIOFLUSH);
		tcsetattr(ofd, TCSANOW, &term);
		tcflush(ofd, TCIOFLUSH);
	} else {
		cfmakeraw(&term);
		cfsetospeed(&term, speed);
		cfsetispeed(&term, speed);
		if (openpty(&ofd, &sfd, tn, &term, NULL) == -1)
			err(1, "openpty");

		tcsetattr(ofd, TCSANOW, &term);
		tcsetattr(sfd, TCSANOW, &term);
	}

	sleeptime = 1000000 / (speed / (WRLEN * 10));
	printf("configured %s for %dbps - write delay %dus\n", tn, speed, sleeptime);

	for(len = 0; len < sb.st_size; len += WRLEN ){
		write(ofd, buf+len, WRLEN );
	//	tcdrain(ofd);
		if (0 == dflag){
			tcflush(ofd, TCIFLUSH);
	//		tcdrain(sfd);
			tcflush(sfd, TCIFLUSH);
		}
		spinner( len );
		/* wait sleeptime Sec */
		delay.tv_sec = (time_t)(sleeptime / 1000000000L);
		delay.tv_nsec = sleeptime % 1000000000L;
		nanosleep(&delay, NULL);
	}

	munmap(buf, sb.st_size);
	close(ifd);
	close(ofd);
	fprintf(stderr, "\010\010\010\010\010\010\010\010\010\010\010\010\n");
	return 0;
}

void spinner(int n){
	char *s = "|/-\\";

	if (n % (WRLEN * 4))
		return;

	n /= (WRLEN * 4);

	fprintf(stderr, "\010\010\010\010\010\010\010\010\010\010\010\010\010");
	fprintf(stderr, "%c %d", s[n%4], n);
	fflush(stderr);
}

void usage(void){
	fprintf(stderr, "usage: binreplay [-d <device>] [-s <port_speed>] <file>\n");
	exit(1);
}
