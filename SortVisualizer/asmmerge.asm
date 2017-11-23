section .text
global asmmerge



asmmerge:

	push rbp
	
	xor rsi, rsi
	xor rdi, rdi

	mov r10, rcx				; sortedData pointer
	mov rbx, rdx				; readData pointer
	mov esi, r8d				; leftStart (int)
	mov edi, r9d				; rightStart (int)
	mov DWORD r14d, [rsp+30h]	; leftEnd (int)
	mov DWORD r15d, [rsp+38h]	; rightEnd(int)
	
	; r8d = diff
	; r9d = begin
	; r12 = start of sortedData
	; rdx = maximum sortedData
	
	;FREE
		;r11d

	; Initialize 
	mov r12, r10
	
	; Initialize r8d and adjust to 4 Bytes
	mov r8d, r15d
	add r8d, esi
	inc r8d
	mov eax, 4h
	mul r8d
	mov r8d, eax
	
	; Adjust leftStart, rightStart, leftEnd and rightEnd address offsets
	mov eax, 4h
	mul esi
	mov esi, eax
	
	mov eax, 4h
	mul edi
	mov edi, eax
	
	mov eax, 4h
	mul r14d
	mov r14d, eax
	
	mov eax, 4h
	mul r15d
	mov r15d, eax
	
	; Initialize begin with leftStart
	mov r9d, esi
	
	
	; Calculate maximum sortedData address
	mov rdx, r10
	add edx, r15d
	
	; Adjust sortedData pointer
	add r10, rsi
	
	cmp r10, rdx
	ja endAll
	mainLoop:
		startFirstIf:
			cmp esi, r14d
			jna startSecondIf
				cmp edi, r15d
				ja endLoop
				mov DWORD r11d, [rbx+rdi]
				mov DWORD [r10], r11d
				add edi, 4h
				jmp endLoop
		
		startSecondIf:
			cmp edi, r15d
			jna startThirdIf
				cmp esi, edi
				ja endLoop
				mov DWORD r11d, [rbx+rsi]
				mov DWORD [r10], r11d
				add esi, 4h
				jmp endLoop
			
		startThirdIf:
			fld DWORD [rbx, rsi]
			fld DWORD [rbx+rdi]
			fcomp st0, st1
			fst
			jnb startFourthIf
				mov DWORD r11d, [rbx+rdi]
				mov DWORD [r10], r11d
				add edi, 4h
				jmp endLoop
		
		startFourthIf:
			mov DWORD r11d, [rbx+rsi]
			mov DWORD [r10], r11d
			add esi, 4h
			jmp endLoop
			
		endLoop:
			add r10, 4h
			cmp r10, rdx
			jna mainLoop
				
	endAll:
		xor rbp, rbp
		mov ebp, r9d
		cld
		lea rdi, [rbx+rbp]
		lea rsi, [r12]
		mov ecx, r8d
		rep movsb
		
		pop rbp
		ret