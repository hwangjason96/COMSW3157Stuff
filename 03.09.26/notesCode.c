#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

int timespec2str(char *buf, size_t len, struct timespec *ts) {
	int ret;
	struct tm t;

	// Set the time zone.
	tzset();

	if(localtime_r(&ts->tv_sec, &t) == NULL){
		return -1;
	}

	if (strftime(buf, len, "%F %T", &t) == 0) {
		return -2;
	}
	if (snprintf(buf + ret, len - ret, ".%09ld", ts->tv_nsec) == 0) {
		return -3;
	}
	return 0;
}
int main(int argc, char **argv) {
	
	struct stat buf;
	char output[128];
	char *ptr;
	
	for (int i = 1; i < argc; i++){
	      	//Youcan give it * and it will give you all of the contents within the working directory.
		printf("%s: \n",argv[i]);
		if(lstat(argv[i],&buf) < 0){
			fprintf(stderr, "Error: Cannot stat '%s'. %s. \n", argv[i],strerror(errno));
		continue;
		}
		if (S_ISREG(buf.st_mode)){
			char timestr[30];
			if (timespec2str(timestr,sizeof(timestr),&buf.st_mtim) <0) {
				fprintf(stderr, "Error: timespect2str fialed. \n");
				continue;
			}
			sprintf(output, "\n regular file, %zu bytes, last modified %s",buf.st_size, timestr);
			ptr = output;
			// TODO
		} else if (S_ISDIR(buf.st_mode)) {
			ptr = "directory";
		} else if (S_ISCHR(buf.st_mode)) {
                        ptr = "character special";
                } else if (S_ISBLK(buf.st_mode)) {
                        ptr = "block special";
                } else if (S_ISFIFO(buf.st_mode)) {
                        ptr = "fifo";
                } else if (S_ISLNK(buf.st_mode)) {
                        ptr = "symbolic link";
                } else if (S_ISSOCK(buf.st_mode)) {
                        ptr = "socket";
                } else {
		        ptr = "** unknown mode";
		}
		printf("%s\n",ptr);


	}

	return EXIT_SUCCESS;
}

