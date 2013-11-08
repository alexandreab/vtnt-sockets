#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
//Biblioteca que possui funcoes pre determinadas para criacao de sockets
#include <sys/socket.h>

// Definindo a porta que será utilizada pelo socket TCP
#define PORTNUM 5137

int main(int argc, char *argv[])
{
    //Criacao de duas estruturas de sockets, contendo o servidor e o cliente que vai conectar no servidor
    struct sockaddr_in clientInfo;
    struct sockaddr_in serverInfo;
    //Criando contadores, IDS de mensagens e um inteiro que sera utilizado com backup 
    int serverSocket, writerSocket,index,temp[2],backup;
    //Criando um char que vai enviar um comando para o servidor e um char que vai enviar a resposta de volta
    char command[1024],buffer[1024];

    //Definindo toda a estrutura do socket do servidor, passando os parametros do proprio Raspberry
    socklen_t socksize;
    socksize = sizeof(struct sockaddr_in);
    memset(&serverInfo, 0, sizeof(serverInfo));
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(PORTNUM);

    //Criando o socket do servidor e "bindando" a porta que foi definida anteriormente
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    bind(serverSocket, (struct sockaddr *)&serverInfo, sizeof(struct sockaddr));
    listen(serverSocket, 1);
    printf("Server initiatled. Listening on port %d \n",PORTNUM);
	
    //Esperando uma conexão até o cliente se conectar, quando se conectar ele aceita a conexao
    int connectionSocket = accept(serverSocket, (struct sockaddr *)&clientInfo, &socksize);
    while(connectionSocket){
    	//Quando um cliente se conecta ele espera o comando com a funcao read()
        printf("Client %s connected\n", inet_ntoa(clientInfo.sin_addr));
        connectionSocket = accept(serverSocket, (struct sockaddr *)&clientInfo, &socksize);
        writerSocket = read(serverSocket,(char *) command, 1024);
	while(writerSocket){
	        writerSocket = read(serverSocket,(char *) command, 1024);
		index = strlen(command) - 1;
		//funcao condicional que vai separar os comandos atraves de um espaco ["Enter"]
		if (command[index] == '\n'){
                        command[index] = '\0';
                        // Definicao dos comandos que o socket vai responder, no caso inicial so temos esses dois comandos
			if (strncmp(command, "ola ", 2) == 0){ 
                        	printf("Client send Hello Message: %s\n",command);
               		}else if(strcmp(command,":logoff") == 0){
                           	writerSocket = write(serverSocket, (void *) "Closing connection\n", 18);
                           	close(connectionSocket);
                            	close(serverSocket);
                   	    	printf ("Connection Closed!\n");
                    	    	exit(0);
			}
		}else{
		    //Devolvendo o retorno do comando digitado para o cliente através da chamada do sistema dup()
	            backup = dup(1);
                    close(0);
                    close(1);
                    pipe(temp);
                    system(command);
                    //Outra chamada de sistema para escrever a resposta para o cliente
                    dup2(backup,1);
                    //Escreve a resposta no socket
                    while (fgets(buffer, 1024, stdin)){
                        writerSocket=write(serverSocket,(void *)buffer,strlen(buffer));
		    }
		}
	}
    }
    //Fechando os sockets e "matando" a conexao
    close(connectionSocket);
    close(serverSocket);
    exit(0);
}
