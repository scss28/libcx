# libcx
Minimalistic template library for C++ with no dependencies. It's meant to be used as a replacement for the STL (mainly for myself).

The library is knowingly written without the use of some C++ features to reduce complexity and make it easier to use.
## Features
#### Slices
`std::Slice` represents a readonly view into a "slice" of memory, on the inside it's just a pointer and length. A lot of functions in the library deal with this struct. 
#### Arrays and lists
- **Array**
    ```C++
    #include <std/array.h>

    // Very similar to std::array from STL, owns the memory and has static size.
    auto arr = std::arr<u32>(1, 2);
    ```
- **ArrayList**
    ```C++
    #include <std/array_list.h>
    #include <std/log.h>

    std::ArrayList<i32> list;
    list.push(1);
    list.push(2);

    // 'items' is the current 'std::Slice' of pushed items.
    for (auto x : list.items) {
        std::log("%d\n", x);
    }
    ```

#### Allocators
`std::Allocator` in the beginning was meant to be a normal C++ interface with pure virtual functions however since the library doesn't link `libcpp` the current `std::Allocator` is a C-style vtable struct.
- **cAllocator** (global) \
    Its the default allocator used when using `std::alloc`, `std::realloc` and `std::free`. It's meant for general use like `malloc`/`free`.
- **Arena**
    ```C++
    #include <std/arena.h>
    
    std::Arena arena;

    // Allocates a slice of 20 bytes. 
    // No need to free it as the arena frees all the owned memory in 'deinit'.
    auto buf = arena.allocator().alloc<u8>(20);

    arena.deinit();
    ```

