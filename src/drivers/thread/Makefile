# scheduler module Makefile fragment
ROOT := ../../..
INCLUDE_DIR := $(ROOT)/kernel/include
SCHED_INC := include
SCHED_SRC := src
SCHED_ASM := asm

BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj

CC := gcc
CFLAGS := -m32 -ffreestanding -O2 -Wall -Wextra -I$(INCLUDE_DIR) -I$(SCHED_INC)
AS := gcc
ASFLAGS := -m32 -c

C_SRCS := $(wildcard $(SCHED_SRC)/*.c)
ASM_SRCS := $(wildcard $(SCHED_ASM)/*.S)

C_OBJS := $(patsubst $(SCHED_SRC)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))
ASM_OBJS := $(patsubst $(SCHED_ASM)/%.S,$(OBJ_DIR)/%.o,$(ASM_SRCS))

OBJS := $(C_OBJS) $(ASM_OBJS)

all: prep $(OBJS)
	@echo "[scheduler] built."

prep:
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SCHED_SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SCHED_ASM)/%.S
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all prep clean
