#include<stdio.h>
#include<stdlib.h>

//max function!
char mystery(char a, char b){
	// will subtract from a - b
	char c = a-b, 
	     //checks if the subtaction of a-b is negative
	     d = (c >> 7) & 1,
	     // a - ( (a-b) * (-1 or 1) )
	     mystery = a - c * d;
	
	return mystery;
}
int main() {
	//this will be true
	if (3) {		
	puts("YES");
	}

	int test = 5;
	
	if(3 || ++test) {
		printf("%d\n",test);
	}

	//can you change the values of two variables using the XOR?
	char a = 11,b = 5;
	printf("a = %d, b = %d\n",a,b);
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
	printf("After switching: a = %d, b = %d\n",a,b);
	
	//strings in C. string something = "42", it is really char[3] = {'4','2',\0} \0 null-terminating char.
	//
	
	//this will output 0 because atoi isn't that great.
	char s[] = "HI";
	printf("%d\n", atoi(s));

	//this will output just 2 decimal points
	printf("%.2lf\n",3.14958);

	//putc
	char ch = 'A';

	putc(ch,stdout);

	return 0;
}
