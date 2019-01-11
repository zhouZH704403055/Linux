#include<iostream>
#include<unistd.h>
#include<signal.h>
using namespace std;
void handler(int signo)
{
    cout<<"catch a sig : "<<signo<<endl;
}

int main()
{
    struct sigaction act;
    struct sigaction oldact;
    act.sa_handler=SIG_DFL;
    sigemptyset (&act.sa_mask);
    sigaction(2,&act,&oldact);
    int ret=pause();
    cout<<ret<<endl;
    while(1)
    {
        cout<<"Hello World!"<<endl;
        sleep(1);
    }
    return 0;
}
