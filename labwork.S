  # labwork.S
  # Written 2015 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1 2015-2016.
  # The macros PUSH and POP are in the public domain.

.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm

  # You can add your own code here
  #

	.global delay
	.global time2string
	.global enable_interrupt
		
	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "59:57\0"
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
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
  #



# Copied from assignment 2
hexasc:
	andi $a0, $a0, 15	# chop off everything but the 4 least significant bytes	
	addi $v0, $a0, 0x30	# always add 0x30 to match ASCII table
	blt $a0, 10, return	# if $a0 < 10, jump directly to return
	nop			# handle delayed branching
	addi $v0, $v0, 0x07	# if $a0 >= 10 add 0x07, since letters are 7 steps higher in ASCII
	
return:
	jr $ra			# Return when done
	nop

# Delay
# Called with $a0 = number of milliseconds delay should run

# $t0 = 4711 (runs per ms)
# $t1 = $a0 (number of ms)
# $t2 = 0 (inner loop counter)

delay:
	addi $t0, $0, 13500	# constant specifying how many loops a millisecond is
	add $t1, $a0, $0	# iterator, $t1 = $a0 (number of ms)

delayloop:	
	blt $t1, 1, return	# break if remaining milliseconds <= 0
	nop
	addi $t1, $t1, -1	# withdraw 1 ms from counter	
	add $t2, $0, $0		# reset inner loop counter
	
delayinner:
	addi $t2, $t2, 1	# increase inner loop counter
	beq $t2, $t0, delayloop	# if limit reached 
	nop
	
	j delayinner
	nop 

time2string:
	# Free up variables by pushing to stack
	PUSH $s0
	PUSH $s1
	PUSH $ra
	
	# $s0 = MEMORY ADDRESS where ASCII text should be stored
	# $s1 = 16 LSB's contain time info (4x4-bit digits)
	move $s0, $a0
	move $s1, $a1
	
	# Clean first 16 bits of $s1 from unwanted input
	sll $s1, $s1, 16
	srl $s1, $s1, 16	# Clean first 16 bits of $a1 from unwanted input
	
	# FIRST DIGIT: Shift right 12 bits
	srl $a0, $s1, 12
	jal hexasc
	nop
	sb $v0, 0($s0)		# Save digit to RAM

	# SECOND DIGIT: Shift right 8 bits
	srl $a0, $s1, 8
	jal hexasc
	nop
	sb $v0, 1($s0)		# Save third digit to RAM

	addi $t2, $0, 0x3A	# Construct ASCII colon
	sb $t2, 2($s0)		# Save colon to RAM

	# THIRD DIGIT: Shift right 4 bits
	srl $a0, $s1, 4
	jal hexasc
	nop
	sb $v0, 3($s0)		# Save third digit to RAM
	
	# FOURTH DIGIT: No shifting necessary
	move $a0, $s1
	jal hexasc
	nop
	
	sb $v0, 4($s0)		# Save fourth digit to RAM
	sb $0, 5($s0)		# Save null byte to RAM
	
	andi $s1, $s1, 15	# chop off everything but the 4 least significant bytes of $s1
	bne $s1, 2, time2str2	# proceed if number is not equal to two	
	
	addi $t0, $0, 0x54	# Construct T
	addi $t1, $0, 0x57	# Construct W
	addi $t2, $0, 0x4f	# Construct O
	
	sb $t0, 4($s0)		# Store T
	sb $t1, 5($s0)		# Store W
	sb $t2, 6($s0)		# Store O
	sb $0, 7($s0)		# Store null byte
	
time2str2:

	POP $ra			# Fetch $ra from stack
	POP $s1
	POP $s0
	
	jr $ra
	nop

enable_interrupt:
	ei
	jr $ra