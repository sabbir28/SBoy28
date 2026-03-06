# ===============================
# Project Variables
# ===============================
CC := gcc
CFLAGS := -m32 -std=gnu99 -ffreestanding -Wall -Wextra -I.
OBJDIR := build
SRC := iso.c
OBJ := $(OBJDIR)/iso.o

# ===============================
# Default target
# ===============================
all: $(OBJ)

# ===============================
# Build object file
# ===============================
$(OBJDIR)/iso.o: $(SRC) iso.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ===============================
# Create build directory if missing
# ===============================
$(OBJDIR):
	mkdir -p $(OBJDIR)

# ===============================
# Clean
# ===============================
clean:
	rm -rf $(OBJDIR)
