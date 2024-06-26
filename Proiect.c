#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>
#include <errno.h>

struct stat file_info;
int status_code;

void pwd();
void CreateDIr(const char *directory_name, const char *path);
void createRegular(const char *file_name, const char *path);
void createFile (const char *input_path, const char *file_type, const char *path);
char** getComand ( char *input_line);
void type(const char* path);
void forkFunction(char *command, char **command_list);
void modifyList(char ** command_list, char **command_list1, char **command_list2);
void Run(char *command, char** command_list);
int check(char **command_list);


int main(){
    char command[200];
    char **commandList;
    char c;
    printf("\033[1;32m");
            printf("User:");
            printf("\033[1;34m");
            pwd();
            printf("\033[1;0m");
            printf("$ ");

    
    if(!isspace(c = getchar())){
                ungetc(c, stdin);
    fgets(command, 200, stdin);
    command[strlen(command)-1] = '\0';

    commandList = getComand(command);
    }
    
    else{
        commandList = getComand("Space");
    }
    
    while(strcmp(commandList[0], "exit") != 0){
        if (strcmp(commandList[0],"pwd") == 0)
        {
            pwd();
            printf("\n");
        }
    
    else if(strcmp(commandList[0],"create") == 0){
        if(commandList[1] != NULL && commandList[2] != NULL){
            createFile(commandList[2], commandList[1], commandList[3]);
        }
    }
    
    else if(strcmp(commandList[0], "cd") == 0){
        if(chdir(commandList[1]) != 0){
            perror("Current directory wasn't changed!");
        }
    }
    
    else if(strcmp(commandList[0], "type") == 0){
        if (commandList[1] != NULL){
            type(commandList[1]);
        }
    }

    else if(strcmp(commandList[0], "run") == 0) {
        if(check(commandList) == 1)
            forkFunction(commandList[1], commandList);
        else{
            Run(commandList[1], commandList);
        }

    }
    
            //how the command works
    else if (strcmp(commandList[0],"help") == 0){
        if(commandList[1] == NULL)
            printf("Type 'help name' to find out more about function 'name'\n Available functions: \nexit\npwd\ncd\ntype\ncreate\nrun\n" );
        else if(strcmp(commandList[1], "pwd") == 0){
            printf("pwd:\n\tPrint the name of the current working directory\n");
            }
        else if(strcmp(commandList[1], "cd") == 0){
            printf("cd:\n\tcd - change working directory\nSYNOPSIS\n\tcd [const char *path]\n");
            }
        else if(strcmp(commandList[1], "type") == 0){
            printf("type:\n\ttype -displays the type of the given entry (absolute or relative path)\nSYNOPSIS\n\ttype [const char *path]\n");
            }
        else if(strcmp(commandList[1], "run") == 0){
            printf("run:\n\trun -execute commands available in linux\nSYNOPSIS\n\trun command OR run command1 | command2\n");
            }
        else if(strcmp(commandList[1], "create") == 0){
            printf("create:\n\tcreate -creates a new entry of the given <type>\nSYNOPSIS\n\tcreate <type> [const char *path]\nTYPES:\n\t-f regular file\n\t-d directory\n\t-l symbolic link (Input file then output file)\n");
            }
        }
    printf("\033[1;32m");
            printf("User:");
            printf("\033[1;34m");
            pwd();
            printf("\033[1;0m");
            printf("$ ");
    if(!isspace(c = getchar())){
                ungetc(c, stdin);
    fgets(command, 200, stdin);
    command[strlen(command)-1] = '\0';

    commandList = getComand(command);
    }
    else{
        commandList = getComand("Space");
    }
    }
    return 0;
}

//print the current work directory
void pwd() {
       char cwd[256];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("%s", cwd);
   } else {
       perror("getcwd() error");
   }
}

//change directory
void CreateDIr(const char *directory_name, const char *path){
    char cwd[256] = "";
    char cwd1[256];
    if( path != NULL) {
            printf("%s", path);
        if (getcwd(cwd1, sizeof(cwd1)) == NULL) {
        perror("getcwd() error");
   }

    if( chdir(path) != 0) {
        perror("This is an invalid path!\n");
    }
    else{
        chdir(cwd1);
        strcat(cwd, path);
        strcat(cwd,"/");
        strcat(cwd,directory_name);
    }
    }
    else
    {
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
             perror("getcwd() error");
             }
        strcat(cwd,"/");
        strcat(cwd,directory_name);
        }
    

    if( mkdir(cwd, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0)
    
    perror("Directory wasn't created\n");
    
//S_IRWXU - Read and write permission bit for the owner of the file
//S_IRWXG - Read and write permission bit for the group owner of the file
//S_IROTH - Read permission bit for other users
//S_IXOTH - Execute permission bit for other users

}
//create a regular file
void createRegular(const char *file_name, const char *path) {

       char cwd[256] = "";
       char cwd1[256];
    if (getcwd(cwd1, sizeof(cwd1)) == NULL) {
        perror("getcwd() error");
   }

    if(path != NULL){
    if( chdir(path) != 0) {
        perror("This is an invalid path!\n");
    }

        else{
        chdir(cwd1);
        strcat(cwd, path);
        strcat(cwd,"/");
        strcat(cwd,file_name);
    }
    }else
    {
        if(path == NULL){
             if (getcwd(cwd, sizeof(cwd)) == NULL) {
             perror("getcwd() error");
             }
        strcat(cwd,"/");
        strcat(cwd,file_name);
        }
    }
    int file = open(cwd, S_IREAD);
    if(file > 0){
        printf("File exist!\n");
    }
else
    open(cwd, O_CREAT, S_IRWXU);
}
//S_IREAD - Read permission bit for the owner of the file

