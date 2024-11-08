#!/bin/bash

set -e
cmake -Bbuild
make -Cbuild

if [[ "$1" == "-bin" ]]; then

    echo "running qemu directly on the bin file"
    qemu-system-i386 -kernel build/kernel/rros.bin

elif [[ "$1" == "-grub" ]]; then

    echo "running via grub MB option"
    mkdir -p build/isodir/boot/grub
    cp build/kernel/rros.bin build/isodir/boot/rros.bin
    cp grub.cfg build/isodir/boot/grub/grub.cfg
    grub-mkrescue -o build/rros.iso build/isodir
    qemu-system-i386 -cdrom build/rros.iso

else
    echo "please use either -grub or -bin options"
fi