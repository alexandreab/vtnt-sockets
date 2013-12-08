#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <thread>

using namespace std;

void socketSend(void);
void socketReceive(void);

int main ( int argc, char* argv[] )
{
  std::cout << "running....\n";

  thread receive;
  thread send;

  receive = thread(socketReceive);
  send = thread(socketSend);

  receive.join();
  send.join();
  

	return 0;
}


void socketReceive(void)
{
	cout << "Inicio do socket receive" << endl;
	try
	{
	  	// Create the socket
		ServerSocket server(5138);

	  	while(true)
		{
			ServerSocket new_sock;
			server.accept(new_sock);

			try
			{
				cout << "Vou receber os dados" << endl;
				while(true)
				{
					std::string data;
					new_sock >> data;
					cout << "Recebido: " << data << endl;
					//Fal algo
				}
		    }
		  	catch ( SocketException& ) {}
		}
	}
  	catch ( SocketException& e )
    {
    	std::cout << "Send Exception was caught:" << e.description() << "\nExiting.\n";
    }
}

void socketSend(void)
{
	cout << "Inicio do socket send" << endl;
	try
	{
	  	// Create the socket
		ServerSocket server(5137);

	  	while(true)
		{
			ServerSocket new_sock;
			server.accept(new_sock);

			try
			{
				while(true)
				{
					std::string data;
					data = "tudo";
					//Coloca coordenadas, bateria e detecao em data
					new_sock << data;
					sleep(2);
				}
		    }
		  	catch ( SocketException& ) {}
		}
	}
  	catch ( SocketException& e )
    {
    	std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
}
