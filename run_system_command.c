//
// Created by hardik on 14/09/21.
//
#include "header_files.h"
void run_system_command(char **args , int no_of_args , int background)
{

//    printf("Number of args is %d\n" , no_of_args);
//    for(int i = 0;i<no_of_args;i++)
//        printf("%s\n" , args[i]);

    if(no_of_args == 0)
        return;

    args[no_of_args] = NULL;
    if(background)
    {
        if(strcmp(args[no_of_args-1] , "&") == 0)
        {
            args[no_of_args-1] = NULL;
            no_of_args--;
        }
        else
        {
            // & is present as last letter of last token
            int len_last_arg = strlen(args[no_of_args-1]);

            args[no_of_args-1][len_last_arg-1] = '\0';
        }
    }


    // we need to make a child process cause otherwise execvp will replace the current process with the new one
    pid_t pid;
    pid = fork();

    if(pid == -1)
    {
        perror("Error in forking: ");
        exit(1);
    }

    if(pid == 0)
    {
        // child process

        if(background)
        {
            // change the group pid of the process to 0 so that it is not attached to the terminal
            setpgid(0,0);
        }


        // execute the command using execvp
        if(execvp(args[0] , args) < 0)
        {
            perror("Not an valid command");
            return;
        }
        exit(1);

    }
    else  // parent process
    {
        int child_id = pid , status;

        // if the process is running in foreground
        // block the parent process till it is completed
        if(background==0)
        {
            // setting the process id to the child id as current running process is child
            process_id = pid;

            // storing the name of the process
            strcpy(process_name , args[0]);

            for(int i=1;i<no_of_args;i++)
            {
                strcat(process_name , " ");
                strcat(process_name , args[i]);
            }


            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);
//            tcsetpgrp(STDIN_FILENO, getpgid(pid));

            waitpid(child_id , &status, WUNTRACED);

//            tcsetpgrp(STDIN_FILENO , getpgid(shell_id));
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);

            // if ctrl+z is pressed
            if(WIFSTOPPED(status))
            {
                printf("%s with PID %d suspended\n", args[0], pid);
            }
        }
        else  // background == 1
        {
            printf("Process pid = %d\n" , child_id);
            fflush(stdout);

            // storing the info about this process
            job_pid[number_of_jobs] = child_id;
            job_name[number_of_jobs] = (char*)malloc(sizeof(args[0]) + 10);
            strcpy(job_name[number_of_jobs] , args[0]);
            for(int i=1;i<no_of_args;i++)
            {
                strcat(job_name[number_of_jobs] , " ");
                strcat(job_name[number_of_jobs] , args[i]);
            }
            number_of_jobs++;
        }

    }
}





