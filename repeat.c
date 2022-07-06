#include "header_files.h"
void repeat(char ** args , int no_of_args)
{
    char *command;
    if(no_of_args < 3)
    {
        printf("Too less arguments");
        return;
    }

    int n = atoi(args[1]);

    command = (char*)malloc(1024*sizeof(char));

    strcpy(command , args[2]);

    for(int i=3;i<no_of_args;i++)
    {
        strcat(command , " ");
        strcat(command , args[i]);
    }

    // executing the command n times
    for(int i=0;i<n;i++)
    {
        char *temp;
        temp = (char*)malloc(sizeof(char)*1024);
        strcpy(temp , command);
        commandHandler(temp);
//        free(temp);
    }
}