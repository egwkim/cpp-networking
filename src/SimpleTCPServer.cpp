#include <ctime>
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
    SOCKET listenSocket;
    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET)
    {
        std::cout << "socket function failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }
    std::cout << "socket function succeeded" << std::endl;

    // Bind the socket to specified server, port
    sockaddr_in service;
    service.sin_family = AF_INET;
    // sin_addr uses in_addr structure, which is a union.
    // s_addr is one of the three ways to access it.
    // https://learn.microsoft.com/en-us/windows/win32/api/winsock2/ns-winsock2-in_addr
    service.sin_addr.s_addr = inet_addr(ADDRESS);
    service.sin_port = htons(PORT);
    iResult = bind(listenSocket, (SOCKADDR *)&service, sizeof(service));
    if (iResult == SOCKET_ERROR)
    {
        std::cout << "bind function failed with error: " << WSAGetLastError() << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    std::cout << "bind function succeeded" << std::endl;

    // Place the socket in listening state
    iResult = listen(listenSocket, 1);
    if (iResult == SOCKET_ERROR)
    {
        std::cout << "listen function failed with error: " << WSAGetLastError() << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    std::cout << "listen function succeeded" << std::endl;

    // Accept incoming connection
    SOCKET acceptSocket;
    sockaddr_in clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    acceptSocket = accept(listenSocket, (SOCKADDR *)&clientAddr, &clientAddrLen);
    if (acceptSocket == INVALID_SOCKET)
    {
        std::cout << "accept function failed with error: " << WSAGetLastError() << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    std::cout << "accept function succeded\n";
    std::cout << inet_ntoa(clientAddr.sin_addr) << std::endl;

    // ISO 8601 date and time with offset
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    char buff[32];
    std::strftime(buff, sizeof buff, "%FT%T%z", &tm);

    std::string message;
    message = message +
              "Hello, world! Connected successfully.\n" +
              "Current time is: " + std::string(buff) + "\n";

    iResult = send(acceptSocket, message.c_str(), DEFAULT_BUFLEN, 0);
    if (iResult == SOCKET_ERROR)
    {
        std::cout << "accept function failed with error: " << WSAGetLastError() << std::endl;
        closesocket(acceptSocket);
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    std::cout << "send function succeded\n";

    closesocket(acceptSocket);
    closesocket(listenSocket);
    WSACleanup();
    return 0;
}