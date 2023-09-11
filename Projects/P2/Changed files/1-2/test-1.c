#include "types.h"
#include "stat.h"
#include "user.h"
int main (int argc,char *argv[])
{
    int Status, a, b;
    int pid1=fork();
    if (pid1==0){
        int pid2=fork();
        sleep(300);
        if (pid2>0){
        Status=waitx(&a , &b);
        printf(1, "second: Wait Time = %d\n Run Time = %d Status = %d  pid=%d\n", a, b, Status,getpid());
        exit();
        }
        else{
            sleep(100);
            Status=waitx(&a,&b);
            printf(1, "third: Wait Time = %d\n Run Time = %d Status = %d  pid=%d\n", a, b, Status,getpid());
            exit();
        }
    }
    if (pid1>0){
        Status=waitx(&a , &b);
        printf(1, "first: Wait Time = %d\n Run Time = %d Status = %d  pid=%d\n", a, b, Status,getpid());
    }
  exit();  
}
