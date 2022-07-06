#include "header_files.h"
void pinfo(char ** args , int no_of_args)
{
    char status[1024] ;
    char exe[1024];
    int pid;

    if(no_of_args >= 2 && args[1] != NULL)
    {
        strcpy(status , "/proc/");
        strcat(status , args[1]);
        strcat(status , "/stat");
        strcpy(exe, "/proc/");
        strcat(exe , args[1]);
        strcat(exe , "/exe");
        pid = atoi(args[1]);
    }
    else {    // if no argument is provided , use the shell_id
        strcpy(status , "/proc/self/stat");
        strcpy(exe , "/proc/self/exe");
        pid = shell_id;
    }

//    printf("Pid being used is %d\n" , pid);
//    printf("status = %s\n" ,status);
//    printf("exe = %s\n" , exe);

    // opening the file
    FILE *f;


    if( !(f = fopen(status , "r")) )
    {
        printf("No process with %d pid exists\n" , pid);
        return;
    }

    else
    {
        int pid ,   pgrp , tpgid , memory;
        char status ;
        fscanf(f,
               "%d %*s %c %*s %d %*s %*s %d %*s %*s %*s %*s %*s %*s %*s %*s %*s "
               "%*s %*s %*s %*s %*s %d",
               &pid, &status, &pgrp, &tpgid, &memory);

        // %*s is used to denote the variable length of space between the arguments

        printf("pid -- %d\n" , pid);
        printf("Process Status -- %c%c\n" , status , pgrp == tpgid ? '+': ' ');
        printf("memory --%d {Virtual Memory}\n" , memory);
        fflush(stdout);
    }

    fclose(f);

    char exe_path[2100];

    int pathlen = readlink(exe , exe_path , 2000);

    if(pathlen < 0)
    {
        printf("No path for executable\n");
        return;
    }


    exe_path[pathlen] = '\0';
    char *substring;


    // it returns the first occurence of substring
    // doing this to find if we have to print the path relative to home_dir
    // or absolute path
    substring = strstr(exe_path , home_dir);

    // print the relative path
    if(substring != NULL)
    {
        printf("Executable Path --~%s\n" , &exe_path[strlen(home_dir)]);
    }
    else // print the absolute path
    {
        printf("Executable Path --%s\n" , exe_path);
    }
}