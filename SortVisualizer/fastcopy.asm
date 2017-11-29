section .text
global fastcopy


fastcopy:
	mov rdi, rcx
	mov rsi, rdx
	mov ecx, r8d
	
	mov r8, rsi
	add r8, 4h
	mov r9, rsi
	add r9, 8h
	mov r10, rsi
	add r10, 0ch
	
	mov r11, rdi
	add r11, 4h
	mov r12, rdi
	add r12, 8h
	mov r13, rdi
	add r13, 0ch
	
	shr ecx, 2
	
	copyLoop:
		mov DWORD eax, [rsi]
		mov DWORD edx, [r8]
		mov DWORD r14d, [r9]
		mov DWORD r15d, [r10]
		
		mov DWORD [rdi], eax
		mov DWORD [r11], edx
		mov DWORD [r12], r14d
		mov DWORD [r13], r15d
		
		add rdi, 10h
		add r8, 10h
		add r9, 10h
		add r10, 10h
		
		add rsi, 10h
		add r11, 10h
		add r12, 10h
		add r13, 10h
		
		loop copyLoop
		
	ret
		