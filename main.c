#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> /* close() */
#include <sys/socket.h>
#include <netdb.h>
 
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Wrong no of arguments, only 1 argument needed.\n Exiting in Error!\n);
		return -1;
	}
	int buf_size = atoi(argv[1]);
    int sock;
    char host[] = "www.ecst.csuchico.edu";
    char port[] = "80";
    struct addrinfo hints, *res;
    char message[] = "GET /~kkredo/file.html HTTP/1.0\r\n\r\n";
    char buf[buf_size];
    int bytes_read;
    int status;
    int count = 0;
    int index = 0;
    int TotalBytesRead = 0;
    int TotalTags = 0;
 
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    status = getaddrinfo(host, port, &hints, &res);
    if (status != 0) {
        perror("getaddrinfo");
        return 1;
    }
    sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock == -1) {
        perror("socket");
        return 1;
    }
    status = connect(sock, res->ai_addr, res->ai_addrlen);
    if (status == -1) {
        perror("connect");
        return 1;
    }
    freeaddrinfo(res);
    send(sock, message, strlen(message), 0);
 
    do {
    	count = 0;
        bytes_read = recv(sock, buf, buf_size, 0);
        
		if (bytes_read == -1) 
		{
            perror("recv");
        }
        else 
		{
			for (index = 0; index < bytes_read - 2, index++)
			{
				if( (buf[index] == '<') && (buf[index+1] == 'p') && (buf[index+2] == '>') )
            	{	
            		count++;
				}
			}
				
        	//printf("%.*s", bytes_read, buf);
          	TotalBytesRead += bytes_read;
          	TotalTags += count;
        }
    } while (bytes_read > 0);

 	printf("No of Bytes Read in Total = %d\n", TotalBytesRead);
	printf("Total no of p-tags = %d\n", TotalTags);
 
    close(sock);
 
    return 0;
}
