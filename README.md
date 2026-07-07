# Custom Memory Allocator in C using mmap! 💾
Custom functions to allocate and free dyanmic raw RAM memory.
## Features 🧩
- Custom Free() features coalescense to merge blocks of freed memory together for later use.
- Memory Allocator splits heap up into smaller blocks of memory to minimise the space used when called.
- Self contained, no need to initialise the heap outside of function use.
- Uses mmap to access raw dynamic memory directly.

## Usage

This allocator is a drop-in replacement for `malloc`/`free`, distributed as source (no prebuilt binary).

### Option A: Compile directly into your project

Copy `memory_alloc.h` and `memory_alloc.c` into your project, then:

```bash
gcc your_program.c memory_alloc.c -o your_program
```

In your code:

```c
#include "memory_alloc.h"

int main() {
    int* arr = memory_alloc(10 * sizeof(int));
    if (arr == NULL) {
        // handle allocation failure
    }
    arr[0] = 42;
    cust_free(arr);
    return 0;
}
```

### Option B: Build as a static library

```bash
gcc -c memory_alloc.c -o memory_alloc.o
ar rcs libmemalloc.a memory_alloc.o
```

Then link against it in other projects:

```bash
gcc your_program.c -L. -lmemalloc -o your_program
```

Make sure `memory_alloc.h` is in your include path (`-I` flag) if it's not in the same directory.

### Requirements

- POSIX system (uses `mmap` from `sys/mman.h`) — Linux/macOS only, not Windows without WSL or a compatibility layer.
- No external dependencies.
