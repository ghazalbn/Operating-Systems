//Q1

#include <stdio.h> 
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>  
#include <unistd.h> 
#include <fcntl.h>

int main(int argc, char **argv)
{    

    struct stat check;
    int fileP, code;
    
    if (argc < 3)
    {
        printf("Usage: ./redirect <program> <file> <program arguments>\n");
        exit(EXIT_FAILURE);
    }

    if ((stat(argv[1], &check) < 0))
    {
        printf("Program path is invalid\n");
        exit(EXIT_FAILURE);
    }

    if (S_ISDIR(check.st_mode))
    {
        printf("This is a directory not a file\n");
        exit(EXIT_FAILURE);
    }

    if (!(check.st_mode & S_IXUSR))
    {
        printf("Given file is not executable\n");
        exit(EXIT_FAILURE);
    }

    fileP = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC , S_IRUSR | S_IWUSR);
    char **childArgv = argv + 2;
    childArgv[0] = argv[1];

    pid_t pid = fork();
    if (pid == -1)
    {
        printf("creating a new process failed\n");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        dup2(fileP, 1); //STDOUT
        dup2(fileP, 2); //STDERR
        close(fileP);
        execv(argv[1], childArgv);
    }
    wait(&code);
    printf("child rc: %d\n", code);
    
    return 0;
}