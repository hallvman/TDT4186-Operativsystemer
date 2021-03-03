#include <cstddef>
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

  if ((p->size - allocated_size) - sizeof(struct mem_control_block)) {
    printf("Need to split block");
  }
  else {
    printf("No need for split");
  }
  
}

void myfree(void *firstbyte) {

  struct mem_control_block* free = (struct mem_control_block*) firstbyte;
  struct mem_control_block* control = free_list_start;
  
  //If firstbyte is NULL
  if (firstbyte == NULL) {
    return;
  }

  //If the first
  if (free_list_start == NULL) {
    free_list_start = free;
    free_list_start->next = NULL;
  }
  else if (free_list_start > free){
    free->size += control->size;
    free->next = control->next;
    free_list_start = free;
  }
  else if (free_list_start < free) {
    while (control->next != free->next) {
      control = control->next;
    }
    if (control->next == free->next) {
        control->size += free->size;
    }
    else {
    return;
    }
  }

  
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