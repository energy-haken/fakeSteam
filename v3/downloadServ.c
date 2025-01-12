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
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <CodeOp> <NomJeu> <URL>\n", argv[0]);
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

    // Génération du code aléatoire (*)
    unsigned int r;
    getrandom(&r, sizeof(r), GRND_NONBLOCK);
    r %= 1000;
    char code[1001];
    for (int i = 0; i < r; i++) {
        code[i] = '*';
    }
    code[r] = '\0';

    // Téléchargement du jeu
    printf("Downloading %s from %s...\n", argv[2], argv[3]);
    sleep(10);
    printf("Downloading %s from %s...DONE\n", argv[2], argv[3]);
    
    // Envoi de la requête "post" au serveur
    sprintf(buffer, "post:%s:%s", argv[2], code);
    printf("Sending to server...\n");
    send(sock, buffer, strlen(buffer), 0);
    
    // Initialisation du buffer pour la réponse du serv
    memset(response_buffer, 0, sizeof(response_buffer));

    // Lecture de la réponse
    read(sock, response_buffer, BUFFER_SIZE);

    // Messages selon la réponse du serv
    if (strcmp(response_buffer, "success") == 0) {
            sleep(10);
            printf("Sending to server...DONE\n");
    } else {
        printf("Sendind to server...FAILED\n");
    }

    close(sock);
    return 0;
}
