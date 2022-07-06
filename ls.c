//
// Created by hardik on 13/09/21.
//

#include "header_files.h"

// returns true if file is hidden
bool file_hidden(char* filename)
{
    if(filename[0] == '.')
        return true;
    else
        return false;
}

// checks if it is a regular file or directry
int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

long int number_of_files(char *full_path)
{
    struct stat buff;
    if(stat(full_path, &buff) < 0)
    {
        perror("Error in finding number of files: ");
        return -1;
    }
    return buff.st_blocks;
}

void long_listing(char* dir_name , char* filename)
{

    char* filepath;
    filepath = (char*)malloc(1024*sizeof(char));

    if(filepath == NULL)
    {
        perror("Malloc allocation error in long_listing");
        return;
    }

    strcpy(filepath , dir_name);
    strcat(filepath , "/");
    strcat(filepath , filename);


    struct stat name;
    int x = stat(filepath, &name);

//    printf("Filename passed is %s\n" , filename);
//    printf("dir_name passed as argument is %s\n" , dir_name);

    if(x <0)
    {
        perror("Error in stat in long listing ls");
    }

    char perms[11];                              // perm[0] tells whether is directory or not
    // perm[1-9] contains rwxrwxrwx conditions  // perm[10] is simply '\0'
    struct group *gr = getgrgid(name.st_gid);   // contains the name of the group
    struct passwd *pw = getpwuid(name.st_uid);  // contains user's login name in pw_name
    mode_t p = name.st_mode;                    // stores info about read write execute permissions

    perms[0] = (stat(filepath, &name) == 0 && S_ISDIR(name.st_mode)) ? 'd' : '-';
    perms[1] = (p & S_IRUSR) ? 'r' : '-';
    perms[2] = (p & S_IWUSR) ? 'w' : '-';
    perms[3] = (p & S_IXUSR) ? 'x' : '-';
    perms[4] = (p & S_IRGRP) ? 'r' : '-';
    perms[5] = (p & S_IWGRP) ? 'w' : '-';
    perms[6] = (p & S_IXGRP) ? 'x' : '-';
    perms[7] = (p & S_IROTH) ? 'r' : '-';
    perms[8] = (p & S_IWOTH) ? 'w' : '-';
    perms[9] = (p & S_IXOTH) ? 'x' : '-';
    perms[10] = '\0';

    // storing the time info
    char* time;
    time = (char*)malloc(100*sizeof(char));

    strftime(time, 100, "%b  %d %H:%M", localtime( &name.st_mtime));
    // %b -> abbreviated name of the month (like Sep)
    // %d -> date (like 12)
    // %H:%M -> Hour(in 24hr format):miniutes (from 0 to 59)

    // print the info
        printf("%s\t%ld\t%s\t%s\t%ld\t %s\t %s\n" , perms , name.st_nlink , pw->pw_name , gr->gr_name , name.st_size , time , filename);
    free(time);
    free(filepath);

}



