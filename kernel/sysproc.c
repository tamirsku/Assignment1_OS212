#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "syscall.h"

uint64
sys_exit(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  int          ret;
  struct proc *p = myproc();

  ret = fork();
  if(IS_BIT_ON(SYS_fork)) printf("syscall %s NULL -> %d\n",syscalls_to_string[SYS_fork - 1],ret);
  return ret;
}

uint64
sys_wait(void)
{
  uint64 p;
  if(argaddr(0, &p) < 0)
    return -1;
  return wait(p);
}

uint64
sys_sbrk(void)
{
  int          ret;
  int          addr;
  int          n;
  struct proc *p = myproc();

  if(argint(0, &n) < 0)
    ret = -1;
  else{
    addr = myproc()->sz;
    if(growproc(n) < 0)
      ret = -1;
    else ret = addr;
  }

  if(IS_BIT_ON(SYS_sbrk)) printf("syscall %s %d -> %d\n",syscalls_to_string[SYS_sbrk - 1],n,ret);
  return ret;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int          pid;
  int          ret;
  struct proc *p = myproc();

  if(argint(0, &pid) < 0)
    ret = -1;
  else ret = kill(pid);

  if(IS_BIT_ON(SYS_kill)) printf("syscall %s %d -> %d\n",syscalls_to_string[SYS_kill - 1],pid,ret);
  return ret;
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_trace(void)
{
  int mask;

  if(argint(0, &mask) < 0)
    return -1;
  
  trace(mask);

  return 0;
}

uint64
sys_wait_stat(void)
{
  // TODO
  return 0;
}