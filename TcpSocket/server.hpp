#pragma once

#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<strings.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string>
#include<cstring>
//#include<signal.h>
#include<sys/wait.h>
#include<pthread.h>

using std::cout;
using std::cerr;
using std::endl;

class Server;
struct Pthread_data
{
    Server* pServer;
    int accept_fd;
};

class Sock
{
public:
    //Sock(const std::string &ip,const int &port)
    //    :sock_fd(-1),_ip(ip),_port(port)
    //{
    //    ;
    //}
    Sock(const int &port)
        :sock_fd(-1),_port(port)
    {
        ;
    }
    void Socket()
    {
        sock_fd=socket(AF_INET,SOCK_STREAM,0);
        if(sock_fd<0)
        {
            cerr<<"socket error!!!"<<endl;
            exit(1);
        }
    }
    void Bind()
    {
        struct sockaddr_in local;
        bzero(&local,sizeof(local));
        local.sin_family=AF_INET;
        local.sin_port=htons(_port);
        //local.sin_addr.s_addr=inet_addr(_ip.c_str());
        local.sin_addr.s_addr=htonl(INADDR_ANY);
        if(bind(sock_fd,(struct sockaddr*)&local,sizeof(local))<0)
        {
            cerr<<"bind error!!!"<<endl;
            exit(2);
        }
    }
    void Listen()
    {
        if(listen(sock_fd,5)<0)
        {
            cerr<<"listen error!!!"<<endl;
            exit(3);
        }
    }
    int Accept()
    {
        struct sockaddr_in peer;
        socklen_t len=sizeof(peer);
        int accept_fd=accept(sock_fd,(struct sockaddr*)&peer,&len);
        if(accept_fd<0)
        {
            cerr<<"accept error!!!"<<endl;
            return -1;
        }
        return accept_fd;
    }
private:
    int sock_fd;
    //std::string _ip;
    int _port;
};

class Server
{
 public:
     //Server(const std::string &ip,const int &port)
     //    :sock(ip,port)
     //{
     //    ;
     //}
     Server(const int &port)
         :sock(port)
     {
         ;
     }
     void InitServer()
     {
         //signal(SIGCHLD,SIG_IGN);
         sock.Socket();
         sock.Bind();
         sock.Listen();
     }
     void Service(int fd)
     {
         char buf[1024]={0};
         while(1)
         {
             ssize_t r_sz=read(fd,buf,sizeof(buf)-1);
             if(r_sz==0)
             {
                 cout<<"客户端退出！！！"<<endl;
                 break;
             }
             else if(r_sz>0)
             {
                 buf[r_sz]=0;
                 cout<<buf<<endl;
                 write(fd,"OJBK",5);
             }
             else
             {
                 cerr<<"read error!!!"<<endl;
                 break;
             }
         }
         close(fd);
     }
     static void* ThreadRun(void* arg)
     {
         pthread_detach(pthread_self());
         Pthread_data* p=(Pthread_data*)arg;
         Server* pServer=p->pServer;
         int accept_fd=p->accept_fd;
         delete p;
         pServer->Service(accept_fd);
     }
     void Run()
     {
         while(1)
         {
             int accept_fd = sock.Accept();
             if(accept_fd<0)
             {
                 continue;
             }
             cout<<"连接到一个新客户端！！"<<endl;
             Pthread_data* p=new Pthread_data;
             p->pServer=this;
             p->accept_fd=accept_fd;
             pthread_t tid;
             pthread_create(&tid,NULL,ThreadRun,p);
             //pid_t pid=fork();
             //if(pid==0)
             //{
             //    //child
             //    Service(accept_fd);
             //    exit(0);
             //}
             //else if(pid>0)
             //{
             //    //parent
             //    close(accept_fd);
             //}
             //else
             //{
             //    cerr<<"fork error!!!"<<endl;
             //    break;
             //}
         }
     }
private:
     Sock sock;
};
