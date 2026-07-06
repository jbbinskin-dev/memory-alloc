#include <stdio.h>
#include <stdlib.h>

void memory_alloc(int size) {

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