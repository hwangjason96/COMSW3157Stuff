#include "divider.h"
#include "subtractor.h"
#include <stdio.h>

int divide(int left, int right){
	int result = 0;
	int divisor = left;
	while (divisor > right){
		divisor = subtract(divisor,right);
		result++;
	}
	return result;
}
