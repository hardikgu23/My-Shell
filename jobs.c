//
// Created by hardik on 06/10/21.
//

#include "header_files.h"

struct output
{
    int pid;
    int job_id;
    char *name;
    char *status;
};
typedef struct output Output;

void sort_output(Output *out , int number_of_output)
{

    Output  temp;
    // using bubble sort to sort the output
    for(int i=0;i<number_of_output;i++)
    {
        for(int j=i+1;j<number_of_output;j++)
        {
            if(strcmp(out[i].name , out[j].name) > 0)
            {
                temp = out[j];
                out[j] = out[i];
                out[i] = temp;
            }
        }
    }
}

void jobs(char **args , int no_of_args)
{
    char type;
    if(no_of_args == 1)
    {
        type = 'a'; // a represent both stopped and runnning process
    }
    else
        type = args[1][1];      // args[1] will be -(r/s)


    // we have to print in the alphabetical order of name of jobs
    int number_of_output =0;
    Output out[100];

    char *proc_status;
    proc_status = (char*)malloc(1024 * sizeof(char ));
//    printf("Number of jobs are %d\n" , number_of_jobs);
    for(int i=0;i<number_of_jobs;i++)
    {
        if(job_pid[i] == -1)
            continue;

//        printf("Reached here i = %d pid is %d\n" , i , job_pid[i]);
//        fflush(stdout);

        sprintf(proc_status , "/proc/%d/status" , job_pid[i]);
        
        FILE* f;
        f = fopen(proc_status , "r");
        if(f == NULL)
        {
            perror("fopen");
            return;
        }

        // status of the process is in 3rd line
        // skip first two line
        int skipped_line = 0;
        while(skipped_line != 2)
        {
            char c;
            fscanf(f , "%c" , &c);
            if(c == '\n')
                skipped_line++;
        }

        // store the 3rd line
        char line[100];
        fgets(line , sizeof(line) , f);

        // line now contains the 3rd line , remove the spaces from it
        remove_white_space(line);

        char *temp;

//        printf("Value of temp is %s\n" , temp);

        temp = strtok(line , ":\n\t\r");
        temp = strtok(NULL , ":\n\t\r");

        if(temp[0] == 'T' && ( (type == 'a') || (type == 's') )) // for stopped process
        {
            out[number_of_output].pid = job_pid[i];
            out[number_of_output].job_id = i+1;
            out[number_of_output].name = (char*)malloc(sizeof(char)*1024);
            out[number_of_output].status = (char*)malloc(sizeof(char)*100);

            strcpy(out[number_of_output].name , job_name[i]);
            strcpy(out[number_of_output].status , "Stopped");
            number_of_output++;
        }
        else if( (temp[0] != 'T') && ((type == 'a') || (type == 'r')) )
        {
            out[number_of_output].pid = job_pid[i];
            out[number_of_output].job_id = i+1;
            out[number_of_output].name = (char*)malloc(sizeof(char)*1024);
            out[number_of_output].status = (char*)malloc(sizeof(char)*100);

            strcpy(out[number_of_output].name , job_name[i]);
            strcpy(out[number_of_output].status , "Running");
            number_of_output++;
        }
    }

//    printf("Reached here\n");
//    fflush(stdout);

    // now sort the output according in alphabetical order
    sort_output(out , number_of_output);

//    printf("Reached here\n");
//    fflush(stdout);

    // print the output
    for(int i=0;i<number_of_output;i++)
    {
        printf("[%d] %s %s [%d]\n",out[i].job_id, out[i].status, out[i].name , out[i].pid);
    }
}