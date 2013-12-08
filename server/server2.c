#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//Biblioteca para pegar as informacoes de IP, porta, etc...
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
//Biblioteca que possui funcoes pre determinadas para criacao de sockets
#include <sys/socket.h>

// Definindo a porta que será utilizada pelo socket TCP


#define PORTNUM 5137

void command(char direction){
    
    switch(direction){
        case 'f':
            //TODO: function to move car forward
        case 'b':
            //TODO: function to move car back
        case 'l':
            //TODO: function to move car left
        case 'r':
            //TODO: function to move car right
        default:
            printf("Unknown direction");
            //TODO: make a exception
    }
}

char * simulation(){
      FILE *file = fopen("../simulation.txt", "rt");
      char values[100], *line;
      int i = 1;
      
      if (!file){
          printf("Unable to open file\n");
          return 0;
      }
      
      while (!feof(file)){
           line = fgets(values, 200,file); 
           if(line){
               printf("Coordenate %d : %s",i,values);
           }
           i++;
           sleep(1);
      }
      close(file);
 
}
int main(int argc, char *argv[])
{
    //Criacao de duas estruturas de sockets, contendo o servidor e o cliente que vai conectar no servidor
    struct sockaddr_in clientInfo;
    struct sockaddr_in serverInfo;
    //Criando contadores, IDS de mensagens e um inteiro que sera utilizado com backup 
    int serverSocket, writer, index, temp[2], backup, clientSocket;
    //Criando um char que vai enviar um comando para o servidor e um char que vai enviar a resposta de volta
    char command[1024],buffer[1024];

    //Definindo toda a estrutura do socket do servidor, passando os parametros do proprio Raspberry
    socklen_t socksize;
    socksize = sizeof(struct sockaddr_in);
    memset(&serverInfo, 0, sizeof(serverInfo));
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(PORTNUM);

    //Zerando o buffer de comando
    bzero(command,1024);
    //Criando o socket do servidor e "bindando" a porta que foi definida anteriormente
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    bind(serverSocket, (struct sockaddr *)&serverInfo, sizeof(struct sockaddr));
    listen(serverSocket, 1);
    printf("Server initiatled. Listening on port %d \n",PORTNUM);
    while(clientSocket  = accept(serverSocket, (struct sockaddr *)&clientInfo, &socksize)){
    	//Quando um cliente se conecta ele espera o comando com a funcao read()
        printf("Client %s connected\n", inet_ntoa(clientInfo.sin_addr));
        writer = write(clientSocket,(void *) "Welcome! Connected to VTNT!\n", 28);
        while(1){
          sleep(1);
          writer = write(clientSocket,(void *) "Enviando coordenada!\n", 24);
        }
    }
/*	
	    while(writer = read(clientSocket,(char *) command, 1024)){
	        index = strlen(command) - 1;
                if (command[index] == '\n'){
		            command[index] = '\0'; 
		            printf("comando recebido\n");
	    	        if(strncmp(command, "teste ", 5) == 0){
		                printf("Comando Teste recebido\n");
		                writer = write(clientSocket,(void *) "You send the test command!\n", 28);
		            } 
                //   else if(strncmp(command, "coordenates ", 10) == 0){
                //        simulation();
                //    }
	            }
	        memset(&command, 0, sizeof (command));
	    }
    }
    //Fechando os sockets e "matando" a conexao
    close(clientSocket);
    close(serverSocket);
    exit(0);*/
}
