#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t got_signal = 0;


void catch_signal(int sig){
	got_signal = 1;
}

int main(int argc, char *argv[]){
	if (argc != 2){
		fprintf(stderr,"Usage: %s <seconds> \n",argv[0]);
		return EXIT_FAILURE;
	}

	int max_sleep_seconds = atoi(argv[1]);
	if (max_sleep_seconds <= 0) {
		fprintf(stderr,"Usage: %s <seconds> \n",argv[1]);
		return EXIT_FAILURE;
	}

	struct sigaction action = {0};
	action.sa_handler = catch_signal;
	action.sa_flags = SA_RESTART;

	if (sigaction(SIGINT, &action, NULL) == -1) {
		perror("sigaction");
		return EXIT_FAILURE;
	}

	int count = 0;
	while (!got_signal && count < max_sleep_seconds) {
		sleep(1);
		count++;
	}
	printf("Slept for %d of the %d seconds allowed.\n",count,max_sleep_seconds);
	return 0;
}
