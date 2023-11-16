#include "TCPWinsocksMaster.h"

TCPWinsocksMaster::TCPWinsocksMaster()
{
	initializeWinsock();
}

TCPWinsocksMaster::~TCPWinsocksMaster()
{
	closeSocket();
}

const SOCKET TCPWinsocksMaster::getIdSocket()
{
	return idSocket;
}

void TCPWinsocksMaster::initializeWinsock()
{
	WORD nVersion = MAKEWORD(2, 2);
	if (WSAStartup(nVersion, &wsaData) != 0) {
		throw std::runtime_error("WSAStartup failed");
	}
}

void TCPWinsocksMaster::createSocket()
{
	if ((idSocket = ::socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		throw std::runtime_error("Failed to create socket");
	}
}

void TCPWinsocksMaster::closeSocket()
{
	closesocket(idSocket);
}

