#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include "structures.c"

void main(){
	
	int fd = open("enrolled_courses.txt", O_RDWR);
	struct course_enrolled c;
	//int i = 0;
	printf("student_id,faculty_id,course_name,course_id,enrolled\n");
	while(read(fd, &c, sizeof(struct course_enrolled))){
		printf("%d          %d          %s          %d          %d\n",c.student_id,c.faculty_id,c.course_name,c.course_id,c.enrolled);
	}
}
