#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(){
    int client_socket = socket(AF_INET6, SOCK_STREAM, 0);
    if(client_socket < 0){
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }
    struct sockaddr_in6 server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin6_family = AF_INET6;
    server_address.sin6_port = htons(8080);
    inet_pton(AF_INET6, "192.168.248.129", &server_address.sin6_addr);
    if(connect(client_socket,(struct sockaddr *)&server_address, sizeof(server_address)) < 0){
        std::cerr << "Failed to connect to server" << std::endl;
        close(client_socket);
        return 1;
    }
    const char* msg = "Hello, Server!";
    send(client_socket, msg, strlen(msg), 0);

    char buffer[1024] = {0};
    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if(bytes_received < 0){
        std::cerr << "Failed to receive message from server" << std::endl;
        close(client_socket);
        return 1;
    }
    buffer[bytes_received] = '\0';
    std::cout << "Received message from server: " << buffer << std::endl;
    std::cout << "Connected to server successfully" << std::endl;
    close(client_socket);
    return 0;
}