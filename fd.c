#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>

int main (int argc, char **argv)
{
	int fd, nfd;
	if(argc<2)
	{
		printf(" usage: %s pathname\n",argv[0]);
		exit(1);
	}
	if ((fd=open(argv[1], O_WRONLY))<0)
	{
		perror("Problem on opening the file");
		exit(1);
	}
	if((nfd=fcntl(fd,F_DUPFD,0))==-1)
	{
		perror("Problem in duplicating FD");
		exit(1);
	}
	
	printf("FD %d duplicated with %d\n",fd, nfd);
	
	close(fd);
	close(nfd);
	return 0;
	
}

		
