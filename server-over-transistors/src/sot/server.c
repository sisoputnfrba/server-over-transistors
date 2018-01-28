#include "server.h"

#define BACKLOG 5
#define PACKAGESIZE 1024

t_log* create_logger(t_log_level log_level){
	char * file = tmpnam(NULL);
	t_log* logger = log_create(tmpnam(NULL), "SOT-Server", true, log_level);

	log_info(logger, "Logeando en [%s]", file);
	return logger;
}

void run_server(t_sot_server_config config){
	t_log* logger = create_logger(config.log_level);


	struct addrinfo hints;
	struct addrinfo *serverInfo;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo(NULL, config.port, &hints, &serverInfo);

	int listenningSocket;
	listenningSocket = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);

	bind(listenningSocket,serverInfo->ai_addr, serverInfo->ai_addrlen);
	freeaddrinfo(serverInfo); 

	log_info(logger, "Escuchar en el puerto %s", config.port);
	listen(listenningSocket, BACKLOG);

	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);


	while (true){
		int socketCliente = accept(listenningSocket, (struct sockaddr *) &addr, &addrlen);
		char package[PACKAGESIZE];
		log_info(logger, "Conexcion con %d aceptada", socketCliente);

		void writter (char *message){
			log_info(logger, "Enviando a %d: [%s]:%d", socketCliente, message, strlen(message));
			send(socketCliente, message, strlen(message) + 1, 0);
		}

		int size = recv(socketCliente, (void*) package, PACKAGESIZE, 0);
		log_info(logger, "Recivido a %d bytes de %d", size, socketCliente);
		config.handler(http_parse(size, package), writter);

		close(socketCliente);
	}
	close(listenningSocket);
	log_destroy(logger);
}