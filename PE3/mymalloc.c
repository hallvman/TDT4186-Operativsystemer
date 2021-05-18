#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int has_initialized = 0;

// our memory area we can allocate from, here 64 kB
#define MEM_SIZE (64*1024)
uint8_t heap[MEM_SIZE];

// start and end of our own heap memory area
void *managed_memory_start; 

// this block is stored at the start of each free and used block
struct mem_control_block {
  int size;
  int isFree;
  struct mem_control_block *next;
};

// pointer to start of our free list
struct mem_control_block *free_list_start;      

void mymalloc_init() { 

  // our memory starts at the start of the heap array
  managed_memory_start = &heap;

  // allocate and initialize our memory control block 
  // for the first (and at the moment only) free block
  struct mem_control_block *m = (struct mem_control_block *)managed_memory_start;
  m->size = MEM_SIZE - sizeof(struct mem_control_block);

  // no next free block
  m->next = (struct mem_control_block *)0;
  m->isFree=1;

  // initialize the start of the free list
  free_list_start = m;

  // We're initialized and ready to go
  has_initialized = 1;
}

// Split function for the split of a memory allocation
void split(struct mem_control_block *slot, int size){
  struct mem_control_block *new=(void*)((void*)slot+size+sizeof(struct mem_control_block));
  new->size=(slot->size)-size-sizeof(struct mem_control_block);
  new->next=slot->next;
  new->isFree=1;
  slot->size=size;
  slot->isFree=0;
  slot->next=new;
}

// Helping function to merge the blocks together
void mergeBlocks(){
  struct mem_control_block *curr, *prev;
  curr = free_list_start;
  while ((curr->next) != NULL)
  {
    if ((curr->isFree) && (curr->next->isFree))
    {
      curr->size+=(curr->next->size)+sizeof(struct mem_control_block);
      curr->next=curr->next->next;
    } else {
      prev=curr;
      curr=curr->next;
    }
  }
}

void *mymalloc(long numbytes) {
  if (has_initialized == 0) {
     mymalloc_init();
     printf("Memory initialized\n");
  }

  /* add your code here! */

  struct mem_control_block *prev, *curr;
  void *result;
  curr=free_list_start;

  while ((((curr->size)<numbytes)||((curr->isFree)=0))&&(curr->next!=NULL))
  {
    prev=curr;
    curr=curr->next;
    printf("One block checked\n");
  }

  /* found memory that exactly fits */

  if ((curr->size)==numbytes)
  {
    curr->isFree=0;
    result=(void*)(++curr);
    printf("Exactly block allocated\n");
    return result;
  }

  /* Found fitting block and split the rest */
  else if((curr->size)>(numbytes + sizeof(struct mem_control_block))){
    split(curr, numbytes);
    result=(void*)(++curr);
    printf("Fitting block allocated\n");
    return result;
  }

  /* Not enough space */
  else{
    result=NULL;
    printf("Sorry. No sufficient memory to allocate\n");
    return result;
 }
}

void myfree(void *firstbyte) {

  struct mem_control_block *curr = firstbyte;

  /* Checks if not empty */
  if (firstbyte != NULL)
  {
    curr -= 1;
    curr->isFree=1;
    mergeBlocks();
  } else {
    printf("Invalid pointer\n");
  }
}

// Function for testing purposes
void printlist(struct mem_control_block* block){
    while (block != NULL) {
        printf("Blocksize: %d, and poiting: %p. Memory: %p \n", block->size, block->next, block);
        block = block->next;
    }
}

int main(int argc, char **argv) {

  /* Code for testing during programming */
  /*
  // Write printf's to test the code 
  printf("Entering mymalloc\n");
  void *p = mymalloc(42);
  printf("If this is the last message printed is does not enter the if or myfree()\n");
  if (p != (void *)0)
  {
    printf("The if in main is true\n");
    myfree(p);
  } else{
    printf("Mymalloc failed\n");
  }
  */

  // Should not print because of no initialization
  printlist(free_list_start);
  printf("----------------Start------------------\n");

  void *k = mymalloc(66);
  printlist(free_list_start);
  myfree(k);
  printf("\n");

  void *l = mymalloc(42);
  printlist(free_list_start);
  myfree(l);
  printf("\n");

  void *m = mymalloc(72);
  printlist(free_list_start);
  myfree(m);
  printf("\n");

  void *n = mymalloc(128);
  printlist(free_list_start);
  myfree(n);

  printf("----------------Slutt------------------\n");

}