// sendmsg.c

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

struct my_msg
{
	int mtype; // 消息类型
	char buf[256];
}msg1, msg2;

int main()
{
	key_t key = ftok("./", 88);

	int msgid = msgget(key, 0666|IPC_CREAT);
	if(-1 == msgid)
	{
		perror("msgget failed!!!");
		exit(1);
	}

	msg1.mtype = 2;
	strcpy(msg1.buf, "hello, msg2");
	msgsnd(msgid, &msg1, sizeof(msg1), 0); // 阻塞
//	msgsnd(msgid, &msg1, sizeof(msg1), IPC_NOWAIT); // 非阻塞

	msg2.mtype = 1;
	strcpy(msg2.buf, "hello, msg1");
	msgsnd(msgid, &msg2, sizeof(msg2), 0); // 阻塞

	printf("消息发送完成，按回车销毁消息队列\n");
	getchar();

	if(-1 == shmctl(msgid, IPC_RMID, NULL))
	{
		perror("shmctl failed");
		exit(2);
	}
	return 0;
}
