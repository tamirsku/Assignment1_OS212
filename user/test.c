
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/syscall.h"
#include "kernel/performence.h"


int
main(void)
{
  struct perf p;
  int mask = (1 << SYS_wait_stat) | (1 << SYS_fork) | (1 << SYS_set_priority);

  trace(mask);
  if(fork() == 0){
    sleep(7);
    set_priority(5);
  }
  else{
    wait_stat(0,&p);  
    printf("create: %d\n finish: %d\n running: %d\n runnable: %d\n sleep: %d \n btime: %d\n",p.ctime,p.ttime,p.rutime,p.retime,p.stime,p.average_bursttime);
  }

  exit(0);
}
