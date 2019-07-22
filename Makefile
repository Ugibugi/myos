CC=i686-elf-g++
ASM=nasm
ASMFLAGS = -felf32
CFLAGS=-ffreestanding -std=c++17 -Wall -Wextra -O2 -fno-exceptions -fno-rtti
CEXTRA_FLAGS = -nostdlib -lgcc
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)
SRC_DIR = src
DEP_DIR = $(SRC_DIR)
LD_SCRIPT = linker.ld
_OBJ = kernel.o console.o string.o boot.o icxxabi.o
_DEPS = console.h string.h icxxabi.h
OBJ = $(patsubst %, $(OBJ_DIR)/%, $(_OBJ))
DEPS = $(patsubst %, $(DEP_DIR)/%, $(_DEPS))
CRTI_OBJ =$(OBJ_DIR)/crti.o
CRT_BEGIN := $(shell $(CC) $(CFLAGS) $(CEXTRA_FLAGS)  -print-file-name=crtbegin.o)
CRT_END := $(shell $(CC) $(CFLAGS) $(CEXTRA_FLAGS)  -print-file-name=crtend.o)
CRTN_OBJ = $(OBJ_DIR)/crtn.o
OBJ_LINK_LIST = $(CRTI_OBJ) $(CRT_BEGIN) $(OBJ) $(CRT_END) $(CRTN_OBJ)
MY_OBJS = $(CRTI_OBJ) $(OBJ) $(CRTN_OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS) ; $(CC) -c -o $@  $< $(CFLAGS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS) ; $(CC) -c -o $@  $< $(CFLAGS)

myos.bin: $(OBJ_LINK_LIST) ; $(CC) -o $@ $^ -T $(LD_SCRIPT) $(CFLAGS) $(CEXTRA_FLAGS)

$(OBJ_DIR)/boot.o: $(SRC_DIR)/boot.asm $(CRTI_OBJ) $(CRTN_OBJ) ; nasm -felf32 $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm ; $(ASM) $(ASMFLAGS) $< -o $@
.PHONY: clean

clean: ; rm -f $(OBJ_DIR)/*.o ; rm -f myos.bin

.PHONY: iso

iso: myos.bin ; mkdir -p isodir/boot/grub ; cp myos.bin isodir/boot/myos.bin ; cp grub.cfg isodir/boot/grub/grub.cfg ; grub-mkrescue -o myos.iso isodir
