//
// Created by hardik on 14/09/21.
//
#include "header_files.h"

// this function is responsible for runnning all the commands
void commandHandler(char* command)
{
    // storing command in some other place cause strtok modifies the original string
    char* temp1 ;
    char * command_copy;
    command_copy = (char *)malloc(1024 * sizeof(char));
    temp1 = (char*)malloc(1024*sizeof(char));

    if(temp1 == NULL || command_copy == NULL)
    {
        printf("Error in malloc allocation in command handler\n");
        return;
    }

    strcpy(command_copy , command);
    strcpy(temp1 ,command_copy);

    if(check_pipe(command))
    {
        handle_pipeline(command);
        return;
    }

    // checking for redirection
    check_redirection(command);

    if(in_type != 0 || out_type != 0) // that means redirection is there
    {
        handle_redirection(command);
        return;
    }


    // return if command is empty
    temp1 = strtok(temp1 , " \n\t\r");
    if(temp1 == NULL)
        return;

    char** args; // will be used to store the tokens of the command
    args = (char**)malloc(100*sizeof(char*));

    int no_of_args=0; // store the number of tokens

    // storing all the tokens
    while(temp1 != NULL)
    {
        int len = strlen(temp1);
        args[no_of_args] = (char*)malloc(len*sizeof(char)+10);
        strcpy(args[no_of_args] , temp1);
        temp1 = strtok(NULL , " \n\t\r");
        no_of_args++;
    }

    // now command name is in args[0]

    if(strcmp(args[0] , "ls")==0)
    {
        // handle ls
        ls(command_copy);
    }
    else if(strcmp(args[0] , "cd")==0)
    {
        // handle cd
        cd(args , no_of_args);
    }
    else if(strcmp(args[0] , "pwd")==0)
    {
        // hanldle pwd
        pwd();
    }
    else if(strcmp(args[0] , "echo")==0)
    {
        // handle echo
        echo(command_copy);
    }
    else if(strcmp(args[0] , "repeat") == 0)
    {
        // handle repeat
        repeat(args , no_of_args);
    }
    else if(strcmp(args[0] , "pinfo") ==0)
    {
        // handle pinfo
        pinfo(args , no_of_args);
    }
    else if(strcmp(args[0] , "history") == 0)
    {
        int n = 10;
        if(no_of_args == 1)
        {
            show_history();
        }
        else
        {
            n = atoi(args[1]);
            hist_num(n);
        }
    }
    else if(strcmp(args[0] , "jobs") == 0)
    {
        jobs(args , no_of_args);
    }
    else if(strcmp(args[0] , "sig") == 0)
    {
        if(no_of_args != 3)
        {
            printf("Wrong number of argument provided\n Format is sig job_id signal\n");
            return ;
        }
        int job_id = atoi(args[1]);
        int signal_no = atoi(args[2]);

        sig(job_id , signal_no);
    }
    else if(strcmp(args[0] , "fg") == 0)
    {
        fg(args , no_of_args);
    }
    else if(strcmp(args[0] , "bg") == 0)
    {
        bg(args , no_of_args);
    }
    else if(strcmp(args[0] , "replay") == 0)
    {
        replay(args , no_of_args);
    }
    else if(strcmp(args[0] , "exit")==0 || strcmp(args[0] , "quit") == 0)
    {
        // closing the opened file
        fclose(hist_ptr);

        printf("Thanks for your time!!\n");
        printf("Have  a nice day!!\n");
        exit(EXIT_SUCCESS);
    }
    // if the last token is & or the last char of last token (say ls&) is & , then run in background
    else if(strcmp(args[no_of_args-1] , "&") ==0 || (args[no_of_args-1][strlen(args[no_of_args-1]) - 1] ==  '&'))
    {
        run_system_command(args , no_of_args, 1);
    }
    else // system command is given , just run it in foreground // backgrund case has already been handled above
    {
        run_system_command(args ,no_of_args ,  0);
    }
    // freeing memory
//    free(command);
    free(command_copy);
    free(temp1);
    for(int i=0;i<no_of_args;i++)
    {
        if(args[i] != NULL)
            free(args[i]);
    }
    free(args);
}