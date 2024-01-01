#include "http_server.h"

#define KILOBYTES 1024

int main(void) {
    char* buf = read_into_buffer("./templates/index.html", KILOBYTES);
    char* buf_new = prepend_header(buf, KILOBYTES * 2);

    int server_socket = create_server_socket();
    setup_server_socket(server_socket, 8001);
    setup_client_socket(server_socket, buf_new);

    return 0;
}
