# Building SBoy28 OS on Windows

To build the SBoy28 OS kernel and ISO on Windows using CMake, you need the following tools installed and available in your PATH.

## Prerequisites

1.  **CMake**: [Download and install CMake](https://cmake.org/download/).
2.  **Cross-Compiler (i686-elf-gcc)**:
    *   You can use **MinGW-w64** if configured for 32-bit targets (`-m32`).
    *   Recommended: Use a dedicated cross-compiler like those from [LordMilko's i686-elf-tools](https://github.com/lordmilko/i686-elf-tools/releases).
3.  **Build Tools**: **Ninja** (recommended) or **Make** (provided by MinGW).
4.  **ISO Creator**: **grub-mkrescue** (requires `xorriso` and `grub-common`).
    *   *Note*: On Windows, installing GRUB can be tricky. You might need to use WSL or a pre-packaged Windows version of these tools.

## Build Steps

Open your terminal (CMD or PowerShell) in the project root:

```powershell
# 1. Create a build directory
mkdir build
cd build

# 2. Configure the project
# If using a specific cross-compiler, specify the toolchain:
cmake .. -G "Ninja"

# 3. Build the binary and ISO
ninja
```

The output will be:
- `build/SBoy28.bin` (Kernel binary)
- `build/SBoy28.iso` (Bootable ISO image)

## Running in QEMU

If you have QEMU installed:

```powershell
qemu-system-i386 -cdrom SBoy28.iso
```
