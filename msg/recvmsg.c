// recvmsg.c

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
}msg;

int main()
{
	key_t key = ftok("./", 88);

	// 获取消息队列
	int msgid = msgget(key, 0);
	if(-1 == msgid)
	{
		perror("msgget failed!!!");
		exit(1);
	}

	int res = msgrcv(msgid, &msg, sizeof(msg),
			2, // 取消息类型为2的消息
			0);
	printf("类型：%d, 内容：%s\n", msg.mtype, msg.buf);

	printf("消息接收完成，按回车销毁消息队列\n");
	getchar();

	if(-1 == shmctl(msgid, IPC_RMID, NULL))
	{
		perror("shmctl failed");
		exit(2);
	}
	return 0;
}
