#pragma once

#include <windows.h>
#include <winternl.h>
#include <intrin.h>

// Most of this is translated from the Zig standard library
namespace cx::windows {
    typedef struct RTL_BITMAP RTL_BITMAP;
    typedef struct ACTIVATION_CONTEXT_DATA ACTIVATION_CONTEXT_DATA;
    typedef struct ASSEMBLY_STORAGE_MAP ASSEMBLY_STORAGE_MAP;
    typedef struct FLS_CALLBACK_INFO FLS_CALLBACK_INFO;

    struct CURDIR {
        UNICODE_STRING DosPath;
        HANDLE Handle;
    };

    struct RTL_DRIVE_LETTER_CURDIR {
        USHORT Flags;
        USHORT Length;
        ULONG TimeStamp;
        UNICODE_STRING DosPath;
    };

    struct RTL_USER_PROCESS_PARAMETERS {
        ULONG AllocationSize;
        ULONG Size;
        ULONG Flags;
        ULONG DebugFlags;
    
        HANDLE ConsoleHandle;
        ULONG ConsoleFlags;
        HANDLE hStdInput;
        HANDLE hStdOutput;
        HANDLE hStdError;
    
        CURDIR CurrentDirectory;
        UNICODE_STRING DllPath;
        UNICODE_STRING ImagePathName;
        UNICODE_STRING CommandLine;
    
        PWSTR Environment;
    
        ULONG dwX;
        ULONG dwY;
        ULONG dwXSize;
        ULONG dwYSize;
        ULONG dwXCountChars;
        ULONG dwYCountChars;
        ULONG dwFillAttribute;
        ULONG dwFlags;
        ULONG dwShowWindow;
    
        UNICODE_STRING WindowTitle;
        UNICODE_STRING Desktop;
        UNICODE_STRING ShellInfo;
        UNICODE_STRING RuntimeInfo;
    
        RTL_DRIVE_LETTER_CURDIR DLCurrentDirectory[0x20];
    };

    struct PPEB_LDR_DATA {
        // Versions: 3.51 and higher
        /// The size in bytes of the structure
        ULONG Length;

        /// TRUE if the structure is prepared.
        BOOLEAN Initialized;

        PVOID SsHandle;
        LIST_ENTRY InLoadOrderModuleList;
        LIST_ENTRY InMemoryOrderModuleList;
        LIST_ENTRY InInitializationOrderModuleList;

        // Versions: 5.1 and higher

        /// No known use of this field is known in Windows 8 and higher.
        PVOID EntryInProgress;

        // Versions: 6.0 from Windows Vista SP1, and higher
        BOOLEAN ShutdownInProgress;

        /// Though ShutdownThreadId is declared as a HANDLE,
        /// it is indeed the thread ID as suggested by its name.
        /// It is picked up from the UniqueThread member of the CLIENT_ID in the
        /// TEB of the thread that asks to terminate the process.
        HANDLE ShutdownThreadId;
    };


    struct PEB {
        BOOLEAN InheritedAddressSpace;            // all
        BOOLEAN ReadImageFileExecOptions;         // 3.51+
        BOOLEAN BeingDebugged;                    // 3.51+
        UCHAR   BitField;                         // 5.2+
    
        HANDLE Mutant;                            // all
        HMODULE ImageBaseAddress;                 // all
        PEB_LDR_DATA* Ldr;                        // all
        RTL_USER_PROCESS_PARAMETERS* ProcessParameters; // all
        PVOID SubSystemData;                      // all
        HANDLE ProcessHeap;                       // all
    
        PRTL_CRITICAL_SECTION FastPebLock;        // 5.1+
        PVOID AtlThunkSListPtr;                   // 5.2+
        PVOID IFEOKey;                            // 5.2+
    
        ULONG CrossProcessFlags;                  // 6.0+
        union {
            PVOID KernelCallbackTable;
            PVOID UserSharedInfoPtr;
        };                                        // 6.0+
    
        ULONG SystemReserved;                     // 5.1+
        ULONG AtlThunkSListPtr32;                 // 5.1, 6.1+
        PVOID ApiSetMap;                          // 6.1+
    
        ULONG TlsExpansionCounter;                // all
        RTL_BITMAP* TlsBitmap;                    // all
        ULONG TlsBitmapBits[2];                   // all
        PVOID ReadOnlySharedMemoryBase;           // all
        PVOID SharedData;                         // 1703+
        PVOID *ReadOnlyStaticServerData;          // all
        PVOID AnsiCodePageData;                   // all
        PVOID OemCodePageData;                    // all
        PVOID UnicodeCaseTableData;               // all
    
