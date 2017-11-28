section .text
global asmtests



asmtests:
	push rbp
	mov rbp, rsp
	sub rsp, 20h
	
	mov rsp, rbp
	pop rbp
	ret