#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int perms[] = {S_IRUSR, S_IWUSR, S_IXUSR,
	       S_IRGRP, S_IWGRP, S_IXGRP,
	       S_IROTH, S_IWOTH, S_IXOTH};

char* permission_string(struct stat *statbuf) {
	char *perm_string;
	perm_string = malloc(11 * sizeof(char));
	if (perm_string == NULL) {
		fprintf(stderr, "Error: malloc failed. %s. \n", strerror(errno));
		exit(EXIT_FAILURE);
		}	
	perm_string[0] = '-';
	for(int i = 0; i <9; i+=3) {
	perm_string[i + 1] = statbuf->st_mode & perms[i] ? 'r' : '-';
	perm_string[i + 2] = statbuf->st_mode & perms[i+1] ? 'w' : '-';
	perm_string[i + 3] = statbuf->st_mode & perms[i+2] ? 'w' : '-';
	}
	perm_string[10] = '\0';
	return perm_string;

}



int main(int argc, char **argv){

//	if(!S_ISREG(statbuf.st_mode)) {
//		fprintf(stderr,"Error: '%s' is not a regular file.\n", argv[1]);
//		return EXIT_FAILURE;
//	}
	return 0;
}
