#include "http_server.h"

int main(void) {
    const char* buf = read_into_buffer("./templates/index.html", 1024);
    const char* buf_new = prepend_header(buf, 2048);

    int server_socket = create_server_socket();
    setup_server_socket(server_socket);
    setup_client_socket(server_socket, buf_new);

    return 0;
}
