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

const int TCPWinsocksMaster::getIdSocket()
{
	return idSocket;
}

std::string TCPWinsocksMaster::sendAndReceiveMsg(int idTarget, const std::string& msg)
{
	sendMessage(msg);
	return receiveMessage();
}

void TCPWinsocksMaster::sendMessage(std::string msg)
{
	if (send(idSocket, msg.c_str(), msg.size() + 1, 0) == -1) {
		throw std::runtime_error("Send Failed");
	}
}
void TCPWinsocksMaster::sendMessage(int idTarget, std::string msg)
{
	if (send(idTarget, msg.c_str(), msg.size() + 1, 0) == -1) {
		throw std::runtime_error("Send Failed SocketId : " + std::to_string(idTarget) + " msg : " + msg);
	}
}

std::string TCPWinsocksMaster::receiveMessage()
{
	uint trameLenght = recv(idSocket, trame_lect, DIMMAX, 0);

	if (trameLenght > DIMMAX || trameLenght == 0)
		return "";

	trame_lect[trameLenght] = '\0';
	return trame_lect;
}

void TCPWinsocksMaster::initializeWinsock()
{
	// WORD nVersion = MAKEWORD(2, 2);
	// if (WSAStartup(nVersion, &wsaData) != 0) {
	// 	throw std::runtime_error("WSAStartup failed");
	// }
}

void TCPWinsocksMaster::createSocket()
{
	if ((idSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		throw std::runtime_error("Failed to create socket");
	}
}

void TCPWinsocksMaster::closeSocket()
{
	close(idSocket);
}


