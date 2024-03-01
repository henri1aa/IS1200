
	addi	$a0, $0, 8
	addi	$v0, $0, 1
	add	$a1, $0, $a0
loop:
	beq	$a0, 0, stop
	
	mul	$v0, $v0, $a0
	addi	$a0, $a0, -1
	
	beq 	$a0, $a0, loop
	
stop:
	beq	$0, $0, stop