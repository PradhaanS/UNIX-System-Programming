#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<mqueue.h>
#define QUEUE_NAME "/my_queue"
#define MAX_MSG_SIZE 256
void sender_process()
{
	mqd_t mqd;
	char msg[MAX_MSG_SIZE];
	mqd=mq_open(QUEUE_NAME,O_WRONLY);
	if(mqd==(mqd_t)-1)
	{
		perror("mq_open");
		exit(EXIT_FAILURE);
	}
	printf("Sender process:enter a message to send to reciever(type 'exit' to quit):\n");
	while(1)
	{
		fgets(msg,MAX_MSG_SIZE,stdin);
		if(mq_send(mqd,msg,strlen(msg),0)==-1)
		{
			perror("mq_send");
			exit(EXIT_FAILURE);
		}
		if(strncmp(msg,"exit",4)==0)
		{
			break;
		}
	}
	mq_close(mqd);
}
void receiver_process()
{
	mqd_t mqd;
	char msg[MAX_MSG_SIZE];
	ssize_t bytes_read;
	mqd=mq_open(QUEUE_NAME,O_RDONLY);
	if(mqd==(mqd_t)-1)
	{
		perror("mq_open");
		exit(EXIT_FAILURE);
	}
	printf("Receiver process: waiting for messages...\n");
	while(1)
	{
		bytes_read=mq_receive(mqd,msg,MAX_MSG_SIZE,NULL);
		if(bytes_read==-1)
		{
			perror("mq_receive");
			exit(EXIT_FAILURE);
		}
		msg[bytes_read]='\0';
		printf("Receive message: %s",msg);
		if(strncmp(msg,"exit",4)==0)
		{
			break;
		}
	}
	mq_close(mqd);
}
int main()
{
	struct mq_attr attr;
	attr.mq_flags=0;
	attr.mq_maxmsg=10;
	attr.mq_msgsize=MAX_MSG_SIZE;
	attr.mq_curmsgs=0;
	mqd_t mqd=mq_open(QUEUE_NAME,O_CREAT|O_RDWR,0666,&attr);
	if(mqd==(mqd_t)-1)
	{
		perror("mq_open");
		exit(EXIT_FAILURE);
	}
	pid_t pid=fork();
	if(pid==-1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if(pid==0)
	{
		receiver_process();
	}
	else
	{
		sender_process();
	}
	mq_unlink(QUEUE_NAME);
	return 0;
}
