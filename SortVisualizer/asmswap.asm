section .text
global asmswap

asmswap:
	mov DWORD eax, [rcx]
	mov DWORD ebx, [rdx]
	mov DWORD [rdx], eax
	mov DWORD [rcx], ebx
	
	ret
	