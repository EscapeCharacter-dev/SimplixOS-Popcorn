MBOOT_HEADER_MAGIC  equ 0x1BADB002
MBOOT_PAGE_ALIGN    equ 1 << 0
MBOOT_MEM_INFO      equ 1 << 1
;MBOOT_GRAPH_MODE    equ 1 << 2
MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO ;| MBOOT_GRAPH_MODE
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

;magic flags checksum (magic + flags + checksum = 0)

[BITS 32]
section .text

dd MBOOT_HEADER_MAGIC
dd MBOOT_HEADER_FLAGS
dd MBOOT_CHECKSUM

dd 0
dd 0
dd 0
dd 0
dd 0

dd 0
dd 800 ; width
dd 600 ; height
dd 32 ; bpp

[GLOBAL start]
[GLOBAL glb_mboot_ptr]
[EXTERN kernel_ep]

start:
    cli

    mov esp, STACK_TOP
    mov ebp, 0
    and esp, 0FFFFFFF0H
    mov [glb_mboot_ptr] , ebx

    push ebx
    call kernel_ep

stop:
    hlt
    jmp stop

section .bss
stack:
    resb 32768
glb_mboot_ptr:
    resb 4

STACK_TOP equ $ - stack - 1