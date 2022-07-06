#ifndef SHELL_HEADER_FILES_H
#define SHELL_HEADER_FILES_H

#define _DEFAULT_SOURCE

// These are the headers files to include
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
//#include <readline/readline.h>
//#include <readline/history.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include "commandHandler.h"
#include "main.h"
#include "prompt.h"
#include "string_manipulation.h"
#include "string_manipulation.h"
#include "signal_handler.h"
#include <dirent.h>
#include <stdlib.h>
#include <time.h>

// these are the function prototype
void print_history_list ();
void change_directory();

char* skip_white_space(char* );

void shell_prompt();
void handle_sigint(int );
void commandHandler(char* );
void cd(char**  , int );
void ls(char*);
void pwd();
void echo(char *);
void repeat(char ** , int);
void pinfo(char ** , int);
void run_system_command(char ** , int  , int );
void history_add(char *);
void show_history();
void hist_num(int );
char * remove_white_space(char *);
void up_arrow(int );
int check_up_key(char *);
void check_redirection(char *);
void handle_redirection(char *);
bool check_pipe(char *);
int tokenize_pipe(char*  , char ** );
void handle_pipeline(char *);
void delete_ith_job(int );
void jobs(char**  , int );
void sig(int  , int );
void fg(char** , int );
void bg(char** , int);
void replay(char ** , int );
// All the global variables

extern char *args[512];
extern int flag, len;
extern char cwd[1024];
extern char home_dir[1024];
extern char* tokens[1024]; // will store tokens in command
extern int job_pid[100]; // job_pid[i] stores the pid of the process with job_id i+1;
extern int number_of_jobs;
extern char* job_name[100]; // stores the name of process
extern pid_t process_id;
extern char process_name[1024];
extern pid_t shell_id;
extern FILE* hist_ptr;  // points to the file which stores history.txt
extern int hist_number; // stores the number of entries in the history.txt
extern int in_type;  // for input redirection
extern int out_type; // for output redirection

#endif //SHELL_HEADER_FILES_H
