#include "kernel/types.h"
#include <kernel/stat.h>
#include <user/user.h>

//here is the declaration of the global array
//int arrGlobal[100000];

int main(){
 
 
    ////comment out for the local array
     //printf("This is for the local declaration\n"); 
     // here is the declaration of local array
     //int arrLocal[10000];
     //arrLocal[0] = 1;
    //doing one operation to avoid error that arrLocal is not used 
    //arrLocal[0] += 1;

 
 
 ////comment out for global array
 
 //arrGlobal[0]=2;
 //arrGlobal[0] +=1;   
 //printf("This is for the global declaration\n");
 
     

    pgtPrint();
    exit(0);
}


