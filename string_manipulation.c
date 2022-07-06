#include "header_files.h"

// removes extra white spaces from the input string
char* skip_white_space(char* input)
{
    int ptr =0;
    int len = strlen(input);
    for(int i=0;i<len;i++)
    {
        if(input[i] != ' ' && input[i] != '\t' && input[i] != '\n') {
            input[ptr++] = input[i];
        }
    }
    input[ptr++] = '\0';
    return input;
}

// This fxn remove white space just from the start
char * remove_white_space(char *input)
{
    int ptr = 0;
    int len = strlen(input);
    for(int i=0;i<len;i++)
    {
        if(input[i] != ' ' && input[i] != '\t' && input[i] != '\n')
        {
            ptr = i;
            break;
        }
    }
    return &input[ptr];
}