void ls_print(char* directory_name , int f1 , int f2)
{
    // f1 tells if -l flag is present
    // f2 tells if -a flag is present

    if(is_regular_file(directory_name))
    {
        // finding if absolute path where file reside is given or is it in current directory?
        // just print the file name
        int len = strlen(directory_name);
        int index = -1;
        for(int i=len-1;i>=0;i--) {
            if (directory_name[i] == '/') {
                directory_name[i] = '\0';
                index = i;
                break;
            }
        }

        char file_name[1024];

        // this means that it is in current directory
        if(index == -1)
        {
            strcpy(file_name , directory_name);
            char *buff = getcwd(NULL , 0);
            strcpy(directory_name , buff);
            free(buff);
        }
        // absolute path is given
        else
        {
            strcpy(file_name , &directory_name[index+1]);
        }


        // for a file -a flag does not matter
        // check only if -l flag is present or not
        if(f1)
        {
            long_listing(directory_name , file_name);
        }
        else
        {
            printf("%s\n" ,file_name);
        }
        return;
    }

    int total = 0;

    struct dirent **file;
    int n = scandir(directory_name , &file , NULL , alphasort);

    if(n== -1)
    {
        perror("Error during ls while doing scandir");
        return;
    }

    // n is the number of directory entry

    //printf("Value of n is %d\n" , n);

    if(f1)
    {
        for(int i=0;i<n;i++)
        {
            if(f2 || !file_hidden(file[i]->d_name)) {
                long_listing(directory_name, file[i]->d_name);
                //printf("Name of the %dth file is %s\n" , i ,file[i]->d_name);

                // finding the full path of the file
                char* full_path;
                full_path = malloc(1024*sizeof(char));

                strcpy(full_path , directory_name);
                strcat(full_path , "/");
                strcat(full_path , file[i]->d_name);

                total += number_of_files(full_path);
                free(full_path);

            }
            free(file[i]);
        }
        printf("\n");
        free(file);
    }
    else
    {
        for(int i=0;i<n;i++)
        {
            if(f2 || !file_hidden(file[i]->d_name)) {
                printf("%s\t", file[i]->d_name);

                // finding the full path of the file
                char* full_path;
                full_path = malloc(1024*sizeof(char));

                strcpy(full_path , directory_name);
                strcat(full_path , "/");
                strcat(full_path , file[i]->d_name);

                total += number_of_files(full_path);
                free(full_path);
            }
            free(file[i]);
        }
        printf("\n");
        free(file);
    }

    if(f1)
        printf("\nTotal: %d\n" , total/2);
}

void ls(char *command)
{
    int sum = 0;  // will store the number of files / directory

    char *token = command; // will be used to make token from the command
    int f1 =0 , f2 =0 ;  // f1 tells if -l flag is present and f2 tells if -a flag is present
    int len = strlen(command);


    for(int i=2;i<len;i++)
    {
        // check if -l command is present
        if(i+1 < len && command[i] == '-' && command[i+1] == 'l')
            f1 = 1;
        // check if -a command is present
        if(i+1 < len && command[i] == '-' && command[i+1] == 'a')
            f2 = 1;
        // check if -al command is present
        if(i+2 < len && command[i] == '-' && command[i+1] == 'a' && command[i+2] == 'l')
        {
            f1 = 1;
            f2 = 1;
        }

        if(i+2 < len && command[i] == '-' && command[i+1] == 'l' && command[i+2] == 'a')
        {
            f1 = 1;
            f2 = 1;
        }
    }


    int y=0;

    token = strtok(token , " \n\t\r");

    token = strtok(NULL , " \n\t\r");



    while(token != NULL)
    {
        if(strcmp(token , "-l")==0 || strcmp(token , "-a")==0 || strcmp(token , "-al")==0 || strcmp(token , "-la")==0 )
        {
            token = strtok(NULL , " \n\t\r");
            continue;
        }
        y = 1; // that means at least one directory/file_name name was provided and it is not ls . or ls simply

        char* final_path;
        int n = strlen(token);
        char* temp= (char*)malloc((n+1) * sizeof(char));
        temp = '\0';

        // token contain some directory name
        // we have to find out if it is relative(to home_dir) or absolute

        if(token[0] == '~') // relative to home_dir
        {
            // have to first copy the path of home dir in final_path
            int length_home_dir = strlen(home_dir);
            final_path = (char*)malloc((length_home_dir)+n + 100);

            strcpy(final_path , home_dir);
            if(n>1)
            strcat(final_path , &token[1]);

            final_path[n+length_home_dir-1] = '\0';
        }
        else
        {
            // copy the token in final_path
            final_path = (char*)malloc((n+10)*sizeof(char ));
            strcpy(final_path , token);
        }

        y= 1;
        ls_print(final_path , f1 , f2);

        free(temp);
        free(final_path);

        token = strtok(NULL , " \n\t\r");
    }

    if(y !=1) // we have to print for current directory
    {

        char *current_dir = getcwd(NULL , 0);
        if(current_dir == NULL)
        {
            perror("getcwd");
            return;
        }

        ls_print(current_dir , f1 , f2 );
        free(current_dir);
    }


}