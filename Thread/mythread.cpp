#include<iostream>
#include<vector>
#include<pthread.h>
#include<sys/types.h>
#include<unistd.h>

using namespace std;
volatile int tickets=1000;
pthread_mutex_t lock;

void* BuyTicket(void* arg)
{
    int number=(int)arg;
    while(1)
    {
        usleep(100);
        pthread_mutex_lock(&lock);
        if(tickets>0)
        {
            usleep(1000);
            cout<<"thread "<<number<<" get a ticket: "<< tickets<<endl;
            tickets--;
            pthread_mutex_unlock(&lock);
        }
        else
        {
            pthread_mutex_unlock(&lock);
            break;
        }
    }
    return (void*)0;
}

struct thread_data
{
    int number;
    pthread_t tid;
};

int main()
{
    int num=10;
    vector<thread_data> thread_list(num);
    pthread_mutex_init(&lock,NULL);
    for(int i=0;i<thread_list.size();i++)
    {
        pthread_create(&(thread_list[i].tid),NULL,BuyTicket,(void*)i+1);
        thread_list[i].number=i+1;
    }
    cout<<"join begin..."<<endl;
    for(int i=0;i<thread_list.size();i++)
    {
        pthread_join(thread_list[i].tid,NULL);
    }
    pthread_mutex_destroy(&lock);
    return 0;
}
