//
// Created by hardik on 10/10/21.
//
#include "header_files.h"

void replay(char **args , int no_of_args)
{

    if(no_of_args <= 6)
    {
        printf("Invalid no of arguments:");
        return;
    }

    char *command;
    command = (char*)malloc(sizeof(char)*1024);

    strcpy(command , args[2]);

    for(int i=0;i<no_of_args;i++)
    {
        if(strcmp(args[i] , "-command") == 0)
        {
            strcpy(command , args[i+1]);
            int a = i+2;
            while(a < no_of_args)
            {
                if(strcmp(args[a] , "-period") == 0)
                {
                    break;
                }
                if(strcmp(args[a] , "-interval") == 0)
                {
                    break;
                }

                    strcat(command , " ");
                    strcat(command , args[a]);
                    a++;
            }
        }
    }

    int interval = -1 , total_time = -1;

    for(int i=0;i<no_of_args;i++)
    {
        if(strcmp(args[i] , "-interval") == 0)
            interval = atoi(args[i+1]);
        if(strcmp(args[i] , "-period") == 0)
        {
            total_time = atoi(args[i+1]);
        }
    }

    if(interval == -1 || total_time == -1)
    {
        printf("Pls enter interval and period correctly\n");
        return ;
    }

    time_t start , end , absolute_start;
    double elapsed = 0;

    time(&start);
    absolute_start = start;
    time(&end);
    while(1)
    {
        time(&end);
        if(end-absolute_start > total_time)
            break;

        elapsed = difftime(end ,start);
        if(elapsed >= interval)
        {
            commandHandler(command);
            start = end;
        }
    }
}

