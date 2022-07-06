#include "header_files.h"
#define clrscr() printf("\033[H\033[J")  // works same as ctrl+l // may not work in all consoles

char home_dir[1024];
char process_name[1024];
char* tokens[1024]; // will store tokens in command
 int  job_pid[100];
 int number_of_jobs =0;
 char* job_name[100];
 int in_type = 0;
 int out_type =0;

 pid_t process_id = 0;

 int shell_id;

 FILE* hist_ptr;
 int hist_number = 0;

int main()
{

    // allocating memory to job_name
    for(int i=0;i<100;i++)
        job_name[i] = (char *)malloc(1024*sizeof(char));

    hist_ptr = fopen("history.txt" , "a+");

    if(hist_ptr == NULL)
    {
        perror("history.txt");
    }

    char a;
    for(a = getc(hist_ptr) ; a != EOF ; a = getc(hist_ptr))
    {
        if(a == '\n')
            hist_number++;
    }

    clrscr();
    getcwd(home_dir , sizeof(home_dir));

    // handle signals
    signal(SIGINT, ctrl_c);    // no effect on bg process but kills the fg process (except shell)
    signal(SIGTSTP , ctrl_z);  // push the fg process to bg and stop it // no effect on the shell if no fg process is running
    signal(SIGCHLD, handler); // handles the signal recieved when a child process is terminated

    shell_id = getpid();

    printf("Current shell pid is %d\n" , shell_id);

    while(1) {
        shell_prompt();
        process_id = 0;
        char *command;
        char *temp;
        char *temp1;
        char ** list_of_commands;
        command = (char *) malloc(1024 * sizeof(char));
        temp = (char *) malloc(1024 * sizeof(char));
        temp1 = (char*)malloc(1024 * sizeof(char ));

        list_of_commands = (char**)malloc(200 * sizeof(char*));

        if(fgets(temp1, 1024, stdin) == NULL) // remember this also include an \n at the last
        {
            printf("Thanks for using the shell\n");
            exit(EXIT_SUCCESS);
        }
        command[strlen(temp1) - 1] = '\0';

        // storing the list of commands
        char *token = strtok(temp1 , ";");
        int number_of_commands = 0;

        while(token != NULL)
        {
            list_of_commands[number_of_commands] = malloc(200 * sizeof(char));
            strcpy(list_of_commands[number_of_commands++] , token);
            token = strtok(NULL , ";");
        }


            for(int i=0;i<number_of_commands;i++)
            {
                strcpy(command , list_of_commands[i]);

                // removing white space from the start of the command
                command = remove_white_space(command);

                strcpy(temp, command);  // copying the original command
                // if nothing is written , continue the loops
                if ((tokens[0] = strtok(command, " \n\t\r")) == NULL) {
                    continue;
                }

                int len = strlen(temp);
                int flag = 0;

                if(temp[len-1] != '\n')
                {
                    temp[len] = '\n';
                    temp[len+1] = '\0';
                }
                history_add(temp);
                commandHandler(temp);
            }

            free(temp);
    }

}