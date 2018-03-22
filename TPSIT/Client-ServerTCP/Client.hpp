class ClientTCP{
	private :	int sock_id;
	public :	ClientTCP();
				~ClientTCP();
				bool connetti(Address);
				bool invia(char*);
				char* ricevi();
				bool inviaRaw(void*, int);
				void* riceviRaw(&int);
				bool broadcast(bool);
};

ClientTCP::ClientTCP(){

}

ClientTCP::~ClientTCP(){
	int ret;
	ret = close(sock_id);
}

bool ClientTCP::connetti(Address server){
	int ret;
	struct sockaddr_in, server;
	ret = connect(sock_id, (struct sockaddr*)&server,(socklen_t)sizeof(struct sockaddr_in));

}

bool ClientTCP::invia(char* msg){
	int ret; 
	ret = send(sock_id, argv[3], strlen(argv[3]+1),0);
}

char* ClientTCP::ricevi(){

}

bool ClientTCP::inviaRaw(void* ptr,int lenght){

}

void* ClientTCP::riceviRaw(&int lenght){

}

bool ClientTCP::broadcast(bool status){

}