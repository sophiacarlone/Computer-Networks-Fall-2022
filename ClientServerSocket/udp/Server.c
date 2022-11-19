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
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT); 

    //create socket for clients/possible connections
    //AF_INET = IPv4
    //SOCK_DGRAM = udp
    //0 = default protocol
    int client_list_socket = socket(AF_INET, SOCK_DGRAM, 0); //TODO error handling 

    //bind socket to address
    int bonded = bind(client_list_socket, (struct sockaddr*) &address, sizeof(address));

    while(ON){
        //read what is comming from the current socket's packet 
        int last = recvfrom(client_list_socket, recv_packet, BUFFER, MSG_WAITALL, (struct sockaddr*) &address, (socklen_t*) &address);
        printf("%s\n", recv_packet); 

        // if(recv_packet[0] == 'q' && read_packet[1] == '\0') ON = 0;
        printf("hit\n");
        //send packet which is from stdin
        line_size = getline(&send_packet, &len, stdin);
        sendto(client_list_socket, send_packet, BUFFER, MSG_CONFIRM,(struct sockaddr*) &address, sizeof(address));
        printf("sent");
        free(send_packet); //refresh input
    }
    close(client_list_socket);   
    //socket close
    return 0;
}