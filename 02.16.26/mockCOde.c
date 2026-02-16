#include <stdio.h>
#include <stdlib.h>

int *get_int_array() {
	//this won't work.
	//doesn't work because the scope of the function is done, and the data is scrapped.
	//int a[3] = {1, 2, 3};
	
	//This works
	int *a = malloc(3*sizeof(int));
	a[0] = 1; a[1] = 2; a[2] = 3;
	return a;
}
int main(int argc, char **argv){
	int *p = get_int_array();
	//frees memory from the function.
	free(p);

	int *arr = malloc(4*sizeof(int));
	int *arr1 = malloc(4*sizeof(int));
	arr[0] = arr1[0] = 0;
	printf("%d,%d\n",*arr,*arr1);
	free(arr);
	free(arr1);

	char *s = "hello"; //readonly data.
	char a[6];

	//doesn't work because hello is really h e l l o \0 not just h e l l o
//	for (int i = 0; i <5; i++) {
//		a[i] = s[i];
//	}
//
//	works because it takes the null terminator into account
	for (int i = 0; i<6; i++) {
		a[i] = s[i];
	}

	printf("%s\n",a);


	char *ro_str = "hello";

	return 0;
}

