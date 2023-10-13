#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "admin.c"
#include "student.c"
#include "faculty.c"

void handle_client(int client_socket) {

    char string[20];
    char buff[] = "----------Welcome to Academia ----------\n"
    "Choose login type \n"
    "1. Admin\t 2. Student\t 3. Faculty\n";

    //sending menu to client
    int bytesSend = send(client_socket,&buff,sizeof(buff),0);

    //recieving choice from client
    int recvBytes = recv(client_socket,&string,sizeof(string),0);
    string[recvBytes] = '\0';  //append the null at the end
    int choice = atoi(string);

    if(choice==1)
    {
        char menu_student[] = "Choose from the following options\n" 
                                "1) Add Student \n"
                                "2) View Student Details \n"
                                "3) Add Faculty \n"
                                "4) View Faculty Details \n"
                                "5) Activate Student \n"
                                "6) Block Student \n"
                                "7) Modify Student Details \n"
                                "8) Modify Faculty Details \n"
                                "9) Logout and Exit \n";
        send(client_socket,menu_student,strlen(menu_student), 0);
        while(1)
        {
            //if choice is 1 send admin menu
            char student_choice;
            recv(client_socket, &student_choice,sizeof(student_choice), 0);
            //call to respective c functions
            if(student_choice=='9') break;
            if(student_choice=='1')
            {
                add_student(client_socket);
            }
            if(student_choice=='2')
            {
                view_student(client_socket);
            }
            if(student_choice=='3')
            {
                add_faculty(client_socket);
            }
            if(student_choice=='4')
            {
                view_faculty(client_socket);
            }
            if(student_choice=='7')
            {
                modify_student(client_socket);
            }
            if(student_choice=='8')
            {
                modify_faculty(client_socket);
            }
        }
     
    } 
    printf("\n");
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Error creating socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(4567);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding");
        exit(1);
    }

    if (listen(server_socket, 10) == 0) {
        printf("Server listening on port %d...\n", ntohs(server_addr.sin_port));
    } else {
        perror("Error listening");
        exit(1);
    }

    while (1) {
        addr_size = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);

        if (client_socket < 0) {
            perror("Error accepting client");
            exit(1);
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("Error forking");
            exit(1);
        } else if (pid == 0) {
            // Child process
            close(server_socket);
            handle_client(client_socket);
            exit(0);
        } else {
            // Parent process
            close(client_socket);
        }
    }
    return 0;
}