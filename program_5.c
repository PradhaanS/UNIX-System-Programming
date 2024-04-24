#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
void file_lock(int fd) {
	struct flock fl;
	fl.l_type = F_WRLCK; // Write lock
	fl.l_whence = SEEK_SET;
	fl.l_start = 0;
	fl.l_len = 0; // Lock entire file
	// Attempt to acquire the lock
	if (fcntl(fd, F_SETLKW, &fl) == -1) {
		perror("fcntl");
		exit(EXIT_FAILURE);
	}
	printf("File locked successfully!\n");
}

void file_unlock(int fd) {
	struct flock fl;
	fl.l_type = F_UNLCK; // Unlock
	fl.l_whence = SEEK_SET;
	fl.l_start = 0;
	fl.l_len = 0; // Unlock entire file
	// Attempt to release the lock
	if (fcntl(fd, F_SETLK, &fl) == -1) {
		perror("fcntl");
		exit(EXIT_FAILURE);
	}
	printf("File unlocked successfully!\n");
}

int main() {
	int fd;
	char *filename = "test.txt";
	// Open the file
	if ((fd = open(filename, O_RDWR | O_CREAT, 0666)) == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}
	// Write some content to the file
	if (write(fd, "Hello, world!\n", 14) != 14) {
		perror("write");
		exit(EXIT_FAILURE);
	}
	// Lock the file
	file_lock(fd);
	// Try to write to the locked file
	if (write(fd, "Locked file content\n", 20) == -1) {
		perror("write");
		printf("Error: Cannot write to the locked file.\n");
	}
	// Unlock the file
	file_unlock(fd);
	// Write to the unlocked file
	if (write(fd, "Unlocked file content\n", 22) != 22) {
		perror("write");
		exit(EXIT_FAILURE);
	}
	// Close the file
	close(fd);
	return 0;
}
