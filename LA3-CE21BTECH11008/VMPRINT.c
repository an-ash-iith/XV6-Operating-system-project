void vmprintRecursive(pagetable_t pagetable, int level) {
  //AS THERE ARE 512 ENTRY SO CHECKING FOR EACH ONE
  for(int i = 0; i < 512; i++){
    pte_t pte = pagetable[i];
    
    //CHECKING BOTH PAGE TABLE ENTRY AND VALID VIT ARE 1 OR NOT 
    if(pte & PTE_V) {
      uint64 child = PTE2PA(pte);
      for(int i = 0; i <= level; i++) {
        printf(".."); //SHOWING NUMBER OF LEVELS IN THE TREE 
        if(i != level) printf(" ");
      }

      printf("%d: pte %p pa %p\n", i, pte, child);
      if((pte & (PTE_R | PTE_W | PTE_X)) == 0)
          vmprintRecursive((pagetable_t)child, level + 1); 
          //RECURSIBELY CALLING THE FUNTION WITH WITH INCREASE NUMBER OF LEVELS
    } 
  }
}

void
vmprint(pagetable_t pagetable) {
  printf("page table %p\n", pagetable);
  vmprintRecursive(pagetable, 0);
}
