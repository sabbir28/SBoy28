# Technical Specification: Porting Nestopia to SBoy28

This document details the technical requirements and implementation strategies for running the Nestopia emulator on SBoy28 OS.

## 1. C++ Runtime Support (`libcxx`)

Nestopia is a C++ application. The kernel/userspace must provide:

### Memory Management
- **Operator `new` and `delete`**: Must be implemented to wrap the kernel's `kmalloc` (or a userspace heap allocator).
  ```cpp
  void* operator new(size_t size) { return malloc(size); }
  void operator delete(void* p) { free(p); }
  ```

### Global Constructors
- **`__libc_init_array`**: The loader must parse the `.init_array` section of the ELF/PE file and call the function pointers within to initialize global objects before calling `main()`.

## 2. Memory Architecture & Paging

Nestopia expects a flat memory model with significant heap space for ROM storage and emulation state.

- **Process Isolation**: Each instance must run in its own page directory.
- **User Stack**: Provide at least 64KB for the user stack, mapped to the top of the virtual address space (e.g., `0xC0000000`).
- **Standard Mapping**:
    - **Code/Data**: `0x08048000` (Standard Linux ELF entry).
    - **Heap**: Dynamic mapping via `brk`/`sbrk` syscalls.

## 3. System Call Interface (The "Emulator Bridge")

Nestopia uses standard Unix/Windows calls. We must implement a subset of POSIX-like syscalls:

| Syscall | Purpose | SBoy28 Implementation |
| :--- | :--- | :--- |
| `open` / `read` | Load ROM files | Map to `FatFS` functions. |
| `write` | Output logs/save games | Map to `tty_print` or `FatFS`. |
| `mmap` | Memory mapping | Page-based allocator. |
| `nanosleep` | Timing/Framerate | Use PIT-based `sleep` function. |

## 4. Graphics & Input (SDL2 Layer)

Nestopia uses SDL2 for cross-platform support. Instead of porting all of SDL2, we can provide a **Minimal SDL2 Shim**:

- **Video**: Provide a pointer to the VGA Framebuffer. Nestopia can blit its 256x240 buffer directly to a scaled region of the screen.
- **Input**:
    - **Keyboard**: Map SBoy28 scancodes to NES buttons (A, B, Start, Select).
    - **Mouse**: Use the `mouse.h` API for UI navigation in Nestopia.

## 5. Implementation Strategy

1. **Step 1: Paging Core**: Enable paging in the kernel and implement a basic `malloc` in userspace.
2. **Step 2: Syscall Handler**: Implement `int 0x80` or `sysenter`.
3. **Step 3: ELF Loader**: Modify the `elf_class.asm` logic to map segments into virtual memory.
4. **Step 4: Nestopia Entry**: Compile Nestopia with a cross-compiler (`i686-elf-gcc`) and provide a `stubs.cpp` file for missing OS functions.
