# SimplixOS-Popcorn
The official SimplixOS repository. The Popcorn Kernel is located inside the folder kernel.
# SimplixOS
SimplixOS is an Unix-like operating system. It's a hobby operating system, it's not made to be a widespread OS like Windows.
# Popcorn
Popcorn is an Unix-like kernel, it powers the SimplixOS operating system. It doesn't rely on Linux or other Unix-based kernel.
# External sources
https://osdev.org/ was an useful website to help develop the kernel, as well as https://codeproject.com/
# Liscence
I am (EscapeCharacter) a supporter for the free software mouvement. So almost all of my code is published under some kind of Free software liscence, 
mostly GPL3. Both SimplixOS and Popcorn are completly open-source and free software. Both follow the "free speech" and "free beer", but if you want 
your new SimplixOS distribution can cost money or be private source. I have no problem with that. You own the software or machine, so you should be
able to modify it as you want, right?
The software is provided as it is, without any guarantee of any kind. The software that can be executed on this operating system can be
proprietary / closed source, meaning that it would be illegal to modify and redistribute.
# Hacking
To hack into SimplixOS or Popcorn, it's pretty simple. The file "kernel/krnlcore/kernel.c" contains the entrypoint of the Popcorn kernel.
# How to build
To build SimplixOS, the script is located at "/kernel/build.sh". On Windows/WSL, you can use the "kernel/buildrun.sh" or "run.sh" to run with QEMU.
Linux support is not yet built-in (script wise) but you can still run with QEMU using 'qemu-system-x86_64 SimplixOS.iso' command to execute.
For now, VirtualBox seems to be the most efficient emulator.
NOTE: SimplixOS & Popcorn both build with GRUB2. If you want another bootloader, you'll need to hack in. Shouldn't be too difficult.
