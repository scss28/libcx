#include "cx/nums.h"
#include <stdio.h>
#include <stdlib.h>

namespace cx::log {
    template <class... Args>
    void print(u8 const*__restrict fmt, Args&&... args) {
        // printf(fmt, args...);
        // printf("\n");
    }

    template <class... Args>
    void debug(u8 const*__restrict fmt, Args&&... args) {
#ifdef DEBUG
        // printf("\033[90mdebug:\033[0m ");
        // printf(fmt, args...);
        // printf("\n");
#endif
    }

    template <class... Args>
    void info(u8 const*__restrict fmt, Args&&... args) {
        // printf("\033[32minfo:\033[0m ");
        // printf(fmt, args...);
        // printf("\n");
    } 

    template <class... Args>
    void warn(u8 const*__restrict fmt, Args&&... args) {
        // printf("\033[91mwarn:\033[0m ");
        // printf(fmt, args...);
        // printf("\n");
    }
    
    template <class... Args>
    void err(u8 const*__restrict fmt, Args&&... args) {
        // printf("\033[31merror:\033[0m ");
        // printf(fmt, args...);
        // printf("\n");
    }

    template <class... Args>
    [[noreturn]] void fatal(u8 const*__restrict fmt, Args&&... args) {
        // err(fmt, args...);
        // printf("\n");
        exit(1);
    }
}
