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
    BlockHeader* first_block = (BlockHeader*)my_heap;
    first_block->size = HEAP_SIZE - sizeof(BlockHeader);
    first_block->is_free = true;
    first_block->next = NULL;
}

//Allocator Function
void* memory_alloc(size_t size) {

}

//Test that it works
int main(void) {
    int number;
    printf("Number of integers to store? ");
    scanf("%d", &number);
//Replace malloc with custom allocator
    int* arr = malloc(number * sizeof(int));
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