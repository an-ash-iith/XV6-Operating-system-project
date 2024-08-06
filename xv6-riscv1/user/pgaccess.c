#include "kernel/types.h"
#include <kernel/stat.h>
#include <user/user.h>

int main(int argc, char*argv[]){ 
  
    uint64 start_va = 6;
    uint64 num_pages =30;
    uint64 buffer ;

    printf("entered\n");
    pgaccess(&start_va,num_pages,&buffer);
    
    printf(" values of the bitmap buffer is  %p\n", buffer);
    exit(0);
}
