#include "kernel/types.h"
#include <kernel/stat.h>
#include <user/user.h>


#define limit 10000
int glob[limit];

int main(){

   printf("Address from user space is : %x\n" , glob);
  
    glob[0] = 1;

    for(int i = 1 ; i < limit ; i++){
        glob[i] = glob[i-1];
        if (i%1000 == 0) pgtPrint();
    }

    printf ("Printing final page table:\n");
    pgtPrint();

    printf("final value in globArray is %d\n" ,    glob[limit-1]);

    exit(0);
}
