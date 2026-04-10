#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv) {
	char test[4] = "abc";
	printf("%s\n",test);

	//This causes an error, test2 is readonly
//	char *test2 = "abcd";
//	strcpy(test2,test);

	//This doesn't case an error, and strdup will copy the string and malloc
        //test2 is still read only, but the method allocates memory for it, making it writable.
//      char *test2 = "abcd";
//      test2 = strdup(test);
//      printf("%s\n",test2);
//      free(test2);

	
	char *test2 = "abcd";
        test2 = strdup(test);
	printf("%s\n",test2);
	free(test2);


	return 0;
}
