#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
void create_zombie_process() {
     pid_t pid = fork();
     if (pid == -1) {
         perror("fork");
         exit(EXIT_FAILURE);
     } 
     else if (pid > 0) {
         // Parent process
         printf("Parent process created a zombie process (PID: %d)\n", pid);
     } 
     else {
         // Child process
         printf("Zombie process created (PID: %d)\n", getpid());
         exit(EXIT_SUCCESS);
     }
}
void prevent_zombie_processes() {
     pid_t pid = fork();
     if (pid == -1) {
         perror("fork");
         exit(EXIT_FAILURE);
     } 
     else if (pid > 0) {
         // Parent process
         printf("Parent process created a child process (PID: %d)\n", pid);
         sleep(2); // Wait for child to exit
     } 
     else {
         // First child process
         pid = fork();
         if (pid == -1) {
             perror("fork");
             exit(EXIT_FAILURE);
         } 
         else if (pid > 0) {
             // First child process exits immediately
             printf("First child process (PID: %d) exited\n", getpid());
             exit(EXIT_SUCCESS);
         } 
         else {
             // Grandchild process
             printf("Grandchild process (PID: %d)\n", getpid());
             sleep(5); // Simulate some work
             printf("Grandchild process completed\n");
             exit(EXIT_SUCCESS);
        }
    } 
}
void create_orphan_process() {
     pid_t pid = fork();
     if (pid == -1) {
         perror("fork");
         exit(EXIT_FAILURE);
     } 
     else if (pid > 0) {
         // Parent process
         printf("Parent process (PID: %d)\n", getpid());
         sleep(2); // Let parent exit first
     } 
     else {
         // Child process becomes orphan
         printf("Orphan process created (PID: %d)\n", getpid());
         sleep(5); // Simulate some work
         printf("Orphan process completed\n");
         exit(EXIT_SUCCESS);
     }
}
void parent_child_scenario() {
     pid_t pid = fork();
     if (pid == -1) {
         perror("fork");
         exit(EXIT_FAILURE);
     } 
     else if (pid > 0) {
         // Parent process
         printf("Parent process (PID: %d)\n", getpid());
         wait(NULL); // Wait for child to complete
     } 
     else {
         // Child process
         printf("Child process (PID: %d)\n", getpid());
         exit(EXIT_SUCCESS);
     }
}
int main() {
     printf("Demonstrating Zombie process:\n");
     create_zombie_process();
     sleep(5); // Wait for the zombie process to become defunct
     printf("\nPreventing Zombie processes:\n");
     prevent_zombie_processes();
     sleep(7); // Wait for grandchild process to complete
     printf("\nCreating an Orphan process:\n");
     create_orphan_process();
     printf("\nParent-Child scenario:\n");
     parent_child_scenario();
     return 0;
}
