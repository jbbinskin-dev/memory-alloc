# Custom Memory Allocator in C using mmap! 💾
Custom functions to allocate and free dyanmic raw RAM memory.
## Features 🧩
- Custom Free() features coalescense to merge blocks of freed memory together for later use.
- Memory Allocator splits heap up into smaller blocks of memory to minimise the space used when called.
- Self contained, no need to initialise the heap outside of function use.
- Uses mmap to access raw dynamic memory directly.  
