/* Link with Ws2_32.lib */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
 
#include <stdio.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
 
 
int main(void)
{
    WSADATA wsaData;
    WORD wVersion;
    SOCKET sock;
    char host[] = "www.martinbroadhurst.com";
    char port[] = "80";
    struct addrinfo hints, *res;
    char message[] = "GET / HTTP/1.1\nHost: www.martinbroadhurst.com\n\n";
    char buf[1024];
    int bytes_read;
    int status;
 
    wVersion = MAKEWORD(1, 1);
    if (WSAStartup(wVersion, &wsaData) != 0) {
        printf("Couldn't initialise WinSock\n");
        return 1;
    }
 
    ZeroMemory(&hints, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    status = getaddrinfo(host, port, &hints, &res);
    if (status != 0) {
        perror("getaddrinfo");
        WSACleanup();
        return 1;
    }
    sock = socket(AF_INET, SOCK_STREAM, 0);
 
    status = connect(sock, res->ai_addr, res->ai_addrlen);
    if (status == SOCKET_ERROR) {
        perror("connect");
        WSACleanup();
        return 1;
    }
 
    send(sock, message, sizeof(message), 0);
 
    do {
        bytes_read = recv(sock, buf, sizeof(buf), 0);
        if (bytes_read == SOCKET_ERROR) {
            perror("recv");
        }
        else {
            printf("%.*s", bytes_read, buf);
        }
    } while (bytes_read > 0);
 
    closesocket(sock);
    WSACleanup();
    return 0;
}