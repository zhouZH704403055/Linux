#include<iostream>
#include<signal.h>
#include<unistd.h>
using namespace std;
void handler(int signo)
{
    ;
}
int Mysleep(int sec)
{
    struct sigaction act;
    struct sigaction oldact;
    act.sa_handler=handler;
    sigemptyset(&act.sa_mask);
    sigaction(SIGALRM,&act,&oldact);
    alarm(sec);
    pause();
    int ret=alarm(0);
    sigaction(SIGALRM,&oldact,NULL);
    return ret;
}

int main()
{
    while(1)
    {
        Mysleep(1);
        cout<<"wake up..."<<endl;
    }
    return 0;
}
