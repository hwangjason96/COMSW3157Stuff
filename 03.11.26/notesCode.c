#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main (int argc, char** argv){
	
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
		return EXIT_FAILURE;
	}
	// PATH_MAX 4096 chars including \0
	char path[PATH_MAX + 1]; // ? +1?
	
	if (realpath(argv[1], path) == NULL){
		fprintf(stderr, "Error: Cannot get full path of file '%s'. %s. \n", argv[1], strerror(errno));
		return EXIT_FAILURE;
	}

	DIR *dir;
	if((dir = opendir(path)) == NULL) {
		fprintf(stderr, "Error: Cannot open directory '%s'. %s.\n", path, strerror(errno));
		return EXIT_FAILURE;
	}

	size_t pathlen = strlen(path);
	//Only the root folder '/' ends with a '/'.
	// ALL paths typically end in the name of the file, as in /home/user.
	if (strcmp(path,"/")) {
		//if not root, append a '/'.
		path[pathlen++] = '/';
		path[pathlen] = '\0';
	}

	struct dirent *entry;
	struct stat sb;

	while ((entry = readdir(dir)) != NULL){
		//SKip . and ..
		if (strcmp(entry->d_name,".") == 0 ||
		    strcmp(entry->d_name,"..") == 0) {
			continue;
		}
		strncpy(path + pathlen, entry->d_name, PATH_MAX - pathlen);
		if(lstat(path, &sb) < 0) {
			fprintf(stderr, "Error: Cannot stat file '%s'. %s.", path, strerror(errno));
		continue;
		}
		if (S_ISDIR(sb.st_mode)) {
			printf("%s [directory]\n",path);
		} else {
			printf("%s\n",path);
		}
	}
	closedir(dir);
	return EXIT_SUCCESS;
}
