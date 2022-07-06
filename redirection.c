//
// Created by hardik on 04/10/21.
//

#include "header_files.h"

bool is_file(char *name)
{
    struct stat f;
    if(stat(name , &f)==0 && !S_ISDIR(f.st_mode))
        return true;
    else return false;
}

void handle_redirection(char *command)
{
    check_redirection(command);

    // saving fd of stdin and stdout
    int stdin_copy = dup(STDIN_FILENO);
    int stdout_copy = dup(STDOUT_FILENO);

    int status;

    char *input_file; // stores the name of input file
    char *output_file; // stores the name of output file

    input_file = (char*)malloc(sizeof(char) * 1024);
    output_file = (char*)malloc(sizeof(char) * 1024);

    // if input redirection is there
    // then store the file_name

    if(in_type != 0)
    {
        strcpy(input_file , command);

        input_file = strtok(input_file , "<");
        input_file = strtok(NULL, "<");
        input_file = strtok(input_file , " \n\r\t");
    }

    // if output_redirection is there , then store the output file name
    if(out_type != 0)
    {
        strcpy(output_file , command);

        output_file = strtok(output_file , ">");
        output_file = strtok(NULL, ">");
        output_file = strtok(output_file , " \n\r\t");
    }

    // now we also have to store the original command arguments
    int number_of_args =0;
    char **args;
    args = (char**)malloc(sizeof(char*)*100);

    command = strtok(command , "<");

    command = strtok(command , " \t\r\n");

    while(command != NULL)
    {
        if(strcmp(command , ">") == 0 || strcmp(command , "<") == 0 || strcmp(command , ">>") == 0)
            break;
        args[number_of_args] = (char*)malloc(sizeof(char)*1024);
        strcpy(args[number_of_args] , command);
        number_of_args++;
        command = strtok(NULL , " \r\t\n");
    }

    // create two processes
    // child and parent

    pid_t pid = fork();

    if(pid < 0)
    {
        perror("Error in forking: ");
        return;
    }

    if(pid == 0) // child process
    {

        int input_file_fd, output_file_fd;

        if(in_type != 0) {

            // checking if input file exists or not
            if (!is_file(input_file)) {
                perror("No such input file exists:");
                return;
            } else // open file for reading
            {
                input_file_fd = open(input_file, O_RDONLY);

                // use dup2 to take input from file rather than stdin
                if (input_file_fd < 0) {
                    perror("Error in opening input file");
                } else {
                    dup2(input_file_fd, 0);
                    close(input_file_fd);
                }
            }
        }

        // creating output file
        if(out_type != 0) {
            if (out_type == 1) {
                output_file_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

                // use dup2 to print output to file rather than stdout
                if (output_file_fd < 0) {
                    perror("Error in opening output file:");
                } else {
                    dup2(output_file_fd, 1);
                    close(output_file_fd);
                }
            } else if (out_type == 2) {
                output_file_fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);

                // use dup2 to print output to file rather than stdout
                if (output_file_fd < 0) {
                    perror("Error in opening output file:");
                } else {
                    dup2(output_file_fd, 1);
                    close(output_file_fd);
                }
            }
        }

        // execute the command using execvp
        if(execvp(args[0] , args) < 0)
        {
            perror("Not an valid command");
            exit(1);
        }

        dup2(stdin_copy, 0);
        close(stdin_copy);

        dup2(stdout_copy, 1);
        close(stdout_copy);

    }
    else // parent process
    {
        // wait for the child process  to finish
        while (wait(&status) != pid);
    }

    // free args
    for(int i=0;i<number_of_args;i++)
        free(args[i]);
    free(args);
//

}