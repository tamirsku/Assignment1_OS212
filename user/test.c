
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/syscall.h"

int
main(void)
{
  int mask = (1 << SYS_getpid) | (1 << SYS_fork) | (1 << SYS_kill);
  trace(mask);
  if(fork() == 0){
      mask = (1 << SYS_fork) | (1 << SYS_kill);
      trace(mask);
      getpid();
  }
  else{
      getpid();
      kill(3);
  }
  exit(0);
}
