// Q2 Bakhshande
// type make in shell and see the resault

#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <wait.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <pthread.h>
#include <string.h>

#define IN_LEN 5
#define PIPE_NO 1
#define CHAR_SIZE 150


int main()
{

    char inputs[IN_LEN][CHAR_SIZE];
    char outputs[IN_LEN][CHAR_SIZE];
    int pipes[PIPE_NO][2]; int pid;

    FILE *file = fopen("logs.txt", "w");
    if (file == NULL)
    {
        perror("error could not open file\n");
    }

    // create pipes
    for (size_t i = 0; i < PIPE_NO; i++)
    {
        if (pipe(pipes[i]) == -1) 
        {
            printf("error creating pipe\n");
        }
    }

    pid = fork();

    if (pid > 0) // parent process
    {
        pid_t pid_new = fork();

        if (pid_new > 0)
        {
            for (int i = 0; i < 3; i++)
            {
                char temp[CHAR_SIZE];
                sprintf(temp, "(%d) => log (%d)", i, rand() % 101);
                strcpy(inputs[i], temp);
                printf("%s \n\n", inputs[i]);
            }
            for (int i = 0; i < 3; i++)
            {
                write(pipes[0][1], &inputs[i], sizeof(char) * CHAR_SIZE);
            }
        }
        else if (pid_new == 0)
        {
            for (int i = 3; i < 5; i++)
            {
                char temp[CHAR_SIZE];
                sprintf(temp, "(%d) => log (%d)", i, rand() % 101);
                strcpy(inputs[i], temp);
                printf("%s \n\n", inputs[i]);
            }

            for (int i = 3; i < 5; i++)
            {
                write(pipes[0][1], &inputs[i], sizeof(char) * CHAR_SIZE);
            }
        }
        else
        {
            perror("NO Child!");
        }
    }

    // child
    else if (pid == 0)
    {
        for (size_t i = 0; i < IN_LEN; i++)
        {
            read(pipes[0][0], &outputs[i], sizeof(char) * CHAR_SIZE);
            printf("RECIEVED: %s\n\n", outputs[i]);
            fprintf(file, "%s\n", outputs[i]);
        }
    }

    else
    {
        perror("No child!");
    }
}
