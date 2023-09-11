#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{   int t=0 ;
        int pid = fork();
        if (pid == 0)
        {
            fork();
            fork();
            fork();
            int pidx = getpid();
            if (pidx % 6 == 0)
            {
                //printf(1, "Initializing process %d, priority : %d\n", pidx, 90);
                set_priority(90, pidx);
            }
            else if (pidx % 6 == 1)
            {
                //printf(1, "Initializing process %d, priority : %d\n", pidx, 70);
                set_priority(80, pidx);
            }
            else if (pidx % 6 == 2)
            {
                //printf(1, "Initializing process %d, priority : %d\n", pidx, 80);
                set_priority(70, pidx);
            }
            else if (pidx % 6 == 3)
            {
                //printf(1, "Initializing process %d, priority : %d\n", pidx, 20);
                set_priority(60, pidx);
            }
            else if (pidx % 6 == 4)
            {
                //printf(1, "Initializing process %d, priority : %d\n", pidx, 50);
                set_priority(50, pidx);
            }

            else
            {
                //printf(1, "Initializing process %d, priority : %d\n", pidx, 60);
                set_priority(40, pidx);
            }
            
            for (int i = 0; i < getpid()*10000; i++) 
            {
                t++;
                if(t%500==0)
                    t=0;
                continue;
            }
            proc_stats();
            printf(1,"process with pid %d is done\n",pidx);
            exit();
        }
        else
        {   set_priority(100,getpid());
            wait();
            exit();
        }
        
    
}