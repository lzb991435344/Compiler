

#lesson 06


.set IRQ_BASE, 0x20

.section .text

.extern _ZN16InterruptManager15handlerInterruptEhj
.global _ZN16InterruptManager22IgnoreInterruptRequestEv

.macro HandleException num
.global _ZN16InterruptManager16HandlerException\num\()Ev
	_ZN16InterruptManager16HandlerException\num\()Ev:
	movb $\num,(interruptnumber)
	jmp int_bottom
.endm

#.global _ZN16InterruptManager26handlerInterruptRequest ??
.macro HandleInterruptRequest num
.global _ZN16InterruptManager26HandlerInterruptRequest\num\()Ev
    _ZN16InterruptManager26HandlerInterruptRequest\num\()Ev:
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
	call _ZN16InterruptManager16handlerInterruptEhj
	#add $5,%esp

	movl %eax,%esp


	popl %gs
	popl %fs
	popl %es
	popl %ds
	popa

_ZN16InterruptManager22IgnoreInterruptRequestEv:
	iret

.data
	interruptnumber: .byte 0
