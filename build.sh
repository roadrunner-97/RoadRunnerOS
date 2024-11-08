mkdir -p build
i686-elf-as bootcode/boot.s -o build/boot.o
i686-elf-gcc -c kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -T linker.ld -o build/rros.bin -ffreestanding -O2 -nostdlib build/boot.o build/kernel.o -lgcc
qemu-system-i386 -kernel build/rros.bin
