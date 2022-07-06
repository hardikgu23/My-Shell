//
// Created by hardik on 07/10/21.
//

#include "header_files.h"

void bg(char **args , int no_of_args)
{
    if(no_of_args != 2)
    {
        printf("Incorrect number of argument provided to bg\n");
        return;
    }
    int job_id = atoi(args[1]);
    job_id--; // cause using 0 based indexing
    if(job_id < 0 || job_id > number_of_jobs || job_pid[job_id] == -1)
    {
        printf("Invalid job id\n");
        return;
    }

    int pid = job_pid[job_id];

    if(kill(pid , SIGCONT) < 0)
    {
        perror("Can not run bg process: ");
        return;
    }
}