//
// Created by hardik on 19/09/21.
//
#include "header_files.h"

// this fxn tells if command is made of arrow keys , if yes then how many times arrow key was passed
int check_up_key(char *command)
{
    int len = strlen(command);
    int up = len/3;
    // if it is not multiple of 3 , then this is not entirely made of up commands
    //hence useless
    if(len %3 != 0)
        return -1;

    bool flag = true;
    for(int i=0;i<up;i++)
    {
        if(command[3*i] != '\033' || command[3*i+1] != '[' || command[3*i+2] != 'A')
        {
            flag = false;
            break;
        }
    }

    if(flag)
        return up;
    else
        return -1;

}

// this command executes the last numth command
void up_arrow(int num) // tells how many up we have to go
{
    int to_skip = hist_number - num;
    if(to_skip < 0)
        to_skip = 0;

    int x =0;
    // skip to_skip number of lines
    char a;

    // setting the pointer to the start
    fseek(hist_ptr , 0 , SEEK_SET);

    while(x != to_skip)
    {
        a = getc(hist_ptr);
        if(a == '\n')
            x++;
    }

    char *command_to_execute = (char *)malloc(1024 * sizeof(char));
    int len = 0;

    while(1)
    {
        a = getc(hist_ptr);
        if(a == '\n' || a== EOF)
            break;

        command_to_execute[len++] = a;
    }

    command_to_execute[len] = '\0';

    commandHandler(command_to_execute);
    free(command_to_execute);
}