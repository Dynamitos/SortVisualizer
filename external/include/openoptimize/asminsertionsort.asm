section .text
global asminsertionsort


asminsertionsort:
	mov rsi, rcx
	mov ecx, edx
	
	; DATA
	; rsi = A[i]
	; rdi = A[j]
	; r8d = i
	; r9d = j
	; ebx = einzusortierender_wert
	; eax = FREE
	; r10d = FREE
	
	; Set rsi to &A[i=1] and decrease ecx by one
	add rsi, 4h
	dec ecx
	
	test ecx, ecx
	jz endAll
	
	mov r8d, 1h
	
	startFirstLoop:
		mov DWORD ebx, [rsi]
		
		; Set j to i thus set rdi to rsi
		mov rdi, rsi
		mov r9d, r8d
		
		startSecondLoop:
			cmp r9d, 0h
			jna endFirstLoop
			cmp [rdi-4h], ebx
			jna endFirstLoop
			
			mov DWORD eax, [rdi-4h]
			mov DWORD [rdi], eax
			
			dec r9d
			sub rdi, 4h
			
			jmp startSecondLoop		
	
		endFirstLoop:
			mov [rdi], ebx
			add rsi, 4h
			inc r8d
			loop startFirstLoop			
			
	
	endAll:
		ret
