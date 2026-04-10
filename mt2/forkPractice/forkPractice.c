#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>


void print_num(int i) { putc(i + '0', stdout); fflush(stdout); }
//what if we recurse?
void palash(pid_t pid, int i) {
	if (i == 2) exit(0);
	print_num(i);
	if (pid == 0) exit(0);
}
//Here is a series of what happens.
int main (int argc, char **argv){
	for (int i = 0; i < 3; i++) {
	pid_t pid = fork();
	palash(pid,i);
	}
	return 0;
}
