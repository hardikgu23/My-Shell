//
// Created by hardik on 05/10/21.
//

#include "header_files.h"

// tokenize commands by '|' and return number of tokens
int tokenize_pipe(char* command , char **args )
{

    // number of tokens
    int n = 0;

    // making copy of the command
    char *temp = (char *)malloc(sizeof(char)*1024);
    strcpy(temp , command);

    char *token = strtok(temp , "|");

    while(token != NULL)
    {
        args[n] = (char*)malloc(1024*sizeof(char));
        strcpy(args[n] , token);

        n++;
        token = strtok(NULL , "|");
    }
    return n;
}

void handle_pipeline(char *command)
{
    char **args1;
    // allocating args memory
    args1 = (char**)malloc(100*sizeof(char));
    int number_of_args = tokenize_pipe(command , args1);

    int pipe1[2] , pipe2[2] , fd = 0 , j =0;

    // checkpoint 1
//    printf("Number of arguments are \n");
//    for(int i=0;i<number_of_args;i++)
//        printf("%s\n" , args1[i]);

    for(int i=0;i<number_of_args;i++)
    {
        if(i%2 ==0)
        {
            if(pipe(pipe1) < 0)
            {
                perror("pipe");
            }
        }
        else
        {
            if(pipe(pipe2) < 0)
            {
                perror("pipe");
            }
        }

        pid_t pid = fork();

        if(pid < 0)
        {
            perror("Error in forking: ");
            return;
        }

        if(pid == 0) // child process
        {
            if(i%2 == 0) // pipe1
            {
                if(i!= 0)
                    dup2(pipe2[0] , STDIN_FILENO);
                if(i!= number_of_args-1)
                    dup2(pipe1[1] , STDOUT_FILENO);
            }
            else // pipe2
            {
                dup2( pipe1[0], STDIN_FILENO);
                if(i!= number_of_args-1)
                    dup2(pipe2[1] , STDOUT_FILENO);
            }

            // execute command // handle_redirection can execute both type of command (with and wothout redirection)
            handle_redirection(args1[i]);
            exit(0);
        }
        else // parent process
        {
            if(i%2 == 0)
            {
                if(i!= 0)
                    close(pipe2[0]);
                if(i!= number_of_args-1)
                    close(pipe1[1]);
            }
            else
            {
                close(pipe1[0]);
                if(i!= number_of_args-1)
                    close(pipe2[1]);
            }

            wait(NULL);
        }
    }



}