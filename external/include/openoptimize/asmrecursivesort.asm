section .text
global asmrecursivesort


asmrecursivesort:
	firstIf:
		push rbp
		
		mov rsi, rcx
		mov rdi, rdx
		mov ebx, r8d
		mov ebp, r9d
		
		; rsi = sortedData pointer
		; rdi = readData pointer
		; ebx = start
		; ebp = end
		; rsp = free
		; r8d = diff
		; r9d = zzz
		; r10d = i
		; r11d = j
		
		cmp ebx, ebp
		jne startSecondIF
		pop rbp
		ret
		
	startSecondIF:
		mov eax, ebp
		sub eax, ebx
		cmp eax, 1
		jne afterSecondIf
		
		; Store readData[end] into floatHelper
		mov DWORD eax, [rdi+rbp]
		
		; Find minimum
		fld DWORD [rdi+rbp]
		fld DWORD [rdi+rbx]
		fcomi st0, st1
		ja secondMinimum
		jmp checkMax
		
		secondMinimum:
			mov DWORD [rdi+rbx], eax
		
		checkMax:
			fcomip st0, st1
			fstp
			ja secondMax
			jmp endSecondIf
			
		secondMax:
			mov DWORD [rdi+rbp], eax
		
	endSecondIf:
		pop rbp
		ret
			
		
	afterSecondIf:
		; Set diff
		mov r8d, ebp
		sub r8d, ebx
		
		; Set zzz
		mov r9d, ebx
		mov eax, r8d
		shr eax, 1h
		add r9d, eax
		
		; Save all needed registers
		push rsi
		push rdi
		push rbx
		push rbp
		push rsp
		push r8
		push r9
		
		; Call first recursive sort
		mov rcx, rsi
		mov rdx, rdi
		mov r8d, ebx
		call asmrecursivesort
		
		; Call second recursive sort
		
		mov rcx, rsi
		mov rdx, rdi
		mov r8d, r9d
		inc r8d
		mov r9d, ebp
		call asmrecursivesort
		
		; After calls	
		pop r9
		pop r8
		pop rsp
		pop rbp
		pop rbx
		pop rdi
		pop rsi
		
		mov r10d, ebx
		mov r11d, r9d
		inc r11d 
		
		; Call asmmerge
		mov rcx, rsi
		mov rdx, rdi
		mov r8d, ebx
		mov r9d, r10d
		push r9
		push rbp		
		call asmmerge
		pop rbp
		pop r9
		
		pop rbp
		ret
		
		
		
		
		
		
		
		
;;;;;;;;;;;;;;;;;;;; ASM MERGE		
	
asmmerge:

	push rbp
	mov rbp, rsp
	
	mov r10, rcx				; sortedData pointer
	mov rbx, rdx				; readData pointer
	mov esi, r8d				; leftStart (int)
	mov edi, r9d				; rightStart (int)
	mov DWORD r11d, [rsp+18h]	; leftEnd (int)
	mov DWORD r12d, [rsp+10h]	; rightEnd(int)

	; r8d = diff
	; r10 = sortedData pointer
	; r11 = free
	; r12 = begin^th element of sortedData
	; r13 = begin^th element of readData
	; rdx = maximum sortedData
	; r14 = leftEnd pointer
	; r15 = rightEnd pointer
	; FREE
	; r11
	
	; Set leftStart and rightStart data pointers (on readData) (r9 now contains leftStart)
	mov eax, 4h
	mul esi
	mov r9, rax
	add rax, rbx
	mov rsi, rax
	
	mov eax, 4h
	mul edi
	add rax, rbx
	mov rdi, rax
	
	; Set leftEnd and rightEnd data pointers (rcx now contains rightEnd)
	mov eax, 4h
	mul r11d
	add rax, rbx
	mov r14, rax
	
	mov eax, 4h
	mul r12d
	mov rcx, rax
	add rax, rbx
	mov r15, rax
	
	; Initialize r8d(diff) and adjust to 4 Bytes
	mov r8, r15
	sub r8, rsi
	add r8, 4h

	; Set r12 to r10 and initialize begin^th of sortedData and readData
	mov r12, r10
	mov r13, rbx
	add r12, r9
	add r13, r9
	
	; Calculate maximum sortedData address
	mov rdx, r10
	add rdx, rcx
	
	; Adjust sortedData pointer
	add r10, r9
	
	cmp r10, rdx
	ja endAll
	mainLoop:
		startFirstIf:
			cmp rsi, r14
			jna startSecondIf
				cmp rdi, r15
				ja endAll
				mov DWORD r11d, [rdi]
				add rdi, 4h
				mov DWORD [r10], r11d				
				jmp endLoop
		
		startSecondIf:
			cmp rdi, r15
			jna startThirdIf
				cmp rsi, r14
				ja endAll
				mov DWORD r11d, [rsi]
				add rsi, 4h
				mov DWORD [r10], r11d				
				jmp endLoop
			
		startThirdIf:
			fld DWORD [rsi]
			fld DWORD [rdi]
			fcomip st0, st1
			fstp
			jnb startFourthIf
				mov DWORD r11d, [rdi]
				add rdi, 4h
				mov DWORD [r10], r11d				
				jmp endLoop
		
		startFourthIf:
			mov DWORD r11d, [rsi]
			add rsi, 4h
			mov DWORD [r10], r11d		
			
		endLoop:
			add r10, 4h
			cmp r10, rdx
			jna mainLoop
				
	endAll:
		mov ecx, r8d
		mov rdi, r13
		mov rsi, r12
		rep movsb
		
		mov rsp, rbp
		pop rbp
		ret