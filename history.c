//
// Created by hardik on 17/09/21.
//

#include "header_files.h"
void history_add(char *command)
{
    if(hist_number < 20 ) {
        // file is already opened and its ptr is hist_ptr
        fseek(hist_ptr, 0, SEEK_SET);

        // check if the newly added command is same as previous command
        // if yes , then do not add this command in the list
        int num = 0;

        int line_no = 0;
        if (hist_number - 1 > line_no)
            line_no = hist_number - 1;


        while (num != line_no) {
            char a = getc(hist_ptr);
            if (a == '\n')
                num++;
            if (a == EOF)
                break;
        }

        // stores this command in prev_commad
        char *prev_command;
        prev_command = (char *) malloc(1024 * sizeof(char));

        int len = 0;
        char a;
        while (1) {
            a = getc(hist_ptr);
            if (a == '\n' || a == EOF)
                break;

            prev_command[len++] = a;
        }

        prev_command[len] = '\0';

        // checking
        if (strcmp(prev_command, command) == 0)
            return;

        fseek(hist_ptr, 0, SEEK_END);
        // printing in the file
        fprintf(hist_ptr, "%s", command);
        hist_number++;
    }
    else
    {
        fseek(hist_ptr , 0 , SEEK_SET);
        // open a temp file
        FILE * temp_file_ptr = fopen("temp_file" , "w+");

        // skip the first line of hist file
        char a;
        while(1)
        {
            a = getc(hist_ptr);
            if(a == '\n')
                break;
        }

        // copy the rest to the temp_file
        while(1)
        {
            a = getc(hist_ptr);
            if(a == EOF)
                break;

            fprintf(temp_file_ptr, "%c" , a);
        }


        // print the new command in temp file
        fprintf(temp_file_ptr , "%s" ,command );

        // close the original history file
        fclose(hist_ptr);

        // reopen the history.txt file
        hist_ptr = fopen("history.txt" , "w+");

        // print the content of temp file back into the history.txt
        fseek(temp_file_ptr, 0 , SEEK_SET);

        while(1)
        {
            a = getc(temp_file_ptr);
            if(a == EOF)
                break;

            fprintf(hist_ptr, "%c" , a);
        }

        // closing the temp.txt
        fclose(temp_file_ptr);

        // rest the hist_ptr to point at the start
        fseek(hist_ptr, 0 , SEEK_SET);
    }

}
// this function shows latest 10 histories
void show_history()
{
   hist_num(10);
}

// this fxn shows last n latest histories
void hist_num(int num )
{
    // setting stream pointer to the start
    fseek(hist_ptr , 0 , SEEK_SET);

    // find the number of top lines we have to skip
    int n = hist_number - num; // n = number of lines we have to skip

    while(n > 0)
    {
        char a = getc(hist_ptr);
        if(a == EOF)
            break;
        if(a == '\n')
            n--;
    }

    // now print the rest of the content
    char a;
    while((a = getc(hist_ptr)) != EOF)
    printf("%c" , a);

    // reset the stream ptr to start
    fseek(hist_ptr , 0 , SEEK_SET);
}
