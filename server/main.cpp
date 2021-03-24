#include <iostream>
#include <string>

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "time.h"

constexpr int BACKLOG = 10;
constexpr int PORT = 8000;
constexpr int BUFFER_SIZE = 128;


int main(int argc, const char** argv) {
    
    int listen_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (listen_socket == -1) {
        printf("Error creating socket.\n");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &addr, sizeof(addr)) == -1) {
        printf("Couldn't set address to reuse.\n");
    }

    if (bind(listen_socket, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
        printf("Error binding port.\n");
        return 1;
    }

    std::string current_time = GetCurrentTime();
    printf("[%s] System: start chat\n", current_time.c_str());

    if (listen(listen_socket, BACKLOG) == -1) {
        printf("Error setting socket to listen.\n");
        return 1;
    }
    
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);

    int accept_socket = accept(listen_socket, (sockaddr *) &client, &clientSize);
    char buffer[BUFFER_SIZE];

    while(true) {

        if (accept_socket == -1) {
            printf("Error accepting request.\n");
            return 1;
        }

        int bytesReceived = recv(accept_socket, buffer, BUFFER_SIZE, 0);

        if (bytesReceived == -1) {
            printf("Error recieve data.\n");
            break;
        }

        if (bytesReceived == 0) {
            current_time = GetCurrentTime();
            printf("[%s] System: Client disconnected.\n", current_time.c_str());
            break;
        }

        std::string message(buffer, bytesReceived);
        printf("[%s] User: %s\n", current_time.c_str(), message.c_str());
    }

    close(accept_socket);

    return 0;
}