// check what kind of file shall be created and where if the path is provided
void createFile (const char *input_path, const char *file_type, const char *path) {

    if(strcmp(file_type, "-f") == 0){
        createRegular(input_path, path);
    }
    else if(strcmp(file_type, "-d") == 0)
        CreateDIr(input_path, path);

    else if(strcmp(file_type, "-l") == 0)
        {
            if(path != NULL)
                {
                    if(symlink(input_path, path) != 0)
                        perror("");
                }
                else 
                printf("Must provide the target!");
        }

        
}

//pharse the command
char** getComand ( char *input_line) {
    char **array;
    char *p;
    int i = 0;

    array = malloc(sizeof(char*)*100);
    for(int i = 0 ; i < 10; i++)
        array[i] = (char*)malloc(sizeof(char*) * 300);
    p = strtok(input_line, " ");

    while(p != NULL) {
        strcpy(array[i], p);
        p = strtok(NULL, " ");
        i++;
    }
    array[i] = NULL;
    return array;
}

//print wich kind of type is the path
void type(const char* path) {
    if( lstat(path, &file_info) == -1)
        perror("type()");

    if(S_ISREG(file_info.st_mode))
        printf("%s: Regular file\n", path);
    
    if(S_ISDIR(file_info.st_mode))
        printf("%s: Directory file\n", path);

    if(S_ISLNK(file_info.st_mode))
        printf("%s: Link file\n", path);
}

//this function is made in order to tun a command without pipe
void forkFunction(char *command, char **command_list)
{
    int pid;
    int status_code1;
    for(int i = 0; command_list[i] != NULL; i++) {
        command_list[i] = command_list[i + 1];
    }
    if((pid = fork()) < 0){
        perror("Error at creating child proccess!");
    }
    if (pid == 0){
        status_code1 = execvp(command, command_list);
        if(status_code < -1){
            perror("Eroare la execvp");
        }
        exit(status_code1);
    }
    else {
    

    if ( waitpid(pid, &status_code, 0) == -1 ) {
        perror("waitpid failed");
    }
     
     WEXITSTATUS(status_code);
    }
}

//exclude the run word from the command
void modifyList(char ** command_list, char **command_list1, char **command_list2)
{



    int i = 0;
    for(i = 1; command_list[i] != NULL && strcmp(command_list[i],"|") != 0; i++){
        strcpy(command_list1[i - 1],command_list[i]);
    }

    command_list1[i - 1] = NULL;
    int j = 0;
    if(command_list[i] != NULL){
        i++;
        for(j = 0; command_list[i] != NULL; j++) {
             strcpy(command_list2[j],command_list[i]);
             i++;
        }
    }
        command_list2[j] = NULL;
}

// Run an command with pipe
void Run(char *command, char** command_list)
{
    pid_t pid1;
    pid_t pid2;
    char **command_list1;
    char **command_list2;
    int pfd[2];


    command_list1 = malloc(sizeof(char*)*100);
    command_list2 = malloc(sizeof(char*)*100);
    for(int i = 0 ; i < 10; i++){
        command_list1[i] = (char*)malloc(sizeof(char*) * 300);
        command_list2[i] = (char*)malloc(sizeof(char*) * 300);
    }

    modifyList(command_list, command_list1, command_list2);

    if(pipe(pfd)<0)
	{
	  perror("Pipe creation error\n");
	  exit(1);
	}
    if((pid1 = fork()) < 0){
        perror("Error at creating child proccess!");
    }

    if (pid1 == 0){
        close(STDOUT_FILENO); //block the standard output
        dup(pfd[1]); //create another file descriptor that point to the same as pfd[1]
        close(pfd[0]);
        close(pfd[1]);

        status_code = execvp(command, command_list1);
        if(status_code <= -1){
            perror("Eroare la execvp ");
        }
    }else if(pid1 != 0){
      
    if((pid2 = fork()) < 0){
        perror("Error at creating child proccess!");
    }

    if (pid2 == 0){
        close(STDIN_FILENO);
        dup(pfd[0]);
        close(pfd[1]);
        close(pfd[0]);

        status_code = execvp(command_list2[0], command_list2);
        if(status_code <= -1){
            perror("Eroare la execvp ");
        }
    }else if(pid2 != 0){
        close(pfd[0]);
        close(pfd[1]);
        waitpid(pid2, &status_code, 0);
        waitpid(pid1, &status_code, 0); 
        WEXITSTATUS(status_code);
    } 
 
    }
}

//check the next command is a pipe or not
int check(char **command_list)
{
    for(int i = 0 ; command_list[i] != NULL; i++)
    {
        if(strcmp(command_list[i], "|") == 0)
            return 0;
    }
    return 1;
}
