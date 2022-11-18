/*Sophia Carlone 11-18-22*/
// #include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h> //constants

#define PORT 8050 
#define ADDRESS = "127.0.0.1" //local host
#define BUFFER = 1024 //size of packet
#define QUEUE = 4 //amount of connections that can be waiting in the socket

int main(){
    int read_packet, send_packet;
    //later for getting stdin
    size_t len = 0;
    ssize_t line_size = 0; 
    
    struct sockaddr_in address; //struct used to initialize address
    //I find having two different packets more readable
    char *recv_packet[buffer]; //recieving packet
    char *send_packet[buffer]; //sent packet
    
    address.sin_family = AF_INET; //IPv4
    address.sin_addr.s_addr = ADDRESS;
    address.sin_port = htons(PORT); 

    //create socket for clients/possible connections
    //AF_INET = IPv4
    //SOCK_STREAM = tcp
    int client_list_socket = socket(AF_INET, SOCK_STREAM, 0); 

    //bind socket to address
    int bind(client_list_socket, (struct sockaddr_in*) &address, sizeof(address));
    
    //listen
    int listen(client_list_socket, QUEUE);

    //accept first connection on queue and make new socket from it
    int current_socket = accept(client_list_socket, (struct sockaddr_in*) &address, sizeof(address));    

    while(1){
        //read what is comming from the current socket's packet 
        read_packet = read(current_socket, recv_packet, BUFFER);
        printf("%s\n", packet); 
        
        //send
        line_size = getline(&send_packet, &len, stdin);
        send_packet = send(current_socket, send_packet, BUFFER);
        free(send_packet);
    }
    
    //socket close
    return 0;
}