#include"comm.h"
static int CommGetMsgQueue(int flag)
{
    key_t k=ftok(PATHNAME,PROJID);
    if(k<0)
    {
        printf("ftok error!\n");
        return -1;
    }
    int msgid=msgget(k, flag);
    if(msgid<0)
    {
        printf("msgget error!\n");
    }
    return msgid;
}

int CreateMsgQueue()
{
    return CommGetMsgQueue(IPC_CREAT | IPC_EXCL | 0666);
}

int OpenMsgQueue()
{
    return CommGetMsgQueue(IPC_CREAT);
}

void DestroyMsgQueue(int msgid)
{
    msgctl(msgid,IPC_RMID,NULL);
}

void SendMsg(int msgid,char msg[],int type)
{
    struct msgbuf msgp;
    msgp.mtype=type;
    strcpy(msgp.mtext,msg);
    if(msgsnd(msgid,&msgp,sizeof(msgp.mtext),0)<0)
    {
        printf("msgsnd error!\n");
    }
}

void RecvMsg(int msgid,char msg[],int type)
{
    struct msgbuf msgp;
    int ret=msgrcv(msgid,&msgp,sizeof(msgp.mtext),SERVER_TYPE,0);
    if(ret>0)
    {
        strcpy(msg,msgp.mtext);
    }
}
