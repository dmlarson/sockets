/*
 * server.cpp -- simple server using sockets
 * @Author Dane
 */

#include "server.h"

void help(){
	std::cout << "USAGE: \n ./server [port]" << std::endl;
}

void error(char *msg){
	std::cout << "---ERROR---"<< std::endl;
	std::wcout << msg << std::endl;
	exit(1);
}

int main(int argc, char *argv[]){

	//check usage
	if(argc !=2){
		help();
		exit(1);
	}

	char[] hostname = HOSTNAME;
	int status=0; //used to check status of getaddrinfo
	int port_num; //port number
	int socket_fd; //the file descryptor for the socket we will use
	int socket_fd_client; //file descryptor of the client
	char buf_in[256]; //buffer that holds incoming
	char buf_out[256]; //buffer that holds outgoing
	struct sockaddr_in addr_serv; //servers address struct
	struct sockaddr_in addr_client; //clients address struct
	struct addrinfo addr_info; //the address info
	struct addrinfo *addr_results; //the results of the address info

	//grab port parameter
	port_num = atoi(argv[1]);

	//look up address and get the correct information
	memset(&addr_info, 0, sizeof(addr_info));//set the struct values to 0
	addr_info.ai_family = AF_UNSPEC; //unspecified address version ip4 or ip6
	addr_info.ai_socktype = SOCK_STREAM; //type of socket to use this case is tcp
	if(LOCAL){
		addr_info.ai_flags = AI_PASSIVE; //use this machines ip

		//get check that we got addr_info results
		if((status=getaddrinfo(NULL, port_num, &addr_info,addr_results)) != 0){
			error("could not get addrinfo");
		}

	}
	//get the results of addrinfo
	else if((status=getaddrinfo(hostname, port_num, &addr_info,addr_results)) != 0){
		error("could not get addrinfo");
	}

	//setup socket
	//using internet addressing, tcp stream, and protocol
	socket_fd = socket(addr_results->ai_family, addr_results->ai_socktype, addr_results->ai_protocol);
	//check to see if it worked
	if(socket_fd<0){
		error("socket_fd not created");
	}

	//bind to a specific port
	if((status =bind(socket_fd, addr_results->ai_addr, addr_results->ai_addrlen))==-1){
		error("could not bind port");
	}

	//connect to our socket
	//if((status = connect(socket_fd, addr_results->ai_addr,addr_results->ai_addrlen))==-1){
	//	error("could not connect")
	//}

	//listen to our socket
	listen(socket_fd, BACKLOG)

	while(1){
	//accept recieved connections
	size_addr = sizeof addr_client;
	socket_fd_client = accept(socket_fd, (struct sockaddr *)&addr_client,&size_addr);
	if(socket_fd_client == -1){
		continue;
	}
	std::cout << "server got a connection from "<< get_in_addr((struct sockaddr *)&addr_client) << std::endl;
	}
}
