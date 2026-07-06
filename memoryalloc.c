#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define HEAP_SIZE 2048
static char my_heap[HEAP_SIZE];

// Every Block of memory gets this hidden header
typedef struct BlockHeader{
    size_t size;
    bool is_free;
    struct BlockHeader* next;
} BlockHeader;

// Initialise the heap with one big free block (first_block)
void init_heap() {
    BlockHeader* first_block = (BlockHeader*)my_heap; //pointer type cast
    first_block->size = HEAP_SIZE - sizeof(BlockHeader);
    first_block->is_free = true;
    first_block->next = NULL;
}

//Allocator Function
void* memory_alloc(size_t size) {
//initialise the heap
    init_heap();

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

//Replace with custom free()
    free(arr);
    arr = NULL;
    return 0;
}