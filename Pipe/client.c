#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#define FIFONAME "pipefile"

int main()
{
    int fd=open(FIFONAME,O_WRONLY);
    if(fd<0)
    {
        return 1;
    }
    char buf[1024];
    while(1)
    {
        printf("pleas enter your mesage to server# ");
        fflush(stdout);
        ssize_t s=read(0,buf,sizeof(buf)-1);
        buf[s]=0;
        write(fd,buf,strlen(buf));
    }
    return 0;
}
