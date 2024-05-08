#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#define FIFO_FILE "/tmp/myfifo"
int main() 
{
	char buf[256];
	int fd;
	// Create the FIFO (named pipe)
	mkfifo(FIFO_FILE, 0666);
	// Parent process writes to the FIFO
	if (fork() != 0) 
	{
		fd = open(FIFO_FILE, O_WRONLY);
		write(fd, "Hello from parent!", sizeof("Hello from parent!"));
		close(fd);
	}
	// Child process reads from the FIFO
	else 
	{
		fd = open(FIFO_FILE, O_RDONLY);
		read(fd, buf, sizeof(buf));
		printf("Child received: %s\n", buf);
		close(fd);
	}
	return 0;
}
