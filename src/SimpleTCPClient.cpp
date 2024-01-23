#include <iostream>

#include <WinSock2.h>

#define PORT 54322

int main()
{
    int iResult = 0;

    // Call WSAStartup function to initiates use of the Winsock DLL
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 2);
    iResult = WSAStartup(wVersionRequested, &wsaData);
    if (iResult != NO_ERROR)
    {
        std::cout << "WSAStartup function failed with error: " << iResult << std::endl;
        return 1;
    }
    else
    {
        std::cout << "WSAStartup function succeeded\n";
        std::cout << "Status: " << wsaData.szSystemStatus << std::endl;
    }

    // Create a socket
    SOCKET connectSocket;
    connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (connectSocket == INVALID_SOCKET)
    {
        std::cout << "socket function failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }
    else
    {
        std::cout << "socket function succeeded" << std::endl;
    }

    // Bind the socket to specified server, port
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr("127.0.0.1");
    service.sin_port = htons(PORT);
    iResult = bind(connectSocket, (SOCKADDR *)&service, sizeof(service));
    if (iResult == SOCKET_ERROR)
    {
        std::cout << "bind function failed with error: " << WSAGetLastError() << std::endl;
        closesocket(connectSocket);
        WSACleanup();
        return 1;
    }
    else
    {
        std::cout << "bind function succeeded" << std::endl;
    }

    // Connect to the server
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientService.sin_port = htons(54321);
    iResult = connect(connectSocket, (SOCKADDR *)&clientService, sizeof(clientService));
    if (iResult == SOCKET_ERROR)
    {
        std::cout << "connect function failed with error: " << WSAGetLastError() << std::endl;
        closesocket(connectSocket);
        WSACleanup();
        return 1;
    }
    else
    {
        std::cout << "connect function succeeded" << std::endl;
    }

    closesocket(connectSocket);
    WSACleanup();
    return 0;
}