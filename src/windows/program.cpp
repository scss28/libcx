#include <windows.h>
#include <dbghelp.h>
#include <stdio.h>

#include "cx/nums.h"
#include "cx/defer.h"
#include "cx/array.h"

namespace cx {
//     void printStackTrace() {
//         cx::Array<usize, 100> addrs;
//         WORD len = RtlCaptureStackBackTrace(0, (DWORD)addrs.len(), (void**)&addrs.data, nullptr);
// 
//         for (auto addr : addrs[0, len]) {
// 
//         }
// 
//         SymSetOptions(SYMOPT_DEFERRED_LOADS | SYMOPT_UNDNAME | SYMOPT_LOAD_LINES);
// 
//         HANDLE process = GetCurrentProcess();
//         if (!SymInitialize(process, nullptr, true)) return;
// 
//         CONTEXT context;
//         context.ContextFlags = CONTEXT_ALL;
// 
//         RtlCaptureContext(&context);
// 
//         STACKFRAME frame;
// #ifdef _M_IX86
//         DWORD machine = IMAGE_FILE_MACHINE_I386;
//         frame.AddrPC = {
//             .Offset = context.Eip,
//             .Segment = 0,
//             .Mode = AddrModeFlat,
//         };
//         frame.AddrFrame = {
//             .Offset = context.Ebp,
//             .Segment = 0,
//             .Mode = AddrModeFlat,
//         };
//         frame.AddrStack = {
//             .Offset = context.Esp,
//             .Segment = 0,
//             .Mode = AddrModeFlat,
//         };
// #elif _M_X64
//         DWORD machine = IMAGE_FILE_MACHINE_AMD64;
//         frame.AddrPC = {
//             .Offset = context.Rip,
//             .Segment = 0,
//             .Mode = AddrModeFlat,
//         };
//         frame.AddrFrame = {
//             .Offset = context.Rbp,
//             .Segment = 0,
//             .Mode = AddrModeFlat,
//         };
//         frame.AddrStack = {
//             .Offset = context.Rsp,
//             .Segment = 0,
//             .Mode = AddrModeFlat,
//         };
// #endif
// 
// 
//         const u32 trailingLen = 256;
//         SYMBOL_INFO* symbol = (SYMBOL_INFO*)calloc(sizeof(SYMBOL_INFO) + trailingLen, 1);
//         defer { free(symbol); };
// 
//         symbol->MaxNameLen = 255;
//         symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
// 
//         while (true) {
//             bool result = StackWalk(
//                 machine,
//                 process,
//                 GetCurrentThread(),
//                 &frame,
//                 &context,
//                 nullptr,
//                 SymFunctionTableAccess,
//                 SymGetModuleBase,
//                 nullptr
//             );
// 
//             if (!result || frame.AddrPC.Offset == 0) break;
// 
//             DWORD64 address = frame.AddrPC.Offset;
//             if (SymFromAddr(process, address, 0, symbol)) {
//                 printf("  %s - 0x%0llX\n", symbol->Name, (u64)symbol->Address);
// 
//                 IMAGEHLP_LINE64 line;
//                 DWORD displacement = 0;
//                 memset(&line, 0, sizeof(line));
//                 line.SizeOfStruct = sizeof(line);
// 
//                 if (SymGetLineFromAddr64(process, address, &displacement, &line)) {
//                     printf(" (%s:%lu)", line.FileName, line.LineNumber);
//                 }
//                 printf("\n");
//             } else {
//                 printf("  [unknown] - 0x%0llX\n", (u64)address);
//             }
// 
//             memset(symbol + sizeof(SYMBOL_INFO) - 1, 0, trailingLen + 1);
//         }
//     }
}
