/*
	vim:syntax=c tabstop=2 shiftwidth=2

	Shell.FM - autoban.c
	Copyright (C) 2006 by Jonas Kramer
	Published under the terms of the GNU General Public License (GPL).
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "include/settings.h"

int banned(const char * artist) {
	FILE * fd;
	signed match = 0;
	
	if(!artist)
		return 0;

	if(!(fd = fopen(rcpath("autoban"), "r")))
		return 0;

	while(!feof(fd) && !match) {
		char line[1024] = { 0 }, * ptr;
		if(!fgets(line, sizeof(line), fd))
			continue;
	
		if(strlen(line) > 1) {
			(ptr = strrchr(line, 10)) && (* ptr = (char) 0);
			match = !strncasecmp(line, artist, strlen(line));
		}
	}

	fclose(fd);
	return match;
}

int autoban(const char * artist) {
	FILE * fd;
	const char * file = rcpath("autoban");

	if(!artist)
		return 0;
	
	if(!(fd = fopen(file, "a"))) {
		printf("Sorry, %s could not be written.\n", file);
		return 0;
	}

	fprintf(fd, "%s\n", artist);
	fclose(fd);

	return !0;
}
