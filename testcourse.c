#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include "structures.c"

void main(){
	
	int fd = open("course.txt", O_RDWR);
	struct CourseDetail c;
	//int i = 0;
	printf("c.id,c.faculty_id,c.name,c.department,c.seat,c.credit,c.max_seats\n");
	while(read(fd, &c, sizeof(struct CourseDetail))){
		printf("%d   %d   %s   %s   %d   %d   %d\n",c.id,c.faculty_id,c.name,c.department,c.seat,c.credit,c.max_seats);
	}
}
