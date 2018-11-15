#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <uWS/uWS.h>
#include <pthread.h>


class IDSWebSocket{
	private:
		uWS::Hub *hub;
		uWS::WebSocket<uWS::CLIENT> mWS;
		pthread_t webSocketThread;
	public:
		int connected;
		IDSWebSocket();
		~IDSWebSocket();
		void createConnection();
		void startConnection();
		static void* run_create_connection(void* ptr){
			IDSWebSocket *webSocket = (IDSWebSocket*) ptr;
			webSocket->startConnection();
		}
		void destroyConnection(){
			pthread_cancel(webSocketThread);
			free(hub);
			connected = false;
		}
	
		void sendMessage(char* buffer, int length);
};
	
IDSWebSocket::IDSWebSocket(){
	connected = false;
}

IDSWebSocket::~IDSWebSocket(){
	destroyConnection();
}

void IDSWebSocket::createConnection(){
	hub = new uWS::Hub();
	hub->onConnection([this](uWS::WebSocket<uWS::CLIENT> ws, uWS::UpgradeInfo ui){
		printf("Connection established... \n");
		this->mWS = ws;
		this->connected = true;
	});
	
	hub->onMessage([this](uWS::WebSocket<uWS::CLIENT> ws, char* message, size_t length, uWS::OpCode opCode){
		this->mWS = ws;
		char buffer[length] = {0};
		memcpy(buffer, message, length);
		printf("Message from server: %s\n", buffer);
	});
	hub->onDisconnection([this](uWS::WebSocket<uWS::CLIENT> ws, int code, char* message, size_t length){
		printf("Disconnected...\n");
		this->connected = false;
	});
	hub->connect("ws://localhost:3000", NULL);
	pthread_create(&webSocketThread, NULL, run_create_connection, this);
	sleep(5);
}

void IDSWebSocket::startConnection(){
	this->hub->run();
}

void IDSWebSocket::sendMessage(char* buffer, int length){
	mWS.send(buffer, length, uWS::OpCode::TEXT);
}


int main(int argc, char** argv){
	IDSWebSocket *webSocket = new IDSWebSocket();
	webSocket->createConnection();
	char buffer[] = "hai this is naveen";
	while(1){
		if(webSocket->connected == true){
			webSocket->sendMessage(buffer, strlen(buffer));
			printf("Sent...\n");
			sleep(1);
		} else {
			sleep(2);
			printf("Reconnecting...\n");
			free(webSocket);
			sleep(1);
			webSocket = new IDSWebSocket();
			webSocket->createConnection();
		}
	}
	return 0;
}
