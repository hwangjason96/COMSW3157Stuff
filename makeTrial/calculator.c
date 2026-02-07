#include "divider.h"
#include "multiplier.h"
#include "adder.h"
#include "subtractor.h"

#include <stdio.h>

int main(int argc, char** argv){
	int menuOption = 0;
	int inputFirst = 0;
	int inputSecond = 0;
	int c;
	int output = 0;

	printf("Tell me what you wanna do!\n1. Add\n2. Subtract\n3. Multiply\n4. Integer Divide\nYour Option: ");
	scanf("%d",&menuOption);
	while ((c = getchar()) != '\n' && c != EOF);

	printf("Give me the left number of that operand: ");
	scanf("%d",&inputFirst);
	while ((c = getchar()) != '\n' && c != EOF);

	printf("Now the second! : ");
	scanf("%d",&inputSecond);
	while ((c = getchar()) != '\n' && c != EOF);

	switch(menuOption){
		case 1:
			output = add(inputFirst,inputSecond);
			break;
		case 2:
			output = subtract(inputFirst,inputSecond);
			break;
		case 3:
			output = multiply(inputFirst,inputSecond);
			break;
		case 4:
			output = divide(inputFirst,inputSecond);
			break;
		default:
			printf("Invalid Option!\n");
			return 1;
		}
	printf("The result is: %d\n", output);

	return 0;
}
