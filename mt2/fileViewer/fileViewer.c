#include <stdio.h>
#include <getopt.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>

void print1(void) {
	printf("Hello ");
}

void print2(void) {
        printf("World");
}

void print3(void) {
        printf("\n");
}

int main(int argc, char **argv) {
	if(atexit(print3) != 0) {
		fprintf(stderr,"can't use print3\n");
	}
	if(atexit(print2) != 0) {
		fprintf(stderr,"can't use print2\n");
	}
        if(atexit(print1) != 0) {
		fprintf(stderr,"can't use print1\n");
        }
	return 0;
}
