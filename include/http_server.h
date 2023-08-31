#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

const char* read_into_buffer(char* file_name, int buf_size);
const char* prepend_header(char* buf, int buf_size);
void setup_server_socket(int server_socket);
void setup_client_socket(int server_socket, char* buf);
int create_server_socket();

#endif

