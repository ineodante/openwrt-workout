SERVER_SRC=server.cc
SERVER=server
CLIENT_SRC=client.cc
CLIENT=client
LIBS=-luWS -lpthread -lz -std=c++11

all:
	$(CXX) $(SERVER_SRC) -o $(SERVER) $(LIBS)
	$(CXX) $(CLIENT_SRC) -o $(CLIENT) $(LIBS)

clean:
	rm -rf $(SERVER) $(CLIENT)
