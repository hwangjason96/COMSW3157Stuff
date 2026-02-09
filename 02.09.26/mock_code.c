#include <stdio.h>
#include <limits.h>


//incorrect macro
#define MAX(A,B) ( A < B ? A :B)

//Correct Macro
//#define MAX(A,B) ((A) > (B) ? (A) : (B))
struct book {
	int year;

	int month;

	int book_id;
}; //don't forget the ;

union my_union {int i; short s; char c; };

int main(int argc, char **argv) {
	int k = 5;
	printf("%d\n",k);

	int a = -12;
	unsigned int b =a;
	printf("%u\n", b);
	printf("%u\n",UINT_MAX);

	double d = 3.14;
	int pi = d;
	printf("%d\n",pi);

	//ascii 65 is 'A', ascii 96 is 'a'.
	//char var1 = 0x41;
	//int avr2 = 1.5;
	//All of the bytes not fitting in the char will be removed except for the end
	//char c = 0x41424344;
	//above will give you d because the last two letters in hex will compute
	
	// float f;
	// int top = 20, bot = 3;
	// f = top/bot; //it is 6
	// f = (float) top/bot; //this is 6.666667
	
	//Macro test	
	printf("%d\n",MAX(6,7));

	//union my_union test;
	//int var0;
	//test.i = 0;
	//test.c = 'A';
	//test.s = 16383;
	//var0 = test.c;

	/*
	 * test.i: |00000000|00000000|00000000|00000000|
	 *
	 * test.c: |00000000|00000000|00000000|01000010|
	 * 
	 * test.s: |00000000|00000000|00111111|11111111|
	 * 
	 * */

	int array[10] = {2};
	printf("%d\n", array[0]);
	printf("%d\n", *(array + 0));
	printf("%d\n", *(0 + array));
	printf("%d\n", *(array));
	printf("%d\n", 0[array]);
	return 0;
}
