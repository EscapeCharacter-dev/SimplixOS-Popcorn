enter_v86:
	mov ebp, esp

	push dword [ebp + 4]
	push dword [ebp + 8]
	pushfd
	or dword [esp], (1 << 17)
	push dword [ebp + 12]
	push dword [ebp + 16]
	iret


detect_v86:
	smsw ax
	and eax, 1
	ret
