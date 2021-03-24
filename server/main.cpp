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


void PrintMessage(std::string message) {
    PrintCurrentTime();
    std::cout << message << "\n\n";
}


int main(int argc, const char** argv) {
    
    int listen_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (listen_socket == -1) {
        PrintMessage("Error creating socket.");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &addr, sizeof(addr)) == -1) {
        PrintMessage("Couldn't set address to reuse.");
    }

    if (bind(listen_socket, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
        PrintMessage("Error binding port.");
        return 1;
    }

    PrintMessage("System: Start chat");

    if (listen(listen_socket, BACKLOG) == -1) {
        PrintMessage("Error setting socket to listen.");
        return 1;
    }
    
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);

    int accept_socket = accept(listen_socket, (sockaddr *) &client, &clientSize);
    char buffer[BUFFER_SIZE];

    while(true) {

        if (accept_socket == -1) {
            PrintMessage("Error accepting request.");
            return 1;
        }

        int bytesReceived = recv(accept_socket, buffer, BUFFER_SIZE, 0);

        if (bytesReceived == -1) {
            PrintMessage("Error recieve data.");
            break;
        }

        if (bytesReceived == 0) {
            PrintMessage("System: Client disconnected.\n");
            break;
        }

        std::string message(buffer, bytesReceived);
        PrintMessage(message);
    }

    close(accept_socket);
    close(listen_socket);

    return 0;
}
