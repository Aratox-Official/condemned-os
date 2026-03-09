#!/bin/bash

nasm bootloader.asm -f bin -o bootloader.bin

gcc -ffreestanding -fno-stack-protector -fno-pic -c kernel.c -o kernel.o

ld -m elf_i386 -T linker.ld kernel.o -o kernel.elf

# Create disk image
dd if=bootloader.bin of=os.img bs=512 count=1 conv=notrunc
dd if=kernel.elf of=os.img bs=512 seek=1 conv=notrunc