        ULONG NumberOfProcessors;                 // 3.51+
        ULONG NtGlobalFlag;                       // 3.51+
        LARGE_INTEGER CriticalSectionTimeout;     // all
    
        SIZE_T HeapSegmentReserve;                // 3.51+
        SIZE_T HeapSegmentCommit;
        SIZE_T HeapDeCommitTotalFreeThreshold;
        SIZE_T HeapDeCommitFreeBlockThreshold;
        ULONG NumberOfHeaps;
        ULONG MaximumNumberOfHeaps;
        PVOID *ProcessHeaps;
    
        PVOID GdiSharedHandleTable;               // 4.0+
        PVOID ProcessStarterHelper;
        ULONG GdiDCAttributeList;
        PRTL_CRITICAL_SECTION LoaderLock;
        ULONG OSMajorVersion;
        ULONG OSMinorVersion;
        USHORT OSBuildNumber;
        USHORT OSCSDVersion;
        ULONG OSPlatformId;
        ULONG ImageSubSystem;
        ULONG ImageSubSystemMajorVersion;
        ULONG ImageSubSystemMinorVersion;
        KAFFINITY ActiveProcessAffinityMask;
    
    #ifdef _WIN64
        ULONG GdiHandleBuffer[0x3C];              // 64-bit
    #else
        ULONG GdiHandleBuffer[0x22];              // 32-bit
    #endif
    
        PVOID PostProcessInitRoutine;             // 5.0+
        RTL_BITMAP* TlsExpansionBitmap;
        ULONG TlsExpansionBitmapBits[32];
        ULONG SessionId;
        ULARGE_INTEGER AppCompatFlags;            // 5.1+
        ULARGE_INTEGER AppCompatFlagsUser;
        PVOID ShimData;
        PVOID AppCompatInfo;                      // 5.0+
        UNICODE_STRING CSDVersion;
    
        ACTIVATION_CONTEXT_DATA* ActivationContextData;    // 5.1+
        ASSEMBLY_STORAGE_MAP* ProcessAssemblyStorageMap;
        ACTIVATION_CONTEXT_DATA* SystemDefaultActivationData;
        ASSEMBLY_STORAGE_MAP* SystemAssemblyStorageMap;
        SIZE_T MinimumStackCommit;
    
        FLS_CALLBACK_INFO* FlsCallback;           // 5.2+
        LIST_ENTRY FlsListHead;
        RTL_BITMAP* FlsBitmap;
        ULONG FlsBitmapBits[4];
        ULONG FlsHighIndex;
    
        PVOID WerRegistrationData;                // 6.0+
        PVOID WerShipAssertPtr;
    
        PVOID pUnused;                            // 6.1+
        PVOID pImageHeaderHash;
        ULONG TracingFlags;
    
        ULONGLONG CsrServerReadOnlySharedMemoryBase; // 6.2+
    
        ULONG TppWorkerpListLock;                 // 1511+
        LIST_ENTRY TppWorkerpList;
        PVOID WaitOnAddressHashTable[0x80];
    
        PVOID TelemetryCoverageHeader;            // 1709+
        ULONG CloudFileFlags;
    };

    struct CLIENT_ID {
        HANDLE UniqueProcess;
        HANDLE UniqueThread;
    };

    struct TEB {
        NT_TIB NtTib;
        PVOID EnvironmentPointer;
        CLIENT_ID ClientId;
        PVOID ActiveRpcHandle;
        PVOID ThreadLocalStoragePointer;
        PEB* ProcessEnvironmentBlock;
        ULONG LastErrorValue;
        CHAR Reserved2[399 * sizeof(PVOID) - sizeof(ULONG)];
        CHAR Reserved3[1952];
        PVOID TlsSlots[64];
        CHAR Reserved4[8];
        PVOID Reserved5[26];
        PVOID ReservedForOle;
        PVOID Reserved6[4];
        PVOID TlsExpansionSlots;
    };

    inline TEB const* teb() {
#ifdef _M_X64
        return (TEB const*)__readgsqword(0x30);
#else
        return (TEB const*)__readgsqword(0x18);
#endif
    }

    inline PEB const* peb() {
        return teb()->ProcessEnvironmentBlock;
    }
}
