#include "multiplier.h"
#include "adder.h"

int multiply(int left, int right){
	int result=0;
	for (int i = 0; i < right; i++){
		result = add(result,left);
	}
	return result;
}
