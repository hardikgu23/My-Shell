#include "header_files.h"
void cd(char** args , int no_of_args)
{
    if(no_of_args > 2)
    {
        printf("Error: Too many arguments\n");
        return;
    }

    // if we are given only cd
    if(no_of_args == 1)
    {
        if(chdir(home_dir) != 0)
        {
            perror("Error in cd: ");
        }
    }
    // if path given is relative to home_dir
    else if(args[1][0] == '~')
    {
        char *path;
        path = (char*)malloc(sizeof(char)*2000);

        strcpy(path , home_dir);

        if(strlen(args[1]) > 1)
        strcat(path , &args[1][1]);

        if(chdir(path) != 0)
        {
            perror("Error in cd: ");
        }
    }
    else
    {
        if(chdir(args[1]) != 0)
        {
            perror("Error in cd: ");
        }
    }
}