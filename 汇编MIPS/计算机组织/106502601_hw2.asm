        .text
        .globl  main
main:
		li 		$t0, 0
		li		$t1, 8
		li		$t2, 10
		li		$t3, 8
		li		$s7, 4
        li      $v0, 4                  # User1
        la      $a0, print1
        syscall
		li      $v0, 4                  
        la      $a0, prompt
        syscall
		
        li      $v0, 5                  # Read int n
        syscall
        move    $s0, $v0				# $s0 = n
		
		li      $v0, 4					
        la      $a0, print2
        syscall

nchange:
		li 		$t4, 0
		li 		$t5, 0
		li 		$t6, 0
		li 		$t7, 0
		divu	$s0, $t2
		mfhi	$t4						# $t4 = (4)
		sub		$s0, $s0, $t4
		divu	$s0, $t2					
		mflo	$s0						
		divu	$s0, $t2
		mfhi	$t5 					# $t5 = (3)
		sub		$s0, $s0, $t5
		divu	$s0, $t2					
		mflo	$s0
		divu	$s0, $t2
		mfhi	$t6						# $t6 = (2)
		sub		$s0, $s0, $t6
		divu	$s0, $t2					
		mflo	$s0
		divu	$s0, $t2
		mfhi	$t7						# $t7 = (1)
		bne		$t1, $t3, checkwarn 
		
nload:
		move	$s1,$t7					# $s1 = (1)
 		move	$s2,$t6					# $s2 = (2)
		move	$s3,$t5					# $s3 = (3)
		move	$s4,$t4					# $s4 = (4)
		
Guess:									# User2
		beq		$t0, $t1, R2
		addi	$t1, $t1, -1				# $t1--
		li      $v0, 4					
        la      $a0, print3
        syscall
		li      $v0, 4					
        la      $a0, prompt
        syscall
		li      $v0, 5                  # input
        syscall
        move    $s0, $v0
		li		$t8, 0					#A
		li		$t9, 0					#B
		j		nchange
		
checkwarn:
		beq		$t7, $t6, R3
		beq		$t7, $t5, R3
		beq		$t7, $t4, R3
		beq		$t6, $t5, R3
		beq		$t6, $t4, R3
		beq		$t5, $t4, R3
		jal		checkA
checkA:
		addi 	$ra, $ra, 8
		beq		$t7, $s1, addA
		addi 	$ra, $ra, 8
		beq		$t6, $s2, addA
		addi 	$ra, $ra, 8
		beq		$t5, $s3, addA
		addi 	$ra, $ra, 8
		beq		$t4, $s4, addA
		jal		checkB
checkB:		
		addi 	$ra, $ra, 8
		beq		$t7, $s2, addB
		addi 	$ra, $ra, 8
		beq		$t7, $s3, addB
		addi 	$ra, $ra, 8
		beq		$t7, $s4, addB
		addi 	$ra, $ra, 8
		beq		$t6, $s1, addB
		addi 	$ra, $ra, 8
		beq		$t6, $s3, addB
		addi 	$ra, $ra, 8
		beq		$t6, $s4, addB
		addi 	$ra, $ra, 8
		beq		$t5, $s1, addB
		addi 	$ra, $ra, 8
		beq		$t5, $s2, addB
		addi 	$ra, $ra, 8
		beq		$t5, $s4, addB
		addi 	$ra, $ra, 8
		beq		$t4, $s1, addB
		addi 	$ra, $ra, 8
		beq		$t4, $s2, addB
		addi 	$ra, $ra, 8
		beq		$t4, $s3, addB	
		li      $v0, 1		
        move    $a0, $t8
        syscall		
		li      $v0, 4					
        la      $a0, PA
        syscall		
		li      $v0, 1
		move    $a0, $t9
        syscall		
		li      $v0, 4					
        la      $a0, PB
        syscall
		beq		$t8, $s7, R1			#win
		j		Guess
addA:	
		addi	$t8, $t8,1				#A++
		jr		$ra
addB:	
		addi	$t9, $t9,1				#B++
		jr		$ra
R1:
		li      $v0, 4					
        la      $a0, result1
        syscall
		j	finish
		
R2:
		li      $v0, 4					
        la      $a0, result2
        syscall
		j	finish
		
R3:
		li      $v0, 4					
        la      $a0, result3
        syscall
		j	finish
		
finish:
		li      $v0, 10
        syscall
		
        .data
print1:	.asciiz "User1 enter the number:\n"
prompt: .asciiz ">"                   
print2:	.asciiz "Start------------------- \n"
print3:	.asciiz "User2 guess:\n"
PA:		.asciiz "A"
PB:		.asciiz "B\n"
result1:.asciiz "You win!\n"
result2:.asciiz "You lose.\n"
result3:.asciiz "WARNING:redundant digits\n"
