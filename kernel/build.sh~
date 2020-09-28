nasm -f elf boot/boot.S -o bin/boot
cc -m32 -c -o bin/kernelcore krnlcore/kernel.c -std=gnu99 -ffreestanding -O2
cc -m32 -c -o bin/kernelcore_asm krnlcore/asmutils.c -std=gnu99 -ffreestanding -O2
cc -m32 -c -o bin/iocon_kernel krnlcore/iocon.c -std=gnu99 -ffreestanding -O2 
cc -m32 -c -o bin/tinyalloc mm/tinyalloc.c -std=gnu99 -ffreestanding -O2 
cc -m32 -c -o bin/atadriver kdrivers/ata/ata.c -std=gnu99 -ffreestanding -O2 
cc -m32 -c -o bin/vgastandard vga/vga_driver.c -std=gnu99 -ffreestanding -O2 
cc -m32 -c -o bin/abort include/libc/abort.c -std=gnu99 -ffreestanding -O2 
cc -m32 -c -o bin/memcmp include/libc/memcmp.c -std=gnu99 -ffreestanding -O2 
cc -m32 -c -o bin/memcpy include/libc/memcpy.c -std=gnu99 -ffreestanding -O2 
cc -m32 -c -o bin/memmove include/libc/memmove.c -std=gnu99 -ffreestanding -O2 
cc -m32 -c -o bin/memset include/libc/memset.c -std=gnu99 -ffreestanding -O2 
cc -m32 -c -o bin/printf include/libc/printf.c -std=gnu99 -ffreestanding -O2 
cc -m32 -c -o bin/putchar include/libc/putchar.c -std=gnu99 -ffreestanding -O2 
cc -m32 -c -o bin/puts include/libc/puts.c -std=gnu99 -ffreestanding -O2 
cc -m32 -c -o bin/strlen include/libc/strlen.c -std=gnu99 -ffreestanding -O2 
cc -m32 -c -o bin/fat kdrivers/fs/fat.c -std=gnu99 -ffreestanding -O2 
nasm -f elf -o bin/v8086 real/v8086.S
ld -m elf_i386 -T link.ld bin/boot bin/kernelcore bin/kernelcore_asm bin/iocon_kernel bin/tinyalloc bin/vgastandard bin/abort bin/memcmp bin/memcpy bin/memmove bin/memset bin/printf bin/putchar bin/puts bin/strlen bin/fat bin/atadriver -o bin/kernel.bin -nostdlib
cp bin/kernel.bin ../bin/isodir/boot/popcorn.elf
cp grub.cfg ../bin/isodir/boot/grub/grub.cfg
grub-mkrescue ../bin/isodir/ -o ../bin/SimplixOS.iso
