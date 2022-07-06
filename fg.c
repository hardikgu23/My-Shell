// Created by hardik on 07/10/21.

#include "header_files.h"

void fg(char **args , int no_of_args)
{

    if(no_of_args != 2)
    {
        printf("Incorrect number of arguments\n");
        return;
    }

    int job_id = atoi(args[1]);
    job_id--;// as we are using 0 based indexing

    if(job_id < 0 || job_id > number_of_jobs || job_pid[job_id] == -1)
    {
        printf("Pls enter a valid job id\n");
        return;
    }

    int pid = job_pid[job_id];
    int status ;

    signal(SIGTTIN , SIG_IGN);
    signal(SIGTTOU , SIG_IGN);

    // making child process group , foreground process group
    tcsetpgrp(STDIN_FILENO , getpgid(pid));

    // send continue signal to child
    kill(pid , SIGCONT);

    // wait till child is finished XD
    waitpid(pid , &status , WUNTRACED);

    // child is done executing
    // again set the shell , the fg process grp
    tcsetpgrp(STDIN_FILENO , getpgid(shell_id));

    // reset sigttin and sigttout
    signal(SIGTTIN , SIG_DFL);
    signal(SIGTTOU , SIG_DFL);

    if(WIFSTOPPED(status))
    {
        // Process was stopped
    }
    else
    {
        // process was not stopped
        // delete its entry from the list
        job_pid[job_id] = -1;
    }
}