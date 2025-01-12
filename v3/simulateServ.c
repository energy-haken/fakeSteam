#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "common.h"
#include "structures.h"
#include "operationsUtils.h"
#include <netdb.h>

#define PORT "8080"
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <NomJeu>\n", argv[0]);
        return 1;
    }

    int sock = 0;
    struct addrinfo hints, *res;
    char buffer[BUFFER_SIZE];
    char response_buffer[BUFFER_SIZE];

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;  // IPv4 ou IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP

    // Adresse du serveur
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

    // Envoi de la requête "get" au serveur
    sprintf(buffer, "get:%s", argv[1]);
    printf("Sending server...\n");
    send(sock, buffer, strlen(buffer), 0);

    // Initialisation du buffer pour la réponse du serveur
    memset(response_buffer, 0, sizeof(response_buffer));

    // Lecture de la réponse
    read(sock, response_buffer, BUFFER_SIZE);

    if (strcmp(response_buffer, "no_such_game") == 0) {
        printf("Game '%s' not found on the server.\n", argv[1]);
    } else {
        printf("Sending server...DONE\n");

        // Simulation du jeu
        printf("Simulating game '%s'...\n", argv[1]);
        char *memory = malloc(strlen(response_buffer) + 1);
        strcpy(memory, response_buffer);
        sleep(20);
        if (rand() % 2 == 0) {
            printf("Le gagnant du Jeu %s est A.\n", argv[1]);
        } else {
            printf("Le gagnant du Jeu %s est B.\n", argv[1]);
        }
        free(memory);
        printf("Game '%s' simulated successfully.\n", argv[1]);
    }

    close(sock);
    return 0;
}
