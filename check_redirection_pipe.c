//
// Created by hardik on 04/10/21.
//

#include "header_files.h"

// check_redirection checks for redirection  and sets bits accordingly
// in_type = 0(no <) , 1 (< is provided)
// out_type = 0(no > or >>) , = 1(> is present) , = 2(>> is present)
void check_redirection(char *command)
{
    int len = strlen(command);

    in_type =0;
    out_type = 0;

    // checking if < or > is present in command or not
    for(int i=0;i<len;i++)
    {
        if(command[i] == '<')
            in_type = 1;
        else if(command[i] == '>')
            out_type = 1;
    }

    // checking if >> is present
    for(int i=0;i<len-1;i++)
    {
        if(command[i] == '>' && command[i+1] == '>')
            out_type = 2;
    }
    return;
}

bool check_pipe(char *command)
{
    for(int i=0;i<strlen(command);i++)
    {
        if(command[i] == '|')
            return true;
    }
    return false;
}
