#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <thread>

#include <stdio.h>
#include <wiringPi.h>

#define	I1	0	// 17
#define	I2	1	// 18
#define I3  2
#define I4  3


using namespace std;

void move(string data);
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
					move(data);
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

void move(string data)
{
  wiringPiSetup () ;
  //MOTOR 1
  pinMode (I1, OUTPUT);
  pinMode (I2, OUTPUT);
  //MOTOR 2
  pinMode (I3, OUTPUT);
  pinMode (I4, OUTPUT);

  digitalWrite (I1, LOW) ;	// Off
  digitalWrite (I2, LOW) ;	// Off
  digitalWrite (I3, LOW) ;	// Off
  digitalWrite (I4, LOW) ;	// Off

  delay (500) ;		// mS

  	if(data=="pause")
  	{
  	 	//printf("\nParando o motor...");
  	 	digitalWrite (I1, LOW) ;	// Off
  	 	digitalWrite (I2, LOW) ;	// Off
  	 	digitalWrite (I3, LOW) ;	// Off
  	 	digitalWrite (I4, LOW) ;	// Off
  	}
  	else if(data=="forward")
  	{
  	 	printf("\nGirando o motor no sentido horario...");
  	 	digitalWrite (I1, LOW) ;	// Off
  		digitalWrite (I2, LOW) ;	// Off
  		digitalWrite (I3, LOW) ;	// Off
  		digitalWrite (I4, LOW) ;	// Off

  		delay (500) ;			// mS
  		
      digitalWrite (I1, HIGH) ;	// On
		  digitalWrite (I3, HIGH) ;
  	}
  	else if(data=="reverse")
  	{
  	 	printf("\nGirando o motor no sentido antihorario...");
  	 	digitalWrite (I1, LOW) ;	// Off
  		digitalWrite (I2, LOW) ;	// Off
  		digitalWrite (I3, LOW) ;	// Off
  		digitalWrite (I4, LOW) ;	// Off
  		
      delay (500) ;			// mS
  		
      digitalWrite (I2, HIGH) ;	// On
		  digitalWrite (I4, HIGH) ;
  	}
	else if(data=="to_left")
	{
  		digitalWrite (I1, LOW) ;	// Off
  		digitalWrite (I2, LOW) ;	// Off
  		digitalWrite (I3, LOW) ;	// Off
  		digitalWrite (I4, LOW) ;	// Off
		
      delay (500);
  		
      digitalWrite (I1,HIGH) ;	// On
	}
	else if(data=="to_right")
	{
		  digitalWrite (I1, LOW) ;	// Off
  		digitalWrite (I2, LOW) ;	// Off
  		digitalWrite (I3, LOW) ;	// Off
  		digitalWrite (I4, LOW) ;	// Off
		  
      delay(500);
  		
      digitalWrite (I3, HIGH) ;	// On
	}
}
