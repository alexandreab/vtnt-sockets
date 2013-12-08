# Makefile for the socket programming example
#
STD_FLAGS = -W -Wall -ansi -pedantic
VTNT_FLAGS = -W -Wall -ansi -pedantic -I. -pthread -std=gnu++0x -lwiringPi
HEARDERS = $(wildcard *.cpp)

simple_server_objects = ServerSocket.o Socket.o simple_server_main.o
simple_client_objects = ClientSocket.o Socket.o simple_client_main.o
sender_objects = ClientSocket.o Socket.o sender_main.o
sequencer_objects = ServerSocket.o Socket.o ClientSocket.o
destination_objects = ServerSocket.o Socket.o
messenger_objects = Socket.o ClientSocket.o

all : socket

socket: 
	g++ $(VTNT_FLAGS) -o prog ClientSocket.cpp ServerSocket.cpp Socket.cpp VTNTConnection.cpp
simple_server: $(simple_server_objects)
	g++ -o simple_server $(simple_server_objects)

clean:
	rm -f *.o simple_server simple_client sender sequencer destination prog
