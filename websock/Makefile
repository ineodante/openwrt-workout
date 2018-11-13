
all:
	$(CXX) demo.cc -o demo -std=c++11 -luWS -lz -lpthread
	$(CXX) server.cc -o server -std=c++11 -luWS -lpthread -lz
	$(CXX) client.cc -o client -std=c++11 -luWS -lpthread -lz

clean:
	rm -rf demo server client
