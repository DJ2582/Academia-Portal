#include <stdio.h>
#include <sys/socket.h>
void handle_student(int client_socket) {
    // Implement student-specific functionality here
    char message[] = "Welcome, student!\n";
    send(client_socket, message, sizeof(message), 0);

    // Additional interactions with the client using client_socket...
}
