#include <stdio.h>
// #include "structures.c"
#include <sys/socket.h>
#include <fcntl.h>
#include<string.h>
#include <sys/stat.h>
#include<stdbool.h>
bool login_student(int client_socket,int id,char* password)
{
    // printf("%d",id);
    // printf("%s",password);
    int file=open("student.txt",O_RDONLY);
    struct StudentDetail log_student;
    ssize_t read_result;
    int found=0;

    //reading file and checking if id and passwords match
    while(read(file,&log_student,sizeof(struct StudentDetail)))
    {
        if(log_student.id==id)
        {
           if(strcmp(log_student.password,password)==0)
           {
            found=1;
            break;
           }
        }
    }
    close(file);
    return found;    
}
