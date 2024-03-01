
	addi	$a0, $0, 7
	add	$a1, $0, $a0
	beq	$a0, 0, stop1
	beq	$a0, 1, stop1

plus:	
	addi	$a1, $a1, -1
	beq	$a1, 0, fac
	
	add	$v0, $v0, $a0
	
	beq	$a0, $a0, plus
	
plus1:	
	addi	$a1, $a1, -1
	beq	$a1, 1, fac
	
	add	$v0, $v0, $a2
	
	beq	$a0, $a0, plus1

fac:
	addi	$a0, $a0, -1
	beq	$a0, 1, stop
	
	add	$a2, $v0, $0
	add	$a1, $0, $a0
	
	beq	$a0, $a0, plus1
	
stop:	
	beq	$0, $0, stop

stop1:
	addi	$v0, $0, 1
	beq	$0, $0, stop
	