#define MAX_MSG 4092
int main (int argc, char*argv[]){
	if(argc!=4){
		printf("Usage % IP Port MSG \n", argv[0]);
		return(-1);
	}
	int sock_id;
	char buffer[MAX_MSG+1];
	sock_id = socket(AF_INET,SOCK_STREAM, 0);
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	inet_aton(&server.sin_address, argv[1]);
	for(int i;i<8;i++){
		server.sinzero[i]=0;
	}
	if(connect(sock_id,(struct sockaddr*)&server, (socklen_t) sizeof(struct sockaddr_in))){
		close(sock_id);
		errore("Errore di connessione",-2);
	}
	int ret=send(sock_id,argv[3],strlen(argv[3]+1),0);
	if(ret!=strlen(argv[3]+1),0){
		close(sock_id);
		errore("Errore di invio", -3);
	}
	ret=recv(sock_id,buffer,MAX_MSG, 0);
	if(ret<=0){
		close(sock_id);
		errore("Errore di ricezione", -3);
	}
	buffer[ret]='';
	printf("[%s:%d]%s\n", argv[1], atoi(argv[2]),buffer);
	close(sock_id);
	return 0;
}