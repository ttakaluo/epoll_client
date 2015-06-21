#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h> 
#include <unistd.h>
#include <errno.h>
#include "send_message.h"

int main(int argc, char *argv[]){

	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int sfd, s;

	if (argc != 4) {

		fprintf(stderr, "Usage: %s host port msg\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC; //IPv4 and IPv6
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = 0;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	s = getaddrinfo(argv[1], argv[2], &hints, &result);

	if (s != 0) {

		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	for (rp = result; rp != NULL; rp = rp -> ai_next) {

		sfd = socket(rp -> ai_family, rp -> ai_socktype, rp -> ai_protocol);

		if (sfd == -1)
			continue;

		if (connect(sfd, rp -> ai_addr, rp -> ai_addrlen) == -1){

			fprintf(stderr, "Value of errno: %d\n", errno);
			fprintf(stderr, "Error occured: %s\n", strerror(errno));
		}
		else
			break; //success

		close(sfd);
	}

	if (rp == NULL) {

		fprintf(stderr, "Could not connect\n");
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(result);

	send_message(argv[3], sfd);

	return 0;
}
