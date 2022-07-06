//
// Created by hardik on 07/10/21.
//

#include "header_files.h"

void sig(int job_id , int signal_no)
{
//    printf("Job is is %d and number of jobs is %d\n" , job_id, number_of_jobs);
    if(job_id > number_of_jobs)
    {
        printf("Error: Not an valid job id\n");
        return;
    }
    int pid = job_pid[job_id-1];

//    printf("Pid is %d\n and signal is %d\n" , pid , signal_no);

    if(pid != -1)
    kill(pid , signal_no);
    else
    {
        printf("Error: Not an valid job id\n");
        return;
    }
}