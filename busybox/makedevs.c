/* vi: set sw=4 ts=4: */
/*
 * public domain -- Dave 'Kill a Cop' Cinege <dcinege@psychosis.com>
 * 
 * makedevs
 * Make ranges of device files quickly. 
 * known bugs: can't deal with alpha ranges
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include "busybox.h"

int makedevs_main(int argc, char **argv)
{
	dev_t dev = 0;
	mode_t mode = 0;
	char *basedev, *type, devname[255], buf[255];
	int major, Sminor, S, E, sbase;

	if (argc < 7 || *argv[1]=='-')
		show_usage();

	basedev = argv[1];
	type = argv[2];
	major = atoi(argv[3]);
	Sminor = atoi(argv[4]);
	S = atoi(argv[5]);
	E = atoi(argv[6]);
	sbase = argc == 8 ? 1 : 0;

	switch (type[0]) {
	case 'c':
		mode = S_IFCHR;
		break;
	case 'b':
		mode = S_IFBLK;
		break;
	case 'f':
		mode = S_IFIFO;
		break;
	default:
		show_usage();
	}
	mode |= 0660;

	while (S <= E) {

		if (type[0] != 'f')
			dev = (major << 8) | Sminor;
		strcpy(devname, basedev);

		if (sbase == 0) {
			sprintf(buf, "%d", S);
			strcat(devname, buf);
		} else {
			sbase = 0;
		}

		if (mknod(devname, mode, dev))
			printf("Failed to create: %s\n", devname);

		S++;
		Sminor++;
	}

	return 0;
}

/*
And this is what this program replaces. The shell is too slow!

makedev () {
local basedev=$1; local S=$2; local E=$3
local major=$4; local Sminor=$5; local type=$6
local sbase=$7

	if [ ! "$sbase" = "" ]; then
		mknod "$basedev" $type $major $Sminor
		S=`expr $S + 1`
		Sminor=`expr $Sminor + 1`
	fi

	while [ $S -le $E ]; do
		mknod "$basedev$S" $type $major $Sminor
		S=`expr $S + 1`
		Sminor=`expr $Sminor + 1`
	done
}
*/
