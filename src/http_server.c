#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include "http_server.h"

char* read_into_buffer(const char* file_name, int buf_size) {
    FILE* html_data = fopen(file_name, "r");

    fclose(html_data);
    fseek(html_data, 0, SEEK_END);
  	long fsize = ftell(html_data);
	  fseek(html_data, 0, SEEK_SET);

	  char* response_data = malloc(sizeof(char) * (fsize+1));
	  char ch;
	  int i = 0;
	  while((ch = fgetc(html_data)) != EOF) {
		    response_data[i] = ch;
		    i++;
	  }
	  fclose(html_data);

    return response_data;
}

char* prepend_header(const char* buf, int buf_size) {
    char* http_header = (char*)malloc(buf_size * sizeof(char));

    if (http_header == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    strncpy(http_header, "HTTP/1.1 200 OK\r\n\r\n", buf_size);
    strcat(http_header, buf);

    return http_header;
}


void setup_server_socket(int server_socket, int port) {
    // defining the address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    listen(server_socket, 5);

    printf("Server started %shttp://127.0.0.1:%d%s\n", "\033[92m", 8001, "\033[0m");
}

void setup_client_socket(int server_socket, char* buf) {
    int buf_size = 4096;
    char local_buf[buf_size];

    strncpy(local_buf, buf, buf_size);

    int client_socket;
    while(1) {
        client_socket = accept(server_socket, NULL, NULL);
        send(client_socket, local_buf, sizeof(local_buf), 0);
        close(client_socket);
    }
}

int create_server_socket() {
    return socket(AF_INET, SOCK_STREAM, 0);
}

