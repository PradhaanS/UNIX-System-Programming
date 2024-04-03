#include<stdio.h>
#include<unistd.h>
#include<limits.h>
int main()
{
	printf("Maximum number of clocks per second : %ld\n",sysconf(_SC_CLK_TCK));
	printf("Maximum number of child processes: %ld\n",sysconf(_SC_CHILD_MAX));
	printf("Maximum path length: %ld\n",pathconf("/",_PC_PATH_MAX));
	printf("Maximum number of characters in a file name: %ld\n",pathconf("/",_PC_NAME_MAX));
	printf("Maximum number of open files per process: %ld\n",sysconf(_SC_OPEN_MAX));
	printf("Systems page size: %ld bytes\n",sysconf(_SC_PAGESIZE));
	char hostname[HOST_NAME_MAX];
	if(gethostname(hostname,HOST_NAME_MAX)==0)
	{
		printf("System host name: %s\n",hostname);
	}
	else
	{
		perror("gethostname");
	}
	char cwd[PATH_MAX];
	if(getcwd(cwd,sizeof(cwd))!=NULL)
	{
		printf("Current working directory: %s\n",cwd);
	}
	else
	{
		perror("getcwd");
	}
	return 0;
}
		
