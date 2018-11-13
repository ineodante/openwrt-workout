#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <uWS/uWS.h>

int main(int argc, char** argv){
	uWS::Hub hub;
	hub.onMessage([](uWS::WebSocket<uWS::SERVER> ws, char *message,size_t length, uWS::OpCode opCode){
		char buffer[length] = {0};
		memcpy(buffer, message, length);
		printf("Message received: %s\n", buffer);
		ws.send(buffer,length,opCode);	
	});
	hub.listen(3000);
	hub.run();

}
