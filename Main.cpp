#include "Server.h"

int main(){
	int thread_num = 4;
	int port = 80;

	Server my_server(thread_num,port);
	my_server.start();

	return 0;
}
