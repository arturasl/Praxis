# vim: ft=gas
/* http://programmingpraxis.com/2011/04/08/credit-card-validation/ */

.equ SYS_EXIT, 1
.equ SYS_WRITE, 4
.equ SYS_READ, 3
.equ STDOUT, 1
.equ STDIN, 0
.equ INIT_LINUX, 0x80
.equ LOCAL1, -4
.equ PARAM1, 8
.equ PARAM2, 12
.equ BUFF_SIZE, 256

.section .data
	szAskNumber:
		.asciz "Enter credit card number: "
	nCreditCard:
		.long 0
	nSum:
		.long 0
	nIsValid:
		.long 0
	szOutput:
		.asciz "Sum is: %d\nIs valid: %d\n"

.section .bss
	.lcomm szCreditCard, BUFF_SIZE

.section .text
.global _start
_start:
	/*print "Enter credit card number: "*/
	movl $SYS_WRITE, %eax
	movl $STDOUT, %ebx
	movl $szAskNumber, %ecx
	movl $26, %edx
	int $INIT_LINUX

	/*read credit card*/
	movl $SYS_READ, %eax
	movl $STDIN, %ebx
	movl $szCreditCard, %ecx
	mov $BUFF_SIZE, %edx
	int $INIT_LINUX

	movl %eax, nCreditCard

	/*calculate sum*/
	pushl $szCreditCard
	pushl nCreditCard
	call fnLuhn
	addl $8, %esp

	movl %eax, nSum

	/*check if it is correct*/
	pushl nSum
	call fnIsValid
	addl $4, %esp

	movl %eax, nIsValid

	pushl nIsValid
	pushl nSum
	pushl $szOutput
	call printf
	addl $12, %esp

	/*try to make valid*/
	/*append 0*/
	movl nCreditCard, %ebx
	/*for \n*/
	decl %ebx
	movb $'0', szCreditCard(, %ebx, 1)
	incl nCreditCard

	/*calculate sum*/
	pushl $szCreditCard
	pushl nCreditCard
	call fnLuhn
	addl $8, %esp

	movl %eax, nSum

	/*check if it is correct*/
	pushl nSum
	call fnIsValid
	addl $4, %esp

	cmpl $1, %eax
	je now_it_is_valid
		/*nSum %= 10*/
		movl $10, %edx
		movl nSum, %eax

		divb %dl

		movb %ah, %al
		xorb %ah, %ah
		movl %eax, nSum

		/*nSum = 10 - nSum*/
		movl $10, %edx
		subl nSum, %edx
		movl %edx, nSum

		/*szCreditCard += nSum*/
		addl $'0', nSum
		movb nSum, %al

		movl nCreditCard, %ebx
		decl %ebx
		decl %ebx
		movb %al, szCreditCard(, %ebx, 1)
	now_it_is_valid:

	/*print correct answer*/
	movl $SYS_WRITE, %eax
	movl $STDOUT, %ebx
	movl $szCreditCard, %ecx
	movl $nCreditCard, %edx
	int $INIT_LINUX

	/*exit 0*/
	movl $0, %ebx
	movl $SYS_EXIT, %eax
	int $INIT_LINUX

	/*Function wich checs if identifying number is correct*/
	/*Parameters:*/
		/*Lugn sum*/
	/*Returns:*/
		/*1 - if number is correct*/
		/*0 - otherwise*/
	.type fnIsValid, @function
	fnIsValid:
		pushl %ebp
		movl %esp, %ebp

		movl PARAM1(%ebp), %eax
		movl $10, %edx

		divb %dl

		cmpb $0, %ah
		jne invalid
			movl $1, %eax
			jmp if_invalid_end
		invalid:
			movl $0, %eax
		if_invalid_end:

		leave
		ret

	 /*Function wich calculates sum according to Luhn algorithm*/
	 /*Parameters:*/
		 /*Size of the buffer*/
		 /*Buffer address*/
	.type fnLuhn, @function
	fnLuhn:
		pushl %ebp
		movl %esp, %ebp

		/*make some place for a variable which will show if current number is double*/
		subl $1, %esp
		movb $0, LOCAL1(%ebp)

		/*%edi is offset from the beginning of the buffer*/
		movl PARAM1(%ebp), %edi
		decl %edi

		/*%ebx is an address of first byte in buffer*/
		movl PARAM2(%ebp), %ebx

		/*%ecx is a sum which will be returned*/
		xor %ecx, %ecx

		/*%eax is currently parsed digit*/

		main_loop:
			cmpl $0, %edi
			jl main_loop_end

			/*put right most digit to %eax*/
			xorl %eax, %eax
			movb (%ebx, %edi, 1), %al
			subb $'0', %al

			/*we are interested just in digits*/
			cmpb $0, %al
			jl not_a_number
			cmpb $9, %al
			jg not_a_number

				cmpb $1, LOCAL1(%ebp)
				jne not_double
					movb $2, %dl
					mulb %dl
					movb $10, %dl
					divb %dl

					xorl %edx, %edx
					movb %ah, %dl
					xorb %ah, %ah

					addl %eax, %ecx
					addl %edx, %ecx

					jmp if_not_double_end
				not_double:
					addl %eax, %ecx
				if_not_double_end:

				/*LOCAL1 = (LOCAL1 + 1) % 2*/
				xorl %eax, %eax
				movb LOCAL1(%ebp), %al
				incb %al
				movb $2, %dl
				divb %dl
				movb %ah, LOCAL1(%ebp)

			not_a_number:

			decl %edi

			jmp main_loop
		main_loop_end:

		movl %ecx, %eax

		leave
		ret
