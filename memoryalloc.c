#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <sys/mman.h>

#define HEAP_SIZE (1024 * 1024) //request 1 megabyte from memory
static void* my_heap = NULL; //pointer to hold the OS allocated memory

// Every Block of memory gets this hidden header
typedef struct BlockHeader{
    size_t size;
    bool is_free;
    struct BlockHeader* next;
} BlockHeader;

// Initialise the heap with one big free block (first_block)
void init_heap() {
    // Request a brand new block of RAW ram from the kernel
    my_heap = mmap(NULL, HEAP_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (my_heap == MAP_FAILED) {
        return;
    }
    BlockHeader* first_block = (BlockHeader*)my_heap; //pointer type cast
    first_block->size = HEAP_SIZE - sizeof(BlockHeader);
    first_block->is_free = true;
    first_block->next = NULL;
}

//Allocator Function
void* memory_alloc(size_t size) {
//initialise the heap exactly once
    static bool is_initialised = false;
    if (!is_initialised) {
        init_heap();
        if (my_heap == MAP_FAILED) {
            return NULL;
        }
        is_initialised = true;
    }

    BlockHeader* curr = (BlockHeader*)my_heap;

    while (curr != NULL) {
        // Find the first free block that fits the data
        if (curr->is_free && curr->size >= size) {

            //Split the Block if it is much larger than requested
            if (curr->size >= size + sizeof(BlockHeader) + 8) {
                BlockHeader* next_block = (BlockHeader*)((char*)curr + sizeof(BlockHeader) + size);
                next_block->size = curr->size - size - sizeof(BlockHeader);
                next_block->is_free = true;
                next_block->next = curr->next;
                
                curr->size = size;
                curr->next = next_block;
            }
            curr->is_free = false;
            //return pointer to user data skipping past the header
            return (void*)((char*)curr + sizeof(BlockHeader));
        }
        //check the next block
        curr = curr->next;
    }
    return NULL; //out of memory (no free blocks)
}

//Free Function
void cust_free(void* ptr) {
    if (!ptr) return;

    //step backward to get the block header
    BlockHeader* header = (BlockHeader*)((char*)ptr - sizeof(BlockHeader));
    header->is_free = true; //update its status so that it can be used again

    //Scan the entire heap and merge adjacent free blocks
    BlockHeader* curr = (BlockHeader*)my_heap;
    
    while (curr != NULL && curr->next != NULL) {
        //if the current block and the next block are free merge them
        if (curr->is_free && curr->next->is_free) {
            // The new size absorbs the next block's payload And its header
            curr->size += sizeof(BlockHeader) + curr->next->size;

            //skip the next block in the linked list chain
            curr->next = curr->next->next;
            //Loop again to see if the new next block can be merged
            continue;
        }
        curr = curr->next;
    }
}

//Test that it works
int main(void) {
    int number;
    printf("Number of integers to store? ");
    scanf("%d", &number);
//allocate memory based on user input
    int* arr = memory_alloc(number * sizeof(int));
    if (arr == NULL) {
        printf("Memory Allocation Failed");
        return 1;
    }
//print the array
    for (int i=0; i<number;i++) {
        printf("Enter a number: ");
        scanf("%d", &arr[i]);
    }
    for (int i=0; i<number;i++) {
        printf("%d\n", arr[i]);
    }

//free memory using cust_free()
    cust_free(arr);
    arr = NULL;
    return 0;
}