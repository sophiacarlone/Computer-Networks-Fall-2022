/*Sophia Carlone 11-18-22*/
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h> //constants

#define PORT 8050 
#define BUFFER 1024 //size of packet
#define QUEUE 2 //number of connections that can be established

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
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT); 

    //create socket for clients/possible connections
    //AF_INET = IPv4
    //SOCK_STREAM = tcp
    int client_list_socket = socket(AF_INET, SOCK_STREAM, 0); //TODO error handling 

    //bind socket to address
    int bonded = bind(client_list_socket, (struct sockaddr*) &address, sizeof(address));
    
    //listen
    int throwaway = listen(client_list_socket, QUEUE);

    //accept first connection on queue and make new socket from it
    int current_socket = accept(client_list_socket, (struct sockaddr*) &address, (socklen_t*) &address);    

    while(ON){
        //read what is comming from the current socket's packet 
        read_packet = read(current_socket, recv_packet, BUFFER);
        printf("%s\n", recv_packet); 

        // if(recv_packet[0] == 'q' && read_packet[1] == '\0') ON = 0;

        //send packet which is from stdin
        line_size = getline(&send_packet, &len, stdin);
        send(current_socket, send_packet, BUFFER, 0);
        free(send_packet); //refresh input
    }
    close(current_socket);   
    //socket close
    return 0;
}