#include "header_files.h"
void ctrl_c(int signum)
{
    // pid of calling process is stored in process_id

    if(process_id > 0 && process_id != shell_id)
    {
        // this is foreground process // kill it
        kill(process_id , SIGINT);
        printf("\n");
        fflush(stdout);
    }
    else
    {
        printf("\n");
        shell_prompt();
        fflush(stdout);
    }
    signal(SIGINT, ctrl_c);
}

void ctrl_z(int signum)
{
    // pid of calling process is stored in process_id

    if(process_id > 0 && process_id != shell_id)
    {
        // this is foreground process
        kill(process_id , SIGTSTP);

        // add the process to background
        job_pid[number_of_jobs] = process_id;
        strcpy(job_name[number_of_jobs] , process_name);
        number_of_jobs++;
        printf("\n");
        fflush(stdout);
    }
    else
    {
        printf("\n");
        shell_prompt();
        fflush(stdout);
    }

    signal(SIGTSTP, ctrl_z);
}

//void delete_ith_job(int i)
//{
//    for(int j=i;j<number_of_jobs-1;j++)
//    {
//        job_pid[i] = job_pid[i+1];
//        strcpy(job_name[i] , job_name[i+1]);
//    }
//
//    number_of_jobs--;
//}

void handler(int signum)
{
    int status , f=0;

    pid_t pid = waitpid(-1 , &status , WNOHANG);

    if(pid > 0)
    {
        char process[200];
        int is_present =0; // tells if pid is present in running processes

        for(int i=0;i<number_of_jobs;i++)
        {
            if(job_pid[i] == pid)
            {
                // copy the name of the process
                strcpy(process , job_name[i]);

                // remove this process from data
//                delete_ith_job(i);
                  job_pid[i] = -1;

                is_present = 1;
                break;
            }
        }

//      checking if process termination was normal
//      WIFEXITED(status) : returns true if the child terminated normally.
//      WEXITSTATUS(status) : returns the exit status of the child. This macro should be employed only if WIFEXITED returned true
        if(WEXITSTATUS(status) == 0 && WIFEXITED(status) && is_present)
        {
            fprintf(stderr , "%s with pid %d exited normally\n" , process  , pid );
        }
        else if(is_present==1)
        {
            fprintf(stderr , "%s with pid %d failed to exit normally\n" , process  , pid );
        }

        if(is_present)
        {
            shell_prompt();
            fflush(stdout);
        }
    }
    signal(SIGCHLD, handler);
}



