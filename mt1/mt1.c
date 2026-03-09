#include <stdio.h>
#include <stdlib.h>

struct ex1{
	int i1;
	int i2;
	char c;
	long l;
	short s;
	void *p;
};
int main(int argc, char **argv){
	struct ex1 *a = malloc(sizeof(*a));

//	char *jason = "abc";
//	*(jason+1) = 'r';
	char ming[] = "jason hwang";
	
	printf("%c\n", *(ming+3));

	//This affects the addresses of the entire struct
	*((short *) &a->i1) = 0;
	a->p = NULL;
	printf("%d\n", a->i2);
	
	free(a);
	return 0;
}

