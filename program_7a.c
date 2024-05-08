#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() 
{
	int pipefd[2];
	if (pipe(pipefd) == -1) 
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid_t pid = fork();
	if (pid == -1) 
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) // Child process
	{ 
		close(pipefd[0]); // Close reading end of the pipe in the child process
		dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to the writing end of the pipe
		close(pipefd[1]); // Close the original writing end of the pipe
		execlp("ls", "ls", "-l", NULL); // Execute the first command
		perror("execlp ls");
		exit(EXIT_FAILURE);
	}
	else // Parent process
	{ 
		close(pipefd[1]); // Close writing end of the pipe in the parent process
		dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to the reading end of the pipe
		close(pipefd[0]); // Close the original reading end of the pipe
		execlp("wc", "wc", "-l", NULL); // Execute the second command
		perror("execlp wc");
		exit(EXIT_FAILURE);
	}
	return 0;
}
