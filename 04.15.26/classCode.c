#include <stdint.h>
#include <stdio.h>
#include <arpa/inet.h>

uint16_t big_to_little_endian(uint16_t big_endian){
	//right shift one by 8, and left shift the other by 8.
	//it fills with 0's
	//btwise OR
	return ( (big_endian >> 8) | (big_endian << 8) );
}

uint16_t little_to_big_endian(uint16_t big_endian){
        //right shift one by 8, and left shift the other by 8.
        //it fills with 0's
        //btwise OR
        return ( (big_endian >> 8) | (big_endian << 8) );
}

int main() {
	uint16_t port = 12345;
	printf("%u\n", port);
	printf("%u\n", little_to_big_endian(port));
	printf("%u\n", big_to_little_endian(little_to_big_endian(port)));
	
	printf("%u\n", port);
	printf("%u\n", htons(port));
	printf("%u\n", ntohs(htons(port)));
	return 0;
}

// O: 0000 0000 | 0000 0001
// >> 8
// 0000 0000 | 0000 0000
// O: 0000 0000 | 0000 0001
// << 8
// 0000 0001 | 0000 0000
// OR both results
// 0000 0001 | 0000 0000
