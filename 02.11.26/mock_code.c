#include <stdio.h>

void byteprintf(void *p, const unsigned int num_bytes){
	int bytes = num_bytes;
	//in order to print this thing in order, from low to high, it has to be drawn in the opposite order. That's why you have to write it in the highest order first. 
	//Meaning the data in the pointer is stored as low order first and then high, so you have to do it in the opposite way.
	//thats why you do the pointer arithmetic to add the number of bytes of a specific type.
	unsigned char *data = (unsigned char *)p + num_bytes - 1;
	//display_line(num_bytes);
	putc('|',stdout);
	//while bytes is not zero, decrement it.
	while (bytes--) {
		printf("%8u", *data--);
		putc('|',stdout);
	}
	printf("\n");
	//display_line(num_bytes);
	return;
}

int main() {
	int x =5, y = 6;
	int *p = &x, *q = &y;
	*p += 2;
	int* q, w, e; //only one value is the pointer, the q. w and e are ints.
	
	printf("%p\n", p);

	int array[10];
	for(int i =0; i< 10; i++){
		array[i] = i;
	}

	return 0;
}
