  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,1000
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digi
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
  #
  
hexasc:	andi	$a0, $a0, 0xF		# Maskar dem efterfr�gade bitarna och ignorerar v�rden >15
	li	$a1, 0x9		# S�tter a1 som 9 f�r att kunna j�mf�ra
	ble	$a0, $a1, nr		# j�mf�r om f�rsta nibbeln i a0 �r mindre �n <= 9 och om den �r det hoppar vi till nr
	nop
	addi	$a2, $a0, 0x37		# s�tter den som r�tt ascii
	move	$v0, $a2		# flyttar v�rdet till v0

	jr	$ra			# hoppar tillbaka dit funktionen blev kallad
	nop
	
nr:	addi	$a2, $a0, 0x30		# s�tter den som r�tt ascii
	move	$v0, $a2		# flyttar v�rdet till v0
	
	jr	$ra			# hoppar tillbaka dit funktionen blev kallad
	nop
	
delay:	li	$a1, 0x00
	ble	$a0, $a1, stop		# while ( ms > 0), hoppar inte in i delay om a0 �r mindre �n 0
	nop
	
	addi	$a0, $a0, -1		# ms = ms - 1
	addi	$s0, $0, 0		# i = 0
	addi	$t0, $0, 20		#$t0 = 1000
	
loop_start:
	slt	$t1, $s0, $t0		# if(i<1) then $t1 = 1 else $t1 = 0
	beq	$t1, $0, delay		# hoppar till delay om $s0 >= $t0
	nop				# skippar
	addi	$s0, $s0, 1		# i = i + 1, i stegar upp 
	j	loop_start		# b�rjar om for loopen
	nop
	
stop:	jr	$ra
	nop
	
time2string:
	PUSH($t0)
	PUSH($ra)
	PUSH($t1)
	move	$s0, $a1		#v�rdet
	move	$s1, $a0		#addressen till v�rdet
	
	
	#F�rsta siffran X0:00
	andi	$t0, $s0, 0xF000
	srl	$a0, $t0, 12 		# shiftar den till LSB
	jal	hexasc			# skickar till hexasc och l�nkar tillbaka hit med $ra
	nop				# Ett mellanrum ifall att
	sb	$v0, 0($s1)		# L�gger byten p� r�tt st�lle i $a0
	
	#Andra siffran 0X:00
	andi	$t0, $s0, 0xF00
	srl	$a0, $t0, 8		# shiftar den till LSB
	jal	hexasc			# skickar till hexasc och l�nkar tillbaka hit med $ra
	nop				# Ett mellanrum ifall att
	sb	$v0, 1($s1)		# L�gger byten p� r�tt st�lle i $a0
	
	#Semikolon
	li	$v0, 0x3A
	sb 	$v0, 2($s1)
		
	#Tredje siffran 00:X0
	andi	$t0, $s0, 0xF0
	srl	$a0, $t0, 4		# shiftar den till LSB
	jal	hexasc			# skickar till hexasc och l�nkar tillbaka hit med $ra
	nop				# Ett mellanrum ifall att
	sb	$v0, 3($s1)		# L�gger byten p� r�tt st�lle i $a0
	
	#Fj�rde siffran 00:0X
	andi	$a0, $s0, 0xF
					# Beh�ver inte shifta eftersom den �r p� r�tt st�lle
	jal	hexasc			# skickar till hexasc och l�nkar tillbaka hit med $ra
	nop				# Ett mellanrum ifall att
	sb	$v0, 4($s1)		# L�gger byten p� r�tt st�lle i $a0
	
	#Null
	li	$v0, 0x00
	sb	$v0, 5($s1)
	
	POP($t1)
	POP($ra)
	POP($t0)	
	jr	$ra
	nop

	
	
	
