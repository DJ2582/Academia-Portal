#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "structures.c"
#define PORT 4567
int main() {
    int client_socket;
    struct sockaddr_in server_address;

    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    //AF_NET is ipv4
    //SOCK_STREAM is for TCP
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // Convert IP address from string to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    printf("Successfully created connection with server.\n");

    //recieving main menu prompt and writing to standard output
    char buf[200];
    int recvdata = recv(client_socket,&buf,sizeof(buf),0);
    int writedata = write(1,buf,recvdata);
    
    //taking user choice to login as
    char choiceprompt[] ="Enter your choice : ";
    writedata = write(1,choiceprompt,sizeof(choiceprompt));

    char readchoice;
    int choice = read(0,&readchoice,sizeof(readchoice));

    //sending choice to server
    int senddata = send(client_socket,&readchoice,sizeof(readchoice),0);

    if(readchoice=='1')
    {
     char server_response_admin[512];
     memset(server_response_admin,'\0',512*sizeof(char));
     //strcpy(server_response_admin,"");
     recv(client_socket, &server_response_admin, sizeof(server_response_admin), 0);
    while(1)
    {
        //admin menu
        printf("%s",server_response_admin);
        //taking choice from that admin menu
        char choice_admin;
        printf("Enter your choice admin: ");
        scanf(" %c", &choice_admin);
        send(client_socket, &choice_admin, sizeof(choice_admin), 0);
        if(choice_admin=='9') break;
        //add student
        if(choice_admin=='1')
        {
        // struct StudentDetail newStudent;
           char buffer[512],ques[30];
            memset(&ques,0,sizeof(ques));
            recv(client_socket,&ques,sizeof(ques),0);
            printf("%s",ques);
            memset(ques,0,sizeof(ques));
            scanf("%s",ques);
            send(client_socket,ques,sizeof(ques),0);
            memset(&ques,0,sizeof(ques));

            recv(client_socket,&ques,sizeof(ques),0);
            printf("%s",ques);
            memset(ques,0,sizeof(ques));
            // getchar();
            scanf("%s",ques);
            send(client_socket,ques,sizeof(ques),0);
            memset(&ques,0,sizeof(ques));

            recv(client_socket,&ques,sizeof(ques),0);
            printf("%s",ques);
            memset(ques,0,sizeof(ques));
            scanf("%s",ques);
            send(client_socket,ques,sizeof(ques),0);
            memset(&ques,0,sizeof(ques));

            recv(client_socket,&ques,sizeof(ques),0);
            printf("%s",ques);
            memset(ques,0,sizeof(ques));
            scanf("%s",ques);
            send(client_socket,ques,sizeof(ques),0);
            memset(&ques,0,sizeof(ques));

            char rec_msg[512];
            recv(client_socket, &rec_msg, sizeof(rec_msg), 0);
            printf("%s\n", rec_msg);
     }
     if(choice_admin=='2')
     {
        // char rec_msg[50];
        // memset(&rec_msg,0,sizeof(rec_msg));
        // recv(client_socket,rec_msg,sizeof(rec_msg),0);
        // printf("%s",rec_msg);
        
        // char send_id[10];
        // // memset(&send_id,0,sizeof(send_id));
        // scanf("%s",send_id);
        // send(client_socket,send_id,sizeof(send_id),0);

        // char sent_detail[300];
        // memset(&sent_detail,0,sizeof(sent_detail));
        // recv(client_socket,&sent_detail,sizeof(sent_detail),0);
        // printf("%s",sent_detail);

        char idprompt[50];
        memset(idprompt,0,sizeof(idprompt));
        recv(client_socket,idprompt,sizeof(idprompt),0);
        printf("%s",idprompt);

        //sending id
        char send_id[10];
        scanf("%s",send_id);
        send(client_socket,send_id,sizeof(send_id),0);

        //recieving the student data
        char studentData[300];

        memset(studentData,0,sizeof(studentData));
        recv(client_socket,&studentData,sizeof(studentData),0);
        printf("%s",studentData);   
     }
    if(choice_admin=='3')
    {
       // struct StudentDetail newStudent;
        char ques1[30];
        memset(&ques1,0,sizeof(ques1));

        recv(client_socket,&ques1,sizeof(ques1),0);
        printf("%s",ques1);
        memset(ques1,0,sizeof(ques1));
        scanf("%s",ques1);
        send(client_socket,ques1,sizeof(ques1),0);
        memset(&ques1,0,sizeof(ques1));

        recv(client_socket,&ques1,sizeof(ques1),0);
        printf("%s",ques1);
        memset(ques1,0,sizeof(ques1));
        scanf("%s",ques1);
        send(client_socket,ques1,sizeof(ques1),0);
        memset(&ques1,0,sizeof(ques1));

        recv(client_socket,&ques1,sizeof(ques1),0);
        printf("%s",ques1);
        memset(ques1,0,sizeof(ques1));
        scanf("%s",ques1);
        send(client_socket,ques1,sizeof(ques1),0);
        memset(&ques1,0,sizeof(ques1));

        recv(client_socket,&ques1,sizeof(ques1),0);
        printf("%s",ques1);
        memset(ques1,0,sizeof(ques1));
        scanf("%s",ques1);
        send(client_socket,ques1,sizeof(ques1),0);
        memset(&ques1,0,sizeof(ques1));

        recv(client_socket,&ques1,sizeof(ques1),0);
        printf("%s",ques1);
        memset(ques1,0,sizeof(ques1));
        scanf("%s",ques1);
        send(client_socket,ques1,sizeof(ques1),0);
        memset(&ques1,0,sizeof(ques1));

        char received_msg[512];
        recv(client_socket, &received_msg, sizeof(received_msg), 0);
        printf("%s\n", received_msg);
     }

     if(choice_admin=='4')
     {
        // char rec_msg[50];
        // memset(&rec_msg,0,sizeof(rec_msg));
        // recv(client_socket,rec_msg,sizeof(rec_msg),0);
        // printf("%s",rec_msg);
        
        // char send_id[10];
        // // memset(&send_id,0,sizeof(send_id));
        // scanf("%s",send_id);
        // send(client_socket,send_id,sizeof(send_id),0);

        // char sent_detail[300];
        // memset(&sent_detail,0,sizeof(sent_detail));
        // recv(client_socket,&sent_detail,sizeof(sent_detail),0);
        // printf("%s",sent_detail);

        char id_prompt[50];
        memset(id_prompt,0,sizeof(id_prompt));
        recv(client_socket,id_prompt,sizeof(id_prompt),0);
        printf("%s",id_prompt);

        //sending id
        char send_id1[10];
        scanf("%s",send_id1);
        send(client_socket,send_id1,sizeof(send_id1),0);

        //recieving the student data
        char student_data[300];

        memset(student_data,0,sizeof(student_data));
        recv(client_socket,&student_data,sizeof(student_data),0);
        printf("%s",student_data);   
     }
     if(choice_admin=='7')
     {

        char get_id[30],set_id[30];
        // int set_id;
        memset(get_id,0,sizeof(get_id));
        recv(client_socket,get_id,sizeof(get_id),0);
        printf("%s",get_id);
        scanf("%s",set_id);
        send(client_socket,set_id,sizeof(int),0);

        char get_field[30],set_field[30];
        memset(get_field,0,sizeof(get_field));
        recv(client_socket,get_field,sizeof(get_field),0);
        printf("%s",get_field);
        scanf("%s",set_field);
        send(client_socket,set_field,sizeof(set_field),0);

        char get_value[30],set_value[30];
        memset(get_value,0,sizeof(get_value));
        recv(client_socket,get_value,sizeof(get_value),0);
        printf("%s",get_value);
        scanf("%s",set_value);
        send(client_socket,set_value,sizeof(set_value),0);

        char gotit[40];
        memset(gotit,0,sizeof(gotit));
        recv(client_socket,&gotit,sizeof(gotit),0);
        printf("%s",gotit);
     }

     if(choice_admin=='8')
     {

        char get_id[30],set_id[30];
        // int set_id;
        memset(get_id,0,sizeof(get_id));
        recv(client_socket,get_id,sizeof(get_id),0);
        printf("%s",get_id);
        scanf("%s",set_id);
        send(client_socket,set_id,sizeof(int),0);

        char get_field[30],set_field[30];
        memset(get_field,0,sizeof(get_field));
        recv(client_socket,get_field,sizeof(get_field),0);
        printf("%s",get_field);
        scanf("%s",set_field);
        send(client_socket,set_field,sizeof(set_field),0);

        char get_value[30],set_value[30];
        memset(get_value,0,sizeof(get_value));
        recv(client_socket,get_value,sizeof(get_value),0);
        printf("%s",get_value);
        scanf("%s",set_value);
        send(client_socket,set_value,sizeof(set_value),0);

        char gotit[40];
        memset(gotit,0,sizeof(gotit));
        recv(client_socket,&gotit,sizeof(gotit),0);
        printf("%s",gotit);
     }

    } 
}
    close(client_socket);
    return 0;
}