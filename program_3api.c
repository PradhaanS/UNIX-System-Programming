#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		fprintf(stderr,"Usage: %s<source><destinstion>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	char *source=argv[1];
	char *destination= argv[2];
	if(link(source,destination)==-1)
	{
		perror("link");
		exit(EXIT_FAILURE);
	}
	if(unlink(source)==-1)
	{
		perror("link");
		exit(EXIT_FAILURE);
	}
	printf("File moved successfully\n");
	return 0;
}
	
