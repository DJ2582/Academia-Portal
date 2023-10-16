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

void view_all_course(int client_socket)
{
    int fd=open("course.txt",O_RDWR);
    if(fd==-1)
    {
        perror("ERROR:");
    }
    struct CourseDetail course_view;
    int ack=1;
    while(read(fd,&course_view,sizeof(course_view)))
    {
    
        send(client_socket,&ack,sizeof(ack),0);
        send(client_socket,&course_view,sizeof(course_view),0);
    }
    ack=0;
    send(client_socket,&ack,sizeof(ack),0);
}

void view_enrolled_course(int client_socket,int id)
{
    // printf("hi\n");
    int fd=open("enrolled_courses.txt",O_RDWR);
    if(fd==-1)
    {
        perror("ERROR:");
    }
    struct course_enrolled course;
    int ack=1;
    // printf("after 1\n");
    while(read(fd,&course,sizeof(course)))
    {
        if(course.student_id==id)
        {
            send(client_socket,&ack,sizeof(ack),0);
            send(client_socket,&course,sizeof(course),0);
        }
    }
    ack=0;
    send(client_socket,&ack,sizeof(ack),0);
}

void enroll_course(int client_socket,int student_id,int course_id)
{
    //open faculty file 
   int fd=open("faculty.txt",O_RDONLY);
    
   //open course file
   int fd2=open("course.txt",O_RDWR);

   //open enrolled courses file
   int fd3=open("enrolled_courses.txt",O_RDWR);

   struct CourseDetail course;

   while(read(fd2,&course,sizeof(struct CourseDetail)))
   {
    if(course.id==course_id)
    {
        if(course.seat>0)
        {
            lseek(fd2,-(sizeof(struct CourseDetail)),SEEK_CUR);
            struct CourseDetail course_copy;
            // printf("fetch course id:%d\n",course_copy.id);
            // printf("fetch course department:%s\n",course_copy.department);
            // printf("fetch course name:%s\n",course_copy.name);
            // printf("fetch course seat:%d\n",course_copy.seat);

            course_copy.id=course_id;
            course_copy.faculty_id=course.faculty_id;
            strcpy(course_copy.name,course.name);
            strcpy(course_copy.department,course.department);
            course_copy.seat=course.seat-1;
            course_copy.credit=course.credit;
            write(fd2,&course_copy,sizeof(struct CourseDetail));
            send(client_socket,"Successfully Enrolled\n",sizeof("Successfully Enrolled"),0);
            printf("available seats:%d\n",course_copy.seat);

            struct course_enrolled course_en;
            course_en.student_id=student_id;
            course_en.course_id=course_id;
            strcpy(course_en.course_name,course.name);
            course_en.faculty_id=course.faculty_id;

            printf("course name:%s\n",course_en.course_name);
            printf("course id:%d\n",course_en.course_id);
            printf("student id:%d\n",course_en.student_id);
            printf("faculty id:%d\n",course_en.faculty_id);
            lseek(fd3,0,SEEK_END);
            write(fd3,&course_en,sizeof(struct course_enrolled));
            
        }
        else
        {
            send(client_socket,"Sorry No Seats Available.....\n",sizeof("Sorry No Seats Available...Try Later Sometime"),0);
        }
    }
  }

}

void change_password_student(int client_socket,int id,char* password)
{
    int fd=open("student.txt",O_RDWR);
    if(fd==-1)
    {
        perror("ERROR:");
    }
    struct StudentDetail stu;
    while(read(fd,&stu,sizeof(stu)))
    {
        if(stu.id==id)
        {
            strcpy(stu.password,password);
            printf("%s",stu.password);
            lseek(fd, -sizeof(stu), SEEK_CUR); // Move the file pointer back to the beginning of the record
            write(fd, &stu, sizeof(stu)); 
            char password_sent[30]="password change successfully..";
            send(client_socket,password_sent,sizeof(password_sent),0);
            break; 
        }   
    }
}
