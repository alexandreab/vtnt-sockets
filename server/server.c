#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>


#define PORTNUM 5137

int main(int argc, char *argv[])
{
    struct sockaddr_in clientInfo;
    struct sockaddr_in serverInfo;
    int serverSocket, writerSocket,index,temp[2],backup;
    char command[1024],buffer[1024];

    socklen_t socksize;
    socksize = sizeof(struct sockaddr_in);
    memset(&serverInfo, 0, sizeof(serverInfo));
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(PORTNUM);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    bind(serverSocket, (struct sockaddr *)&serverInfo, sizeof(struct sockaddr));
    listen(serverSocket, 1);
    printf("Server initiatled. Listening on port %d \n",PORTNUM);

    int connectionSocket = accept(serverSocket, (struct sockaddr *)&clientInfo, &socksize);

    while(connectionSocket){
        printf("Client %s connected\n", inet_ntoa(clientInfo.sin_addr));
        //connectionSocket = accept(serverSocket, (struct sockaddr *)&clientInfo, &socksize);
        writerSocket = read(serverSocket,(char *) command, 1024);
	while(writerSocket){
	        //writerSocket = read(serverSocket,(char *) command, 1024);
		index = strlen(command) - 1;
		if (command[index] == '\n'){
                        command[index] = '\0';
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
	            backup = dup(1);
                    close(0);
                    close(1);
                    pipe(temp);
                    system(command);
                    dup2(backup,1);
                    while (fgets(buffer, 1024, stdin)){
                        writerSocket=write(serverSocket,(void *)buffer,strlen(buffer));
		    }
		}
	}
    }
    close(connectionSocket);
    close(serverSocket);
    exit(0);
}
