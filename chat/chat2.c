#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void* envoyer(void* arg)
{
    FILE* p1 = (FILE*)arg;
    char message[50];
    while (1)
    {
        printf("\nVous : ");
        fflush(stdout);
        if(fgets(message, sizeof(message), stdin)== NULL)
            continue;

        while(strcmp(message, "\n") == 0){
            printf("\nVous : ");
            fflush(stdout);
            if(fgets(message, sizeof(message), stdin)== NULL)
                continue;
        }
        fputs(message, p1);
        fflush(p1);

        if (strcmp(message, "exit\n") == 0){
            printf("\n\tdeconnexion...\n");
            sleep(2);
            exit(0);
        }

    }
    return NULL;
}

void* recevoire(void* arg)
{
    char message[50];
    FILE* tmp = fopen("fichier1.txt", "w+");
    if (tmp == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(-1);
    }
    long currentPos = ftell(tmp);
    while (1)
    {
        fseek(tmp, 0, SEEK_END);
        long fileSize = ftell(tmp);
        if (fileSize > currentPos)
        {
            fseek(tmp, currentPos, SEEK_SET);
            if (fgets(message, sizeof(message), tmp) != NULL)
            {
                if(strcmp(message,"exit\n")==0){
                    printf("\n\tUser 1 est deconnecte...\n");
                    sleep(4);
                    exit(0);
                }
                printf("\n  User 1: %s\nVous : ", message);
                fflush(stdout);
            }
            currentPos = ftell(tmp);
        }
        struct timespec sleepTime = {0, 100000000};
        nanosleep(&sleepTime, NULL);
    }
    fclose(tmp);
    return NULL;
}

int main()
{
    FILE* p1 = fopen("fichier2.txt", "w");
    pthread_t thread_envoyer, thread_recevoire;
    printf("\n\t PROGRAMME CHAT 2 : [Entrer 'exit' pour sortir du programme]\n");
    if (p1 == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(-1);
    }

    pthread_create(&thread_envoyer, NULL, envoyer, (void*)p1);
    pthread_create(&thread_recevoire, NULL, recevoire, NULL);

    pthread_join(thread_envoyer, NULL);
    pthread_join(thread_recevoire, NULL);

    fclose(p1);

    return 0;
}
