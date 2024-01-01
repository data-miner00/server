#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

char* read_into_buffer(const char* file_name, int buf_size);
char* prepend_header(const char* buf, int buf_size);
void setup_server_socket(int server_socket, int port);
void setup_client_socket(int server_socket, char* buf);
int create_server_socket();

#endif

