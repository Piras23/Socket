class SocketTCP {
	protected:	int socket_id;
	public:		SocketTCP();						//socket()
				~SocketTCP();						//close()
				bool broadcast(bool broadcast);		//setsockopt()
};


class ConnessioneTCP {
private:	int conn_id;
			Address* address;
public:		ConnessioneTCP(int conn_id, Address* address);
			~ConnessioneTCP();						//shutdown()

			bool invia(char* msg);
			bool invia_raw(void* msg, int length);	//send()
			char* ricevi();
			void* ricevi_raw(int* length);	//recv()
};

class ServerTCP: public SocketTCP {
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