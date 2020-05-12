
#load the image
.set MAGIC,0x1badb002
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)


.section .multiboot
	.long MAGIC
	.long FLAGS
	.long CHECKSUM




.section .text
.extern kernelMain #jmp to kernelMain

#lesson2
.extern callConstructors
.global loader


# Ax to multiboot struct
# Bx to MagicNumber
loader:
	mov $kernek_stack, %esp

	#lesson02
	call callConstructors
	push %eax
	push %ebx
	call kernelMain

_stop:
    cli
    hlt
    jmp _stop

.section .bss
.space 2*1024*1024 #2MiB
kernek_stack: