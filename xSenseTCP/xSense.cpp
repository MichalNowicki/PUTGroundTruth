#include <iostream>
#include <fstream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>

#include <boost/thread.hpp>


#define DEFAULT_BUFLEN 512
#define CYCLIC_BUFFER_SIZE 5000

#define DEFAULT_PORT "27015"

int i = 0, j=0 ;
bool experiment_end = 0;

void savingThread()
{
	/* get handle to dll */ 
   HINSTANCE hGetProcIDDLL = LoadLibrary("xsens_dll.dll"); 

   /* get pointer to the function in the dll*/ 
   FARPROC lpfnGetProcessID1 = GetProcAddress(HMODULE (hGetProcIDDLL),"XSENS_create"); 
   FARPROC lpfnGetProcessID2 = GetProcAddress(HMODULE (hGetProcIDDLL),"XSENS_doTheMeasurements"); 
   FARPROC lpfnGetProcessID3 = GetProcAddress(HMODULE (hGetProcIDDLL),"XSENS_getData"); 

   /* 
      Define the Function in the DLL for reuse. This is just prototyping the dll's function. 
      A mock of it. Use "stdcall" for maximum compatibility. 
   */ 
   typedef void* (__cdecl * pICFUNC1)(int);
   typedef void (__cdecl * pICFUNC2)(void*);
   typedef void (__cdecl * pICFUNC3)(void*, double* , double* , double* , double* , double*);

   pICFUNC1 connectAtComport; 
   pICFUNC2 doTheMeasurement;
   pICFUNC3 getTheMeasurement;
   connectAtComport = pICFUNC1(lpfnGetProcessID1); 
   doTheMeasurement = pICFUNC2(lpfnGetProcessID2);
   getTheMeasurement = pICFUNC3(lpfnGetProcessID3);

   /* The actual call to the function contained in the dll */ 
   void * xsens = connectAtComport(6);

   double temp;
   double acc[4];
   double quat[4];
   double gyr[4];
   double mag[4];
   
   std::ofstream zap;
   zap.open("Xsense.data");

   printf("Ready to start the experiment\n");
	while(true)
	{
		if ( j >= i )
		{
			if ( experiment_end == 1)
				break;
			doTheMeasurement(xsens);
		}
		else
		{
			getTheMeasurement(xsens,&temp,acc,quat,gyr,mag);
			zap << temp << " | " << acc[0] << " " << acc[1] << " " << acc[2] << " | ";
			zap << quat[0] << " "<< quat[1]<< " "<< quat[2] << " "<< quat[3] << " | ";
			zap << gyr[0] << " "<<gyr[1]<< " "<<gyr[2]<< " | ";
			zap << mag[0] << " "<<mag[1]<< " "<<mag[2]<< std::endl;

			j++;
		}
		//printf("i, j : %d , %d\n", i, j);
	}

	/* Release the Dll */ 
    FreeLibrary(hGetProcIDDLL); 
	zap.close();
}

int main(void)
{
	boost::thread t(savingThread);

	WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // No longer need server socket
    closesocket(ListenSocket);

	printf("Ready to receive!\n");

    // Receive until the peer shuts down the connection
    do {

        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
				printf("Bytes received: %d\n", iResult);

				i++;
        }
        else if (iResult == 0)
            printf("Connection closing...\n");
        else  {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }

    } while (iResult > 0);

    // shutdown the connection since we're done
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();
	
	t.join();


	return 1;
}
