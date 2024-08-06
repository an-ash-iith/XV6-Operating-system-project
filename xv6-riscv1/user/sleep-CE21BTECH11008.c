#include "kernel/types.h"
#include <kernel/stat.h>
#include <user/user.h>

int main(int argc,char *argv[])
{

int tick;
if(argc<2)
{
    printf("No sufficient argument\n");
    exit(-1);
}

 tick = atoi(argv[1]);
 printf("Time for sleep is %d ",tick);
 sleep(tick);
 exit(0);

return 0;
}
