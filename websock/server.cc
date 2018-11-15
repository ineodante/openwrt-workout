#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <uWS/uWS.h>

int main(int argc, char** argv){
	uWS::Hub mHub;
	mHub.onConnection([](uWS::WebSocket<uWS::SERVER> ws, uWS::UpgradeInfo ui){
		printf("Connection from client\n");
	});
	
	mHub.onMessage([](uWS::WebSocket<uWS::SERVER> ws, char* message, size_t length, uWS::OpCode opCode){
		char buffer[length] = {0};
		memcpy(buffer, message, length);
		buffer[length]= '\0';
		printf("Message received from the client: %s\n", buffer);
		ws.send(buffer, length, opCode);
	});
	
	mHub.listen(3000);
	mHub.run();
	return 0;
}
