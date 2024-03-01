  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #

.global enable_interrupt
enable_interrupt:
	ei	
	jr $ra

hexasc:	
	andi	$a0, $a0, 0xF		# Maskar dem efterfrågade bitarna och ignorerar värden >15
	li	$a1, 0x9		# Sätter a1 som 9 för att kunna jämföra
	ble	$a0, $a1, nr		# jämför om första nibbeln i a0 är mindre än <= 9 och om den är det hoppar vi till nr
	nop
	addi	$a2, $a0, 0x37		# sätter den som rätt ascii
	move	$v0, $a2		# flyttar värdet till v0

	jr	$ra			# hoppar tillbaka dit funktionen blev kallad
	nop
	
nr:	addi	$a2, $a0, 0x30		# sätter den som rätt ascii
	move	$v0, $a2		# flyttar värdet till v0
	
	jr	$ra			# hoppar tillbaka dit funktionen blev kallad
	nop

.global delay
delay:	
	PUSH	$s0

	li	$a1, 0x00
	ble	$a0, $a1, stop		# while ( ms > 0), hoppar inte in i delay om a0 är mindre än 0
	nop
	
	addi	$a0, $a0, -1		# ms = ms - 1
	addi	$s0, $0, 0		# i = 0
	addi	$t0, $0, 3800		# $t0 = 4711				
	
loop_start:
	slt	$t1, $s0, $t0		# if(i<1) then $t1 = 1 else $t1 = 0
	beq	$t1, $0, delay		# hoppar till delay om $s0 >= $t0
	nop				# skippar
	addi	$s0, $s0, 1		# i = i + 1, i stegar upp 
	j	loop_start		# börjar om for loopen
	nop
	
stop:	
	POP $s0

	jr	$ra
	nop

.global	time2string
time2string:
	PUSH	$s1
	PUSH	$ra
	PUSH	$s0

	move	$s0, $a1		#värdet
	move	$s1, $a0		#addressen till värdet
	
	
	#Första siffran X0:00
	andi	$t0, $s0, 0xF000
	srl	$a0, $t0, 12 		# shiftar den till LSB
	jal	hexasc			# skickar till hexasc och länkar tillbaka hit med $ra
	nop				# Ett mellanrum ifall att
	#move 	$t0, $v0
	sb	$v0, 0($s1)		# Lägger byten på rätt ställe i $a0
	
	#Andra siffran 0X:00
	andi	$t0, $s0, 0xF00
	srl	$a0, $t0, 8		# shiftar den till LSB
	jal	hexasc			# skickar till hexasc och länkar tillbaka hit med $ra
	nop				# Ett mellanrum ifall att
	#move 	$t0, $v0
	sb	$v0, 1($s1)		# Lägger byten på rätt ställe i $a0
	
	#Semikolon
	li	$v0, 0x3A
	sb 	$v0, 2($s1)
		
	#Tredje siffran 00:X0
	andi	$t0, $s0, 0xF0
	srl	$a0, $t0, 4		# shiftar den till LSB
	jal	hexasc			# skickar till hexasc och länkar tillbaka hit med $ra
	nop				# Ett mellanrum ifall att
	#move 	$t0, $v0
	sb	$v0, 3($s1)		# Lägger byten på rätt ställe i $a0
	
	#Fjärde siffran 00:0X
	andi	$a0, $s0, 0xF
					# Behöver inte shifta eftersom den är på rätt ställe
	jal	hexasc			# skickar till hexasc och länkar tillbaka hit med $ra
	nop				# Ett mellanrum ifall att
	#move 	$t0, $v0
	sb	$v0, 4($s1)		# Lägger byten på rätt ställe i $a0
	
	#Null
	li	$v0, 0x00
	sb	$v0, 5($s1)
	
	POP		$s0
	POP		$ra
	POP		$s1	
	jr	$ra
	nop