#include "TCPWinsocksMaster.h"

TCPWinsocksMaster::TCPWinsocksMaster(uint serverPORT) : serverPORT(serverPORT)
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

std::string TCPWinsocksMaster::sendAndReceiveMsg(SOCKET idTarget, const std::string& msg)
{
	sendMessage(msg);
	return receiveMessage();
}

void TCPWinsocksMaster::sendMessage(std::string msg)
{
	if (send(idSocket, msg.c_str(), msg.size() + 1, 0) == SOCKET_ERROR) {
		throw std::runtime_error("Send Failed");
	}
}
void TCPWinsocksMaster::sendMessage(SOCKET idTarget, std::string msg)
{
	if (send(idTarget, msg.c_str(), msg.size() + 1, 0) == SOCKET_ERROR) {
		throw std::runtime_error("Send Failed SocketId : " + std::to_string(idTarget) + " msg : " + msg);
	}
}

std::string TCPWinsocksMaster::receiveMessage()
{
	uint trameLenght = recv(idSocket, trame_lect, DIMMAX, 0);

	trame_lect[trameLenght] = '\0';
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

