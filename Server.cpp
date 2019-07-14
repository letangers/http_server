#include "Server.h"

Server::Server(int thread_num,int port):
	port_(port),
	epoll_(new Epoll()),
	//thread_pool_(new ThreadPool(epoll_,thread_num)),
	thread_pool_(new ThreadPool(thread_num)),
	start_(false)
{
}

Server::~Server(){
	start_.store(false);
	accept_thread_.join();
	Close(listenfd_);
}

bool Server::Init(){
	//init http field trie
	auto http_field_data = HttpFieldData::GetInstance();
	if(!http_field_data->LoadFile("data/HttpField")){
		std::cout<<"open http field failed"<<std::endl;
	}
	
	//gain listenfd_
	listenfd_ = Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port_);
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);

	int on=1;
	//开启地址重复利用(TIME-WAIT时可以启用被占用的端口)
	setsockopt(listenfd_,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
		
	Bind(listenfd_,(struct sockaddr*)&server_addr,sizeof(server_addr));

	Listen(listenfd_,SOMAXCONN);
	SetSocketNonBlocking(listenfd_);

	return true;
}

void Server::start(){

	start_.store(true);
	Init();
	accept_thread_ = std::move(std::thread(AcceptFunc,this));
	thread_pool_->start();
	accept_thread_.join();
}

void AcceptFunc(Server *sp){
	struct sockaddr_in peer_addr;
	socklen_t peer_len = sizeof(peer_addr);
	int connfd;
	while(sp->start_.load()){
		connfd = Accept(sp->listenfd_, (struct sockaddr*)&peer_addr, &peer_len);
		if(connfd < 0){
			continue;
		}
		SetSocketNonBlocking(connfd);
		sp->thread_pool_->epoll_->EpollAdd(connfd);
	}
}
