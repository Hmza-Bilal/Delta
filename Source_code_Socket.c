/* Link with Ws2_32.lib */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
 
#include <stdio.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <winsock2.h>

 
 
int main(void)
{
    WSADATA wsaData;
    WORD wVersion;
    SOCKET sock;
    char host[] = "www.ecst.csuchico.edu";
    char port[] = "80";
    struct addrinfo hints, *res;
    char message[] = "GET /~kkredo/file.html HTTP/1.0\r\n\r\n";
    char buf[1024];
    int bytes_read;
    int status;
    int count = 0;
    int index = 0;
    int TotalBytesRead = 0;
    int TotalTags = 0;
 
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
 
    do 
	{
        bytes_read = recv(sock, buf, sizeof(buf), 0);
        if (bytes_read == SOCKET_ERROR) 
		{
            perror("recv");
        }
        else 
		{
        		
           	if(buf[index]=='<'&& buf[index+1]=='p'&& buf[index+2]=='>');
          		count++;
            
			printf("%.*s", bytes_read, buf);
            TotalBytesRead += bytes_read;
            TotalTags +=count;

       
        }
    } while (bytes_read > 0);

    
	//printf("No of p Tags per Chunk = %d.\n",count);
	printf("No of Bytes Read in total = %d.\n",TotalBytesRead);
	printf("No of Total Tags = %d",TotalTags);
      
         
      
      
      
    closesocket(sock);
    WSACleanup();
    return 0;
}



