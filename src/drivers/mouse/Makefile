# ============================================
# Mouse Driver Build Pipeline
# ============================================

# Core paths
ROOT        := ../../..
INCLUDE_DIR := $(ROOT)/kernel/include
MOUSE_INC   := include
MOUSE_SRC   := src
MOUSE_ASM   := asm

# Build output
BUILD_DIR   := build
OBJ_DIR     := $(BUILD_DIR)/obj

# Toolchain
CC      := gcc
AS      := gcc        # GAS assembler for .S files
CFLAGS  := -m32 -ffreestanding -O2 -Wall -Wextra -I$(INCLUDE_DIR) -I$(MOUSE_INC)
ASFLAGS := -m32 -c    # GCC assembling mode

# Source maps
C_SRCS    := $(wildcard $(MOUSE_SRC)/*.c)
ASM_SRCS  := $(wildcard $(MOUSE_ASM)/*.S)

C_OBJS    := $(patsubst $(MOUSE_SRC)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))
ASM_OBJS  := $(patsubst $(MOUSE_ASM)/%.S,$(OBJ_DIR)/%.o,$(ASM_SRCS))

OBJS := $(C_OBJS) $(ASM_OBJS)

# Build target
all: prep $(OBJS)
	@echo "[MouseDriver] Build completed."

prep:
	@mkdir -p $(OBJ_DIR)

# Compilation pipelines
$(OBJ_DIR)/%.o: $(MOUSE_SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(MOUSE_ASM)/%.S
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean prep
