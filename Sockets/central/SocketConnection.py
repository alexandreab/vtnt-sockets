import socket
from threading import Thread
import time

class SocketConnection:

    host = ''
    coordinates_port = 5137
    command_port = 5138
    data = "nada"


    def __init__(self,host):
        self.connect(host)
        self.start_communication()

    def connect(self,host):
        HOST = host

        #Coordinates connection
        self.tcp_coord = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.dest = (HOST, self.coordinates_port)
        self.tcp_coord.connect(self.dest)

        #Command connection
        self.tcp_comm = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.dest = (HOST, self.command_port)
        self.tcp_comm.connect(self.dest)

    def start_communication(self):
        th_data = Thread( target=self.receive_data, args=())
        th_data.start()
        

    def receive_data(self):
        while True:
            data = self.tcp_coord.recv(1024)
            self.set_data(data)

    def set_data(self,data):
        self.data = data

    def send_command(self,command):
        data = self.tcp_comm.send(command)

    def disconnect(self):
        self.tcp_coord.close()
        self.tcp_comm.close()


if __name__=="__main__":
    print "instanciando"
    conexao = SocketConnection("localhost")

    conexao.start_communication()

    for i in range(1,100):
        print conexao.data
        time.sleep(0.5)


    print "desconectando"
    conexao.disconnect();

    print "fim"
