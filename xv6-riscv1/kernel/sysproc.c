#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
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
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
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
  int pid;

  argint(0, &pid);
  return kill(pid);
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





//implementing the pgtPrint function here

int sys_pgtPrint()
{
  // accessign the pointer to the page directory
 // pte_t *pte = myproc()->pagetable;
  pagetable_t pagetable = myproc()->pagetable;
  
  // counter for the total number of valid entry
  int counter = 0;
  
  //storeage for virtual address 
  uint64 va=0;
  
  // for each entry in the page directory
  for(int i = 0 ; i < 512 ; i++)
  {
    pte_t pte= pagetable[i];
    
    if(pte & PTE_V)
    {
    
      uint64 pa1 = PTE2PA(pte);
      
      // for table in directory
      for(int j = 0 ; j < 512 ; j++)
      {
        
        pte_t pte2 = ((pagetable_t)pa1)[j];
     
        if (pte2 & PTE_V)
        {
          
          uint64 pa2 = PTE2PA(pte2);
          
        for(int k=0;k<512;k++)
        
        {    
         
           pte_t pte3 = ((pagetable_t)pa2)[k];
           
           //page tabel entry will the address

        if(pte3 & PTE_V)
        {
        
          uint64 pa3 = PTE2PA(pte3);
              printf("PTE No::%d, Virtual page address-: %p , Physical page address-: %p\n" , counter , va , pa3);
         counter++;
          
        }  
         
         //increasing the page size
         va+= PGSIZE;  //page size is definde in riscv.h

        }
      }  
      va= va + 512 * PGSIZE; 
    } 
  }
  va=va+512*512*PGSIZE; //as we have crossed 512 * 512 entry thus increasing the virtual addrss
  }
  return 0;
}


//implementing pgaccess function call 

int
sys_pgaccess(void)
{
  uint64 startaddr;
  int total_page;
  uint64 useraddr;
  
  //taking the argumner from the pgaccess.c function 
  argaddr(0, &startaddr);
  argint(1, &total_page);
  argaddr(2, &useraddr);

  uint64 bitmask = 0;
  
  //finding the compliment  using the negation sign
  uint64 compliment = ~PTE_A;
  
  struct proc *p = myproc();
  for (int i = 0; i < total_page; ++i) {
    pte_t *pte = walk(p->pagetable, startaddr+i*PGSIZE, 0);
    if (*pte & PTE_A & PTE_D) {
      bitmask |= (1 << i);
      *pte &= compliment;
    }
  }
  copyout(p->pagetable, useraddr, (char *)&bitmask, sizeof(bitmask));
  printf("coming out\n");
  return 0;
}




