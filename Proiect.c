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

void pwd();
void CreateDIr(const char *directory_name, const char *path);
void createRegular(const char *file_name, const char *path);

int main(){
    pwd();
    createRegular("file.txt", NULL);
    CreateDIr("file", NULL);
    return 0;
}

void pwd() {
       char cwd[256];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("%s", cwd);
   } else {
       perror("getcwd() error");
   }
}

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
}

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