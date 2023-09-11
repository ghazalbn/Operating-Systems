#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "user.h"
#include "x86.h"
int 
main (int argc, char *argv[])
{
         
      	int pid=fork();
	if(pid==0)
	{
		if(fork())
		{
			malloc(sizeof(int)*10000*1);
			
		      	while(1){}
				
             }
		else
		{
				
			malloc(sizeof(int)*10000*2);

			while(1){}

		}	

	}
else{
	
		sleep(10);
	int size;
        struct proc_info *info = malloc(sizeof(struct proc_info) * NPROC);
        proc_dump(info, &size);

        for (int i = 0; i < size; i++) {
            printf(1,"*pid*:          %d       *sz*:          %d    \n  ", info[i].pid, info[i].memsize);
        }

	exit();

}	
       
     		
}
        
