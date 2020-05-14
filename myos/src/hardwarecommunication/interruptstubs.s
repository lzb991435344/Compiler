

#lesson 06


.set IRQ_BASE, 0x20

.section .text

.extern _ZN4myos21hardwarecommunication16InterruptManager15handlerInterruptEhj
.global _ZN16InterruptManager22IgnoreInterruptRequestEv

.macro HandleException num
.global _ZN4myos21hardwarecommunication16InterruptManager19HandlerException\num\()Ev
	_ZN4myos21hardwarecommunication16InterruptManager19HandlerException\num\()Ev:
	movb $\num,(interruptnumber)
	jmp int_bottom
.endm

#.global _ZN16InterruptManager26handlerInterruptRequest ??
.macro HandleInterruptRequest num
.global _ZN4myos21hardwarecommunication16InterruptManager26HandlerInterruptRequest\num\()Ev
    _ZN4myos21hardwarecommunication16InterruptManager26HandlerInterruptRequest\num\()Ev:
	movb $\num + IRQ_BASE,(interruptnumber)
	jmp int_bottom
.endm


HandleInterruptRequest 0x00
HandleInterruptRequest 0x01
#lesson08
HandleInterruptRequest 0x0C

#jump to interrupt funtion
int_bottom:
	
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs


	push %esp
	push (interruptnumber)
	call _ZN4myos21hardwarecommunication16InterruptManager15handlerInterruptEhj
	#add $5,%esp
	add %esp, 6
	movl %eax,%esp


	popl %gs
	popl %fs
	popl %es
	popl %ds
	popa
.global _ZN4myos21hardwarecommunication16InterruptManager15IgnoreInterruptIgnoreEv
_ZN4myos21hardwarecommunication16InterruptManager15IgnoreInterruptIgnoreEv:
	iret

.data
	interruptnumber: .byte 0
