#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define BUF_SIZE 256

int send_message(char * message, int sfd){

	size_t len;
	ssize_t nread;
	char buf[BUF_SIZE];

	len = strlen(message) + 1;

	if (len +1 > BUF_SIZE) {

      	fprintf(stderr, "Too long message, failed.\n");
		return 1;
	}

	if (write(sfd, message, len) != len) {

      	fprintf(stderr, "partial/failed write\n");
      	exit(EXIT_FAILURE);
	}

	nread = read(sfd, buf, BUF_SIZE);
	if (nread == -1) {

      perror("read");
      exit(EXIT_FAILURE);
	}

	printf("Received %ld bytes: %s\n", (long) nread, buf);

	return 0;
}

