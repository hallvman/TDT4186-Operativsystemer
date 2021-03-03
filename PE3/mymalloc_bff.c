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
<<<<<<< HEAD:PE3/mymalloc_bff.c
  m->size = MEM_SIZE - sizeof(struct mem_control_block); //sizeof mem_control_block er 16
=======
  m->size = MEM_SIZE - sizeof(struct mem_control_block);
  m->isFree=0;
>>>>>>> 79dfd6dd4779b835001ad034163c47184ecdafc0:PE3/mymalloc.c

  // no next free block
  m->next = (struct mem_control_block *)0;

  // initialize the start of the free list
  free_list_start = m;

  // We're initialized and ready to go
  has_initialized = 1;
}

void *mymalloc(long numbytes) {
  /* Initialize the memory */
  if (has_initialized == 0) {
     mymalloc_init();
  }
  struct mem_control_block *p = free_list_start;
  struct mem_control_block *q = NULL;
  void *addr;
  
  //Check if there is 8 free bytes on the end
  long allocated_size = numbytes;
  while (allocated_size % 8) {
    allocated_size++;
  }

  allocated_size += sizeof(struct mem_control_block);

  //Find a block with enough space for p
  while (p->size < allocated_size) {
    q = p;
    p = p->next;
    if (p == NULL) 
      return NULL;
  }

  //Pointer to the 
  addr = (void *)p;

<<<<<<< HEAD:PE3/mymalloc_bff.c
  if ((p->size - allocated_size) - sizeof(struct mem_control_block)) {
    printf("Need to split block");
  }
  else {
    printf("No need for split");
  }
  
=======
  /* Metadata block pointer to traverse the free list */
  struct mem_control_block *prev, *curr;
  void *result;
  curr = free_list_start;

  while ((((curr -> size) < numbytes)||((curr->isFree)==0)) && ((curr -> next) != NULL)){
    prev = curr;
    curr=curr->next;
    printf("One block checked\n");
  }

  /*

  */
  if ((curr->size) == numbytes)
  {
    curr->isFree=0;
    result=(void*)(++curr);
    printf("Exact fitting block allocated\n");
  return result;
  }

  /* 

  */
  else if((curr->size)>(numbytes+sizeof(struct mem_control_block))){
    result = (void*)(++curr);
    printf("Fitting block allocated with a split\n");
  return result;
  }

  /* 
    Else if there is not any memory to allocate 
  */
  else {
    result = NULL;
    printf("Sorry, no sufficient memory to allocate\n");
  }
>>>>>>> 79dfd6dd4779b835001ad034163c47184ecdafc0:PE3/mymalloc.c
}

void myfree(void *firstbyte) {

  /* add your code here! */
  
}

int main(int argc, char **argv) {

  void *p;
  p = mymalloc(42); // allocate 42 bytes

  if (p != (void *)0) {
    // do something
    myfree(p); // release memory again
  } else {
    printf("mymalloc failed!\n");
  }

}