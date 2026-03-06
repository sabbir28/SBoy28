# =========================
# Makefile for ELFReader test
# =========================

ASM = nasm
ASMFLAGS = -f elf32          # Correct NASM output format for 32-bit ELF

CC = gcc
CFLAGS = -m32 -Wall -O2

LD = gcc
LDFLAGS = -m32

TARGET = test

OBJ = elf_class.o test.o

# Default target
all: $(TARGET)

# Compile assembly to object
elf_class.o: elf_class.asm
	$(ASM) $(ASMFLAGS) $< -o $@

# Compile C code to object
test.o: test.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link everything
$(TARGET): $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $(TARGET)

# Clean
clean:
	rm -f $(OBJ) $(TARGET)
