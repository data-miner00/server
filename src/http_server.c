#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include "http_server.h"

const char* read_into_buffer(char* file_name, int buf_size) {
    FILE* html_data = fopen(file_name, "r");
    char* response_data = (char*)malloc(buf_size * sizeof(char));

    // Check memory allocation successful
    if (response_data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    fgets(response_data, buf_size, html_data);

    return response_data;
}

const char* prepend_header(char* buf, int buf_size) {
    char* http_header = (char*)malloc(buf_size * sizeof(char));

    if (http_header == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    strncpy(http_header, "HTTP/1.1 200 OK\r\n\n", buf_size);
    strcat(http_header, buf);

    return http_header;
}


void setup_server_socket(int server_socket) {
    // defining the address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8001);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    listen(server_socket, 5);
}

void setup_client_socket(int server_socket, char* buf) {
    int client_socket;
    while(1) {
        client_socket = accept(server_socket, NULL, NULL);
        send(client_socket, buf, sizeof(buf), 0);
        close(client_socket);
    }
}

int create_server_socket() {
    return socket(AF_INET, SOCK_STREAM, 0);
}

