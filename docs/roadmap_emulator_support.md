# Roadmap: Nestopia & App Support

To support applications like **Nestopia** (Nintendo emulator originally for Windows/Unix), SBoy28 OS needs to evolve from a basic kernel into a process-oriented operating system with specific library support.
## Current Status (SBoy28)
- [x] **GDT/IDT**: Foundation for CPU protection and interrupts.
- [x] **Multitasking**: Preemptive round-robin scheduler (Kernel Mode).
- [x] **Input**: Basic Keyboard and Mouse drivers.
- [x] **Filesystem**: Early `FatFS` integration (needs kernel-wide VFS).
- [ ] **ELF Reading**: Basic assembly logic for reading ELF headers exists but isn't integrated.

## Immediate Next Steps (Phase 1: Process Foundation)

### 1. Virtual Memory & Paging
Emulators and modern applications expect a fixed memory layout (e.g., Windows apps at `0x400000`).
- **Implement Paging**: Set up Page Directories and Page Tables.
- **Identity Mapping**: Map the kernel (first 1-4MB) to its physical address.
- **Process Isolation**: Every new process should have its own Page Directory.

### 2. User Mode (Ring 3) Transition
Applications must run in Ring 3 for security and stability.
- **TSS (Task State Segment)**: Implement TSS to handle stack switching during interrupts/syscalls.
- **Ring 3 GDT Entries**: Ensure User Code and User Data segments are properly configured (already introduced in my last update).
- **Switch to User Mode**: Create a function to jump into Ring 3 with a user stack.

### 3. System Call Interface (Syscalls)
Applications need a way to talk to the kernel.
- **Interrupt 0x80 (Linux Style)** or **Sysenter/Sysexit**.
- **Syscall Dispatcher**: A handler that takes a syscall number and arguments and routes them to kernel functions (e.g., `sys_read`, `sys_write`).

## Phase 2: Emulator Compatibility

### 4. Advanced Process Loading
- **PE/ELF Loader**: A robust C-based loader that parses headers, maps segments into the virtual address space, and resolves symbols.
- **Environment Block**: Set up the environment (like `argc`, `argv`, `envp`) and the Thread Information Block (TIB) for Windows emulation compatibility.

### 5. VFS (Virtual File System)
- **Abstraction Layer**: A standard interface (`open`, `read`, `write`) that can talk to `FatFS`, `ISO9660`, or a temporary `procfs`.
- **Handle Mapping**: Windows uses `HANDLE`, Linux uses `fd`. The VFS must manage these mappings.

### 6. Video Framebuffer (VESA/GOP)
Modern apps require high-resolution graphics.
- **Switch from VGA Text Mode**: Implement a linear framebuffer driver (LFB).
- **Basic Drawing Library**: Support for blitting and windows.

## Phase 3: Nestopia Specific Requirements

### 7. C++ Runtime Support
Nestopia is written in C++. The kernel must provide:
- **Global Constructors/Destructors**: Support for `__libc_init_array`.
- **Operator New/Delete**: Integrated with our `kmalloc`.
- **Exception Handling**: Minimal `libgcc_s` or `libsupc++` support.

### 8. Multimedia Abstraction
Emulators need sound and fast graphics.
- **Direct Link to Framebuffer**: A way for the app to write directly to video memory.
- **Audio Driver**: Basic PC Speaker or SB16 support (optional but recommended).

## Summary of Implementation Order
1. **Paging** (required for isolation)
2. **TSS & User Mode** (required for app safety)
3. **Syscalls** (required for app interaction)
4. **C++ Runtime & Process Loading** (required for Nestopia)
