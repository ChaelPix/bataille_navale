#include "TCPWinsocksMaster.h"

TCPWinsocksMaster::TCPWinsocksMaster()
{
	initializeWinsock();
	createSocket();
}

TCPWinsocksMaster::~TCPWinsocksMaster()
{
	closeSocket();
}

const SOCKET TCPWinsocksMaster::getIdSocket()
{
	return idSocket;
}

void TCPWinsocksMaster::sendMessage(SOCKET targetSocketId, std::string msg)
{
	if (send(targetSocketId, msg.c_str(), msg.size() + 1, 0) == SOCKET_ERROR) {
		throw std::runtime_error("Send Failed");
	}
}

std::string TCPWinsocksMaster::receiveMessage()
{
	recv(idSocket, trame_lect, DIMMAX, 0);
	return trame_lect;
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
	if ((idSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		throw std::runtime_error("Failed to create socket");
	}
}

void TCPWinsocksMaster::closeSocket()
{
	closesocket(idSocket);
}

