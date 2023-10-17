#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include "structures.c"

/*
{
    int id;
    int faculty_id;
    char name[50];
    char department[50];
    int seat;
    int credit;
    int max_seats;
}
*/

void main(){
	
	int fd = open("course.txt", O_RDWR);
	struct CourseDetail c;
	//int i = 0;
	printf("c.id,c.faculty_id,c.name,c.department,c.seat,c.credit,c.max_seats\n");
	while(read(fd, &c, sizeof(struct CourseDetail))){
		printf("%d   %d   %s   %s   %d   %d   %d\n",c.id,c.faculty_id,c.name,c.department,c.seat,c.credit,c.max_seats);
	}
}