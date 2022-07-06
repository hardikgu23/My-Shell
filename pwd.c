#include "header_files.h"
void pwd()
{
    char *buff = getcwd(NULL , 0);
    if(buff == NULL)
    {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    printf("%s\n" , buff);
    free(buff);
}