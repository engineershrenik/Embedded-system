/*
    Create a TCP socket
*/
 
#include<stdio.h>
#include<winsock2.h>
#include "console.h"

 
#pragma comment(lib,"ws2_32.lib") //Winsock Library
 
 WSADATA wsa;
 SOCKET s;
 struct sockaddr_in server;
 char *message;

int tcpInit(void)
{
  
 
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }
     
    printf("Initialised.\n");
     
    //Create a socket
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }
 
    printf("Socket created.\n");
     
     
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(5005 );
 
    //Connect to remote server
    if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }
	return 0;

}

int tcpSendData(char *uData)
{
     //while (1)
     //{
		//puts("Connected");

		retry:  
		//Send some data
		//message = "GET / HTTP/1.1\r\n\r\n";
		if( send(s , uData , strlen(uData) , 0) < 0)
		{
			puts("Send failed");
			return 1;
			goto retry;
		}
		Sleep(1);
		puts("Data Send\n");
    //}
		return 0;
}
 //   closesocket(s);
   // WSACleanup();
  //  return 0;
//}
