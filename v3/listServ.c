#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/random.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "operationsUtils.h"
#include "common.h"

#define PORT "8080"
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    int sock = 0;
    struct addrinfo hints, *res;
    char buffer[BUFFER_SIZE];
    char response_buffer[BUFFER_SIZE];

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;  // IPv4 ou IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP

    // Adresse du serv
    if (getaddrinfo("127.0.0.1", PORT, &hints, &res) != 0) {
        fprintf(stderr, "getaddrinfo failed\n");
        return -1;
    }

    // Création du socket
    sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock < 0) {
        fprintf(stderr, "Socket creation error\n");
        freeaddrinfo(res);
        return -1;
    }

    // Connexion au serveur
    if (connect(sock, res->ai_addr, res->ai_addrlen) < 0) {
        fprintf(stderr, "Connection failed\n");
        close(sock);
        freeaddrinfo(res);
        return -1;
    }

    freeaddrinfo(res);

    // Envoi de la requête "list" au serveur
    sprintf(buffer, "list:");
    printf("Sending to server...\n");
    send(sock, buffer, strlen(buffer), 0);
    sleep(1);
    printf("Sending to server...DONE\n");
    // Initialisation du buffer pour la réponse du serv
    memset(response_buffer, 0, sizeof(response_buffer));

    // Lecture de la réponse
    read(sock, response_buffer, BUFFER_SIZE);

    printf("List of games:\n%s\n", response_buffer);
    

    close(sock);
    return 0;
}
