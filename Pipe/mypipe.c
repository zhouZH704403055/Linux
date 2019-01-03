#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int main()
{
    int fd[2];//0表示读，1表示写
    if(pipe(fd)<0)
    {
        printf("pipe error!\n");
        return 1;
    }
    pid_t id=fork();
    if(id==0)//子进程
    {
        close(fd[0]);
        const char* str="I am child.I am write!";
        int i=0;
        //for(i=0;i<5;i++)
        // {
        //    write(fd[1],str,strlen(str));
        //    printf("child write done!\n");
        //    //sleep(1);
        //}
        while(1)
        {
            write(fd[1],str,strlen(str));
            printf("child write done! : %d\n",i++);
        }
        close(fd[1]);
        exit(0);
    }
    else{//父进程
        close(fd[1]);
        char buff[1024];
        while(1)
        {
            sleep(5);
            ssize_t s=read(fd[0],buff,sizeof(buff)-1);
            if(s>0)
            {
                buff[s]=0;
                printf("father recv done : %s \n",buff);
            }
            else if(s==0)
            {
                printf("child quit! father quit!\n");
                break;
            }
        }
        waitpid(id,NULL,0);
        close(fd[0]);
    }
    return 0;
}
