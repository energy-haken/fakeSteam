#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#define PORT "8080"
#define BUFFER_SIZE 1024

// Fonction pour envoyer une requête et obtenir une réponse 
void send_request_and_get_response(const char* request, char* response) {
    int sock = 0;
    struct addrinfo hints, *res;
    
    char buffer[BUFFER_SIZE];

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;  // IPv4 ou IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP

    // Adresse du serveur
    if (getaddrinfo("127.0.0.1", PORT, &hints, &res) != 0) {
        fprintf(stderr, "getaddrinfo failed\n");
        exit(-1);
    }

    // Création du socket
    sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock < 0) {
        fprintf(stderr, "Socket creation error\n");
        freeaddrinfo(res);
        exit(-1);
    }

    // Connexion au serveur
    if (connect(sock, res->ai_addr, res->ai_addrlen) < 0) {
        fprintf(stderr, "Connection failed\n");
        close(sock);
        freeaddrinfo(res);
        exit(-1);
    }

    freeaddrinfo(res);

    // Envoi de la requête
    sprintf(buffer, "%s", request);
    if (send(sock, buffer, strlen(buffer), 0) < 0) {
        close(sock);
        printf("Sending to server...FAILED\n");
        exit(-1);
    }

    sleep(1); 
    printf("Sending to server...DONE\n");

    // Lire la réponse du serveur
    memset(response, 0, BUFFER_SIZE);
    read(sock, response, BUFFER_SIZE);
    
    // Fermer le socket
    close(sock);
}

int main() {
    char response_buffer[BUFFER_SIZE];
    
    // Envoi de la requête count pour savoir s'il y a des jeux avant de faire appel à list
    printf("Sending count request to server...\n");
    send_request_and_get_response("count:", response_buffer);

    // Convertir la réponse en entier
    int game_count = atoi(response_buffer);
    sleep(1);

    // S'il y a des jeux, envoyer la requête liste pour afficher
    if (game_count > 0) {
        printf("Sending list request to server...\n");
        send_request_and_get_response("list:", response_buffer);
        printf("List of games:\n%s\n", response_buffer);
    } else {
        printf("No games available\n");
    }

    return 0;
}
