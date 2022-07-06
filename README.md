# This shell is completely writeen in C. It has some in-built fxn and various user defines commands. It also supports redirection , piping and can run processes in both foregrounf and background.

# Usage
To run the shell
```
make
./a.out
```

To quit the shell
```
quit
```

Various fxn's of the shell: 
    1. `cd`
    Changes the directory 
    >* cd [arguments] 
    This changes the current directory to the argument
    >* cd .. 
    Takes back to the prev directory.
    >* cd or cd /
    Takes to the home directory

    2. echo [argument]
    prints the argument give 

    3. `pwd' 
    prints the name of current working directory 

    4. ls 
    -> -l and -a flags are supported.
    -> It prints the contents of the directory

    5. system command (with and w/o argumnets ) can be run both in foreground and background.

    6. `pinfo <pid>`
    Prints the deatail of the process of the given pid. If no pid is provided , then it assume the pid = shell_pid


    7. Prints the pid of the process after a background process exits. 

    8. repeat <num> <command > - repeat a command given number of times

    9. History -> shows the last 10 used commands. 

    10-> History <num> -> shows the last num number of commands. 

    11. `jobs`
    Print all the jobs in order of their aplhabetical name of the process and show their current status.
    - supports -r(show running only) and -s (show stopped only) flags

    12 `bg [job id]` 
    Changes the state of a stopped background job to running (in the background) and do nothing if the job is already running in the background.

    13. `fg [job id]`
    Brings the running or stopped background job corresponding to ​job number​ to the foreground, and changes its state to ​running .

    14. CTRL-Z
    Pushes any currently running foreground job into the background, and change its state from running to stopped. Have no effect on the shell if there is no foreground process running.

    15. CTRL-C
    Interrupt any currently running foreground job, by sending it the ​SIGINT​ signal. Have no effect on the shell if there is no foreground process running.

    16. CTRL_D 
    log you out of your shell, without having any effect on the actual terminal

    17. replay -command [command] -interval [interval] -period [period]

    It will execute the command periodically at an interval of [interval] untill total times elapsed from start is less than period. 

    Flags {-command , -interval , -period can be provided in any order}

    18. quit
    Exits the shell. 


# The complete code is modular and each functionality has been implemented in diff files. 
# all fxn prototypes has been defined in header.h

1-> run_system_command => has run_system_command()  is responsible to run system command in bg/fg
2->  signal_handler.c => handles ctrl_c , ctrl_z signals and also handles signals received when a child dies.
3->  string_manipulation.c => manages white spaces present in commands
4-> repeat.c => contains implementation of repeat command
5-> pwd.c =>  contains implementation of pwd command
6-> prompt.c => responsible to show prompt
7-> pinfo.c => contains implementation of pinfo command
8-> ls.c , cd.c , echo.c => contains implementation of ls , cd , echo commands respectively
9-> history.c , up_arrow.c => contains implementation of history , up_arrow command
10 -> command_handler.c => contains the command_handler.c fxn which gets the input from the terminal after it is parsed properly and is responsible for calling appropriate fxn according to command.
11-> main.c => takes input from the terminal and then parse it and then pass it to command handler.
12. bg.c => have implementation of bg commad
13. fg.c => have implementation of fg commad
14. signal_handler.c => have implementation to handle ctrl_c , ctrl_z and sigchld signal.
15. replay.c => have implementation of replay command
16. jobs.c -> have implementation of jobs command 
17 -> sig.c -> have implementation of sig command 
18. -> check_redirection_pipe => contains command to check if redirectio/piping is there in command
19. redirection.c -> handles redirection
20. piping.c -> handles piping

