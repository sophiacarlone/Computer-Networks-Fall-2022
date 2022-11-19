/*Sophia Carlone 11-18-22*/

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h> //constants

#define PORT 8050 
#define BUFFER 1024 //size of packet

int main(){
    int ON = 1; //connection on

    int read_packet;
    //later for getting stdin
    size_t len = 0;
    ssize_t line_size = 0; 
    
    struct sockaddr_in address; //struct used to initialize address
    //I find having two different packets more readable
    char *recv_packet[BUFFER]; //recieving packet
    char *send_packet; //sent packet

    address.sin_family = AF_INET; //IPv4
    address.sin_addr.s_addr = INADDR_ANY; //TODO change to local host later
    address.sin_port = htons(PORT); 

    //create socket for clients/possible connections
    //AF_INET = IPv4
    //SOCK_STREAM = tcp
    int server_socket = socket(AF_INET, SOCK_STREAM, 0); //TODO error handling 

    //connect to server
    int throwaway = connect(server_socket, (struct sockaddr*)&address, sizeof(address));
    // connect(server_socket, (struct sockaddr_in*) &address, sizeof(address));

    while(ON){
        //send packet that is from stdin
        line_size = getline(&send_packet, &len, stdin);
        send(server_socket, send_packet, BUFFER, 0); //socket, packet, size, flag
        free(send_packet);

        //read packet
        read_packet = read(server_socket, recv_packet, BUFFER);
        printf("%s\n", recv_packet); 

        // if(recv_packet[0] == 'q' && read_packet[1] == '\0') ON = 0;
    }

    close(server_socket);
}
