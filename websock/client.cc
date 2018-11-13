#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <uWS/uWS.h>

class mysock{
public:
	uWS::Hub hub;
	uWS::WebSocket<uWS::CLIENT> mWS;
	mysock(){
		this->hub.onConnection([this](uWS::WebSocket<uWS::CLIENT> ws, uWS::UpgradeInfo ui){
			this->mWS = ws;
		});
	
		this->hub.onMessage([](uWS::WebSocket<uWS::CLIENT> ws, char* message, size_t length, uWS::OpCode opCode){
			printf("Message is : %s\n", message);
		});
		this->hub.connect("ws://127.0.0.1:3000", nullptr);
		pthread_t myt;
		pthread_create(&myt,NULL,run_web_socket,this);
	}
	
	static void *run_web_socket(void* ptr){
		mysock *p = (mysock*) ptr;
		p->hub.run();
	}

};

int main(int argc, char** argv){
	mysock *obj = new mysock();
	for(int i=0;i<10;i++){
		sleep(1);
		obj->mWS.send("Hai this is the message",uWS::OpCode::TEXT);
	}
	return 0;
}
