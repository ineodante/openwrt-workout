#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <uWS/uWS.h>

class mysock{
	private:
		uWS::Hub mClient;
  	     	uWS::WebSocket<uWS::CLIENT> mWS;
	public:
		mysock();
		~mysock();
		void onMessage(uWS::WebSocket<uWS::CLIENT> ws, char *message, size_t length);
		void sendMessage(char *msg, size_t length);
		static void * run_web_socket(void* ptr){
			mysock *obj = (mysock*) ptr;
			obj->mClient.run();
		}
	
};

mysock::mysock(){
	this->mClient.onConnection([this](uWS::WebSocket<uWS::CLIENT> ws, uWS::UpgradeInfo ui){ 
		this-> mWS = ws;
		printf("connected\n");
	 });
	this->mClient.onError([this](void* user){ printf("Failed %s\n", (char*)user); });
	this->mClient.onMessage([this](uWS::WebSocket<uWS::CLIENT> ws, char *message, size_t length, uWS::OpCode opCode){ this->onMessage(ws, message, length); });
	this->mClient.onDisconnection([this](uWS::WebSocket<uWS::CLIENT> ws, int code, char* message, size_t length){ printf("%s\n", message); });
	this->mClient.connect("ws://echo.websocket.org",NULL);
	pthread_t clientRun;
	pthread_create(&clientRun,NULL,run_web_socket,this);
}

mysock::~mysock(){

}

void mysock::onMessage(uWS::WebSocket<uWS::CLIENT> ws, char *message, size_t length){
	printf("Message from server is: %s\n", message);	
}

void mysock::sendMessage(char *msg, size_t length){
	printf("Sending message\n");
	this->mWS.send(msg, length, uWS::OpCode::TEXT);
	printf("Message sent\n");
}

int main(int argc, char** argv){
	char msg[] = "Hai this is naveen";
	mysock *obj = new mysock();
	sleep(5);
	obj->sendMessage(msg,strlen(msg));
	printf("Message Sent to server\n");
	return 0;
}
