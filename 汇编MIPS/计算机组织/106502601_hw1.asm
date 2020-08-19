        .text
        .globl  main
main:
		li      $t0, 2 					# i
		li      $t1, 0 					# 0
		li		$t5, 10					# 10
		li      $t6, 2 					
		
        li      $v0, 4                  # input
        la      $a0, print1
        syscall
		
		li      $v0, 4                  # String
        la      $a0, prompt
        syscall
        li      $v0, 5                  # Read int n
        syscall
        move    $s0, $v0				# $s0 = n
		li      $v0, 4					# output
        la      $a0, print2
        syscall
		beq		$s0, $t0, nchange		# n = 2
		
Nprime:
        beq     $t0, $s0, nchange		# i == n,break
		divu	$s0, $t0				# $hi = n%i
		mfhi	$t2						# $t2 = mod
		beq		$t2, $t1, R1			# not prime
		addi	$t0, $t0, 1				# i++
        j       Nprime					# Round again

R1:		
        li      $v0, 4                  # not prime
        la      $a0, result1
        syscall
		j		finish
		
nchange:
		divu	$s0, $t5
		mfhi	$t3						# $t3 = 0
		sub		$s0, $s0, $t3
		beq		$t1, $s0, R3
		divu	$s0, $t5					
		mflo	$t4						# $t4 = 00
		multu	$t3, $t5					
		mflo	$s0
		add		$s0, $s0, $t4
		j 		Emirp

Emirp:
		beq     $t6, $s0, R3			# i == n,Emirp
		divu	$s0, $t6				# $hi = n%i
		mfhi	$t7						# $t2 = mod
		beq		$t7, $t1, R2			# Prime
		addi	$t6, $t6, 1				# i++
        j       Emirp					# Round again

R2:
		li      $v0, 4                  # Prime
        la      $a0, result2
        syscall
		j		finish
		
R3:
		li      $v0, 4                  # emrip
        la      $a0, result3
        syscall
		j		finish

finish:
		j		main
		li      $v0, 10
        syscall
		
        .data
print1:	.asciiz "Input:\n"
prompt: .asciiz ">"                   
print2:	.asciiz "Output:\n"
result1:.asciiz "not prime\n"
result2:.asciiz "Prime\n"
result3:.asciiz "emirp\n"
