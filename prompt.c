#include "header_files.h"

//char home_dir[1024];

void print_directory()
{
    // storing the current working directory
    char cwd[1024];
    if (getcwd(cwd , sizeof(cwd)) == NULL)
    {
        perror("Error in getting curent working directory: ");
        return;
    }

    // home_dir
    int l = strlen(cwd);
    int len = strlen(home_dir);

    bool flag1 = true , flag2 = true;

    if(l < len) // cwd is surely not inside in home_dir or is home_dir , so just print it
    {
        printf("%s>",cwd);
        return;
    }
    else
    {
        // checking if first len character of cwd is same as home_dir
        for(int i=0;i<len;i++)
        {
            if(home_dir[i] != cwd[i])
            {
                flag1 = false;
                break;
            }
        }

        if(flag1 == false) // not in home dir
        {
            printf("%s>" , cwd);
            return;
        }
        else
        {
            // if both length are same , that means they both are same dir
            if(l == len)
            {
                printf("~>");
                return;
            }

            // if current directory is in home dir , than printing it relative path else printing cwd
            if(l >= len && cwd[len] == '/')
            {
                printf("~");
                for(int i=len;i<l;i++)
                {
                    printf("%c" , cwd[i]);
                }
                printf(">");
                return;
            } else
            {
                printf("%s>"  , cwd);
                return;
            }

        }

    }

}

void shell_prompt()
{
    // adding colors to the prompt // will display in red color
    printf("\033[0;31m");

    // Store username , hostname
    char* UserName = getlogin();
    char hostname[256];
    int hostnum = gethostname(hostname, sizeof(hostname));
    if(hostnum == -1)
    {
        perror("error in getting hostname");
        exit(1);
    }

    printf("<%s@%s: " , UserName , hostname);

    print_directory();

    printf("\033[0m");  // will display back to original color
}


//int main()
//{
//    shell_prompt();
//}
