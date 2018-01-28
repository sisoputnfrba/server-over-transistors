#include "server.h"

#define BACKLOG 5
#define PACKAGESIZE 1024

#define safe_call(x) if (x == -1) {\
    perror(string_from_format("ERROR-%d", __LINE__));\
    exit(1);\
} 

t_log* create_logger(t_log_level log_level){
	char * file = tmpnam(NULL);
	t_log* logger = log_create(tmpnam(NULL), "SOT-Server", true, log_level);

	log_info(logger, "Logeando en [%s]", file);
	return logger;
}

char* wrap_response(char* wrap_response){
    return string_from_format("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %d\r\nConnection: close\r\n\r\n%s", string_length(wrap_response), wrap_response);
}

void run_server(t_sot_server_config config){
	t_log* logger = create_logger(config.log_level);

	struct addrinfo hints;
	struct addrinfo *serverInfo;
	int yes = 1;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo(NULL, config.port, &hints, &serverInfo);

	int listenningSocket;
	listenningSocket = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);

	safe_call(
		setsockopt(listenningSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))
	)

	safe_call(
		bind(listenningSocket,serverInfo->ai_addr, serverInfo->ai_addrlen)
	)
	freeaddrinfo(serverInfo); 

	log_info(logger, "Escuchar en el puerto %s", config.port);
	safe_call(
		listen(listenningSocket, BACKLOG)
	)

	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);


	while (true){
		int socketCliente = accept(listenningSocket, (struct sockaddr *) &addr, &addrlen);
		char package[PACKAGESIZE];
		log_info(logger, "Conexcion con %d aceptada", socketCliente);

		void writter (char *message){
			log_info(logger, "Enviando a %d: [%s]:%d", socketCliente, message, strlen(message));
			char* response = wrap_response(message);
			log_trace(logger, ">>> [%s]", response);
			send(socketCliente, response, strlen(response), 0);
			free(response);
		}

		int size = recv(socketCliente, (void*) package, PACKAGESIZE, 0);
		log_info(logger, "Reciviendo %d bytes de %d", size, socketCliente);
		log_trace(logger, "<<< [%s]", package);

		config.handler(http_parse(size, package), writter);

		shutdown (socketCliente, SHUT_RDWR);
		close(socketCliente);
	}
	close(listenningSocket);
	log_destroy(logger);
}