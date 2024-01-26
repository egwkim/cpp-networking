#include <iostream>
#include <string>

#include <WinSock2.h>

#include "config.h"

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
    std::cout << "WSAStartup function succeeded\n";
    std::cout << "Status: " << wsaData.szSystemStatus << std::endl;

    // Create a socket
    SOCKET connectSocket;
    connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (connectSocket == INVALID_SOCKET)
    {
        std::cout << "socket function failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }
    std::cout << "socket function succeeded" << std::endl;

    // Connect to the server
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr(ADDRESS);
    clientService.sin_port = htons(PORT);
    iResult = connect(connectSocket, (SOCKADDR *)&clientService, sizeof(clientService));
    if (iResult == SOCKET_ERROR)
    {
        std::cout << "connect function failed with error: " << WSAGetLastError() << std::endl;
        closesocket(connectSocket);
        WSACleanup();
        return 1;
    }
    std::cout << "connect function succeeded" << std::endl;

    char buff[DEFAULT_BUFLEN];
    iResult = recv(connectSocket, buff, DEFAULT_BUFLEN, 0);
    if (iResult == SOCKET_ERROR)
    {
        std::cout << "connect function failed with error: " << WSAGetLastError() << std::endl;
        closesocket(connectSocket);
        WSACleanup();
        return 1;
    }
    std::cout << "recv function succeeded" << std::endl;
    std::cout << buff;

    closesocket(connectSocket);
    WSACleanup();
    return 0;
}