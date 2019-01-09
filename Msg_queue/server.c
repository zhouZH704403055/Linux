#include"comm.h"
int main()
{
    int msgid=CreateMsgQueue();
    printf("msgid:%d\n",msgid);

    char* str="HELLO WORLD!";
    SendMsg(msgid,str,SERVER_TYPE);
    sleep(1);
    SendMsg(msgid,str,SERVER_TYPE);
    sleep(1);
    SendMsg(msgid,str,SERVER_TYPE);
    sleep(1);
    SendMsg(msgid,str,SERVER_TYPE);
    sleep(1);
    char buf[128];
    RecvMsg(msgid,buf,SERVER_TYPE);
    sleep(1);
    RecvMsg(msgid,buf,SERVER_TYPE);
    sleep(1);
    RecvMsg(msgid,buf,SERVER_TYPE);
    sleep(1);
    RecvMsg(msgid,buf,SERVER_TYPE);
    sleep(1);


    DestroyMsgQueue(msgid);
    return 0;
}
