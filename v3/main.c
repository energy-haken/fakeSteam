#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "common.h"
#include "structures.h"
#include "operationsUtils.h"
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024


Jeu jeux[20];
int nb_jeux = 0;

bool prefix(const char *pre, const char *str)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}

void* handleRequest(void* arg) {
    int new_socket = *((int*) arg);
    char buffer[BUFFER_SIZE];
    // Lire le message depuis le client
    memset(buffer, 0, sizeof(char) * BUFFER_SIZE);
    int valread = read(new_socket, buffer, BUFFER_SIZE);
    if (valread < 0) {
        perror("read failed");
    }

    char response_buffer[5096];
    sprintf(response_buffer, "no_such_operation");

    char* argt = strchr(buffer, ':');
    argt++;

    // GESTION DU MESSAGE
    if (prefix("count:", buffer)) {
        sprintf(response_buffer, "%d", nb_jeux);
    }
    if (prefix("list:", buffer)) {
        list(jeux, nb_jeux, response_buffer);
    }
    if (prefix("exists:", buffer)) {
        if (exists(jeux, nb_jeux, argt)) {
            sprintf(response_buffer, "true");
        } else {
            sprintf(response_buffer, "false");
        }
    }
    if (prefix("get:", buffer)){
        int index = get_index(jeux, nb_jeux, argt);
        if (index != -1) {
            sprintf(response_buffer, "%s", jeux[index].Code);
        } else {
            sprintf(response_buffer, "no_such_game");
        }
    }
    if (prefix("delete:", buffer)){
        if (delete(jeux, &nb_jeux, argt) == -1) {
            sprintf(response_buffer, "no_such_game");
        } else {
            sprintf(response_buffer, "success");
        }
    }
    if (prefix("post:", buffer)){
        char* code = strchr(argt, ':');
        *code = 0;
        code++;
        if (exists(jeux, nb_jeux, argt)) {
            sprintf(response_buffer, "game_already_exists");
        } else {
            Jeu new_game;
            strcpy(new_game.NomJeu, argt);
            strcpy(new_game.Code, code);
            jeux[nb_jeux++] = new_game;
            sprintf(response_buffer, "success");            
        }
    }
    send(new_socket, response_buffer, strlen(response_buffer) + 1, 0);
    // Fermer le socket pour cette connexion
    close(new_socket);
    return NULL;
}

int main() {

    //end of debug test
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // Création du socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Attachement du socket au port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Attachement du socket à l'adresse et au port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Écouter les connexions
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Écoute sur le port %d...\n", PORT);

    while (1) {
        // Accepter une connexion entrante
        int new_socket;
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            continue; // Continuer la boucle pour accepter une nouvelle connexion
        }
        pthread_t handleRequestThread;
        pthread_create(&handleRequestThread, NULL, handleRequest, (void*)(&new_socket));
    }

    close(server_fd);
    return 0;
}
