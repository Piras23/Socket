#include "./Address.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <list>
using namespace std;

#define MAX_CONNS 50
#define MAX_MSG 4096

class SocketTCP {
	protected:	int socket_id;
	public:		SocketTCP();						//socket()
				~SocketTCP();					//close()
				bool broadcast(bool broadcast);		//setsockopt()
};


class ConnessioneTCP {
private:	int conn_id;
			Address* address;
			bool client;
public:		ConnessioneTCP(int conn_id, Address* address, bool client);
			~ConnessioneTCP();					//shutdown()

			bool invia(char* msg);
			bool invia_raw(void* msg, int length);	//send()
			char* ricevi();
			void* ricevi_raw(int* length);	//recv()
};

class ServerTCP: public SocketTCP, ConnessioneTCP {
private:	list<ConnessioneTCP>* connessioni;

public:		ServerTCP(int port, bool loopback);		//bind(), listen()
			~ServerTCP();						
			ConnessioneTCP* accetta();				//accept()
			
};

class ClientTCP: public SocketTCP {
	private:	ConnessioneTCP* connessione;
	public:		ClientTCP();					
				~ClientTCP();					

				bool connetti(Address* address);	//connect()
				bool invia(char* msg);
				bool invia_raw(void* msg, int length);	
				char* ricevi();
				void* ricevi_raw(int* length);
};


SocketTCP::SocketTCP() {
	socket_id = socket(AF_INET, SOCK_STREAM, 0);
	
}

SocketTCP::~SocketTCP() {
	close(socket_id);
}

bool SocketTCP::broadcast(bool broadcast) {
	int len_so = sizeof(int); 
	int val = status? 1: 0;
	return (setsockopt(socket_id, 
						SOL_SOCKET,
						SO_BROADCAST, 
						&val, 
						(socklen_t) len_so) == 0);
}

ConnessioneTCP::ConnessioneTCP(int conn_id, Address* address, bool client) {
	this->conn_id = conn_id;
	this->address = address;
	this->client = client;
}

ConnessioneTCP::~ConnessioneTCP(bool client) {
	delete(this->address);

	if(!this->client){
		shutdown(connId, SHUT_RDWR);
	}
}

bool ConnessioneTCP::invia(char* msg) {
	int bufferLen;
	bufferLen = strlen(msg) + 1;

	return invia_raw(msg, bufferLen);
}

bool ConnessioneTCP::invia_raw(void* msg, int length) {
	int ret = send(connId, msg, length, 0);
	if(ret != length)
		return true;

	return false;
}

char* ConnessioneTCP::ricevi() {
	char* buffer;
	int ret;

	buffer = (char*) ricevi_raw(&ret);
	if(!buffer)
		return buffer;
	buffer[ret + 1] = '\0';

	return buffer;
}

void* ConnessioneTCP::ricevi_raw(int* length) {
	void* buffer = malloc(MAX_MSG + 1);
	*length = recv(connId, buffer, MAX_MSG, 0);
	if(*length <= 0){
		free(buffer);
		return NULL;
	}

	return buffer;
}


ServerTCP::ServerTCP(int port, bool loopback):SocketTCP() {
	struct sockaddr_in myself;
	myself.sin_family = AF_INET;
	inet_aton(loopback?"127.0.0.1":"0.0.0.0", &myself.sin_addr);
	myself.sin_port = htons(port);
	if (bind(socket_id, (struct sockaddr*)&myself, (socklen_t)sizeof(struct sockaddr_in))) {
		printf("Errore sulla bind()\n");
	}

	if(listen(socket_id, MAX_CONNS)) {
		printf("Errore sulla listen()\n");
	}

	connessioni = new list<ConnessioneTCP>;
	
}

ServerTCP::~ServerTCP():~SocketTCP(), ~ConnessioneTCP() {
	connessioni*->clear();
}

ServerTCP::remConnessione(ConnessioneTCP* conn){
	this->connessioni*->remove(conn);
	this->delete(connessione*);
}

ConnessioneTCP* ServerTCP::accetta() {
	Address* address;
	struct sockaddr_in client;list<Connessione*> connessioni;
	int length = sizeof(struct sockaddr);
	conn_id = accept(socket_id, (struct sockaddr*)&client, (socklen_t*)&length);
	address = new Address(client);
	ConnessioneTCP* conn = new ConnessioneTCP(conn_id, address);

	connessioni* -> insert(conn);
	return conn;
}

ClientTCP::ClientTCP():SocketTCP() {}

ClientTCP::~ClientTCP():~SocketTCP() {
	delete(this->connessione);
}

bool ClientTCP::connetti(Address* address) {
	struct sockaddr_in server = address->getAddress();
	if (connect(socket_id, 
			    (struct sockaddr*)&server, 
			    (socklen_t)sizeof(struct sockaddr_in))) {
		return false;
	}

	ConnessioneTCP* conn = new ConnessioneTCP(socket_id, address);
	this->connessione = conn;

	return true;
}

bool ConnessioneTCP::invia(char* msg) {
	connessione->invia(msg);
}

bool ConnessioneTCP::invia_raw(void* msg, int length) {
	connessione->invia_raw(msg, length);
}

char* ConnessioneTCP::ricevi() {
	connessione->ricevi();
}

void* ConnessioneTCP::ricevi_raw(int* length) {
	connessione->ricevi_raw(length);

