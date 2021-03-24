#include <cstdio>
#include <iostream>
#include <string>

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>


constexpr int kServerPort = 8000;


int main(int argc, char const *argv[])
{
    int client = socket(AF_INET, SOCK_STREAM, 0);

    if (client == -1) {
        printf("Error creating socket.\n");
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(kServerPort);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (connect(client, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
        printf("Error connecting server.\n");
        return 1;
    }

    std::string message = "";

    while (true) {
        std::cout << "Send message: ";
        std::getline(std::cin, message);
        send(client, message.c_str(), message.size() + 1, 0);
    }

    close(client);

    return 0;
}
