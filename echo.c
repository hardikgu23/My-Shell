//
// Created by hardik on 14/09/21.
//

#include "header_files.h"


void echo(char *command)
{
    char *token = strtok(command , " \"\n\t\r");
    if(token == NULL)
        return;

    token = strtok(NULL , " \"\n\t\r");

    while(token != NULL)
    {
        printf("%s " , token);
        token = strtok(NULL , " \n\t\r\"");
    }
    printf("\n");

}
