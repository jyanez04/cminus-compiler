# MIPS CODE GENERATED BY Compilers Class

.data

_L0: .asciiz "\n"
_L1: .asciiz "\n"
_L2: .asciiz "\n"
_L3: .asciiz "\n"
_L4: .asciiz "\n"
_L5: .asciiz "\n"
_L6: .asciiz "even: "
_L7: .asciiz "\n"
_L8: .asciiz "odd: "
_L9: .asciiz "\n"

.align 2

x: .space 4 # global variable
A: .space 400 # global variable

.text

.globl main

addNums:			# function definition
	move $a1, $sp		# activation record carve out copy SP
	subi $a1, $a1, 20		# activation record carve out copy size of function
	sw $ra, ($a1)		# store return address
	sw $sp, 4($a1)		# store the old stack pointer
	move $sp, $a1		# make SP the current activation record


	sw $t0, 8($sp)		# copy temp to formal param
	sw $t1, 12($sp)		# copy temp to formal param
	li $t1, 0		# var is a scalar
	la $a0, 8($sp)		# get base address of local array or scalar
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a0, ($a0)		# expression is a VAR
	sw $a0, 16($sp)		# store LHS value
	li $t1, 0		# var is a scalar
	la $a0, 12($sp)		# get base address of local array or scalar
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a0, ($a0)		# expression is a VAR
	move $a2, $a0		# store RHS into $a2
	lw $a0, 16($sp)		# load stored LHS back into $a0
	add $a0, $a0, $a2		# perform addition
	lw $ra, ($sp)		# restore old environment RA
	lw $sp, 4($sp)		# return from function, store SP

	jr $ra		# jump back to caller
	li $a0, 0		# return has no specific value, set to 0
	lw $ra, ($sp)		# restore old environment RA
	lw $sp, 4($sp)		# return from function, store SP

	jr $ra		# jump back to caller
main:			# function definition
	move $a1, $sp		# activation record carve out copy SP
	subi $a1, $a1, 140		# activation record carve out copy size of function
	sw $ra, ($a1)		# store return address
	sw $sp, 4($a1)		# store the old stack pointer
	move $sp, $a1		# make SP the current activation record


	li $a0, 0		# expression is a constant
	sw $a0, 60($sp)		# store LHS into temp space created by A_ASSIGN
	li $t1, 0		# var is a scalar
	la $a0, 52($sp)		# get base address of local array or scalar
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a1, 60($sp)		
	sw $a1, ($a0)		


	li $a0, 6		# expression is a constant
	sw $a0, 64($sp)		# store LHS into temp space created by A_ASSIGN
	li $a0, 0		# expression is a constant
	move $t1, $a0		# store index expression result into $t1
	sll $t1, $t1, 2		# multiply expression result by 4 to get internal array offset
	la $a0, 8($sp)		# get base address of local array or scalar
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a1, 64($sp)		
	sw $a1, ($a0)		


	li $a0, 0		# expression is a constant
	sw $a0, 68($sp)		# store LHS into temp space created by A_ASSIGN
	li $a0, 1		# expression is a constant
	move $t1, $a0		# store index expression result into $t1
	sll $t1, $t1, 2		# multiply expression result by 4 to get internal array offset
	la $a0, 8($sp)		# get base address of local array or scalar
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a1, 68($sp)		
	sw $a1, ($a0)		


	li $a0, 3		# expression is a constant
	sw $a0, 72($sp)		# store LHS into temp space created by A_ASSIGN
	li $a0, 2		# expression is a constant
	move $t1, $a0		# store index expression result into $t1
	sll $t1, $t1, 2		# multiply expression result by 4 to get internal array offset
	la $a0, 8($sp)		# get base address of local array or scalar
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a1, 72($sp)		
	sw $a1, ($a0)		


	li $a0, 5		# expression is a constant
	sw $a0, 76($sp)		# store LHS into temp space created by A_ASSIGN
	li $a0, 3		# expression is a constant
	move $t1, $a0		# store index expression result into $t1
	sll $t1, $t1, 2		# multiply expression result by 4 to get internal array offset
	la $a0, 8($sp)		# get base address of local array or scalar
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a1, 76($sp)		
	sw $a1, ($a0)		


	li $a0, 125		# expression is a constant
	sw $a0, 80($sp)		# store LHS into temp space created by A_ASSIGN
	li $a0, 5		# expression is a constant
	move $t1, $a0		# store index expression result into $t1
	sll $t1, $t1, 2		# multiply expression result by 4 to get internal array offset
	la $a0, A		# emit global var (array or scalar)
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a1, 80($sp)		
	sw $a1, ($a0)		


	li $a0, 34		# expression is a constant
	sw $a0, 84($sp)		# store LHS into temp space created by A_ASSIGN
	li $a0, 0		# expression is a constant
	move $t1, $a0		# store index expression result into $t1
	sll $t1, $t1, 2		# multiply expression result by 4 to get internal array offset
	la $a0, A		# emit global var (array or scalar)
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a1, 84($sp)		
	sw $a1, ($a0)		


	li $a0, 5		# expression is a constant
	move $t1, $a0		# store index expression result into $t1
	sll $t1, $t1, 2		# multiply expression result by 4 to get internal array offset
	la $a0, A		# emit global var (array or scalar)
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a0, ($a0)		# expression is a VAR
	sw $a0, 92($sp)		# store arg value into space reserved for it by function
	li $a0, 0		# expression is a constant
	move $t1, $a0		# store index expression result into $t1
	sll $t1, $t1, 2		# multiply expression result by 4 to get internal array offset
	la $a0, A		# emit global var (array or scalar)
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a0, ($a0)		# expression is a VAR
	sw $a0, 88($sp)		# store arg value into space reserved for it by function
	lw $a0, 92($sp)		
	move $t0, $a0		
	lw $a0, 88($sp)		
	move $t1, $a0		
	jal addNums		# call function
	sw $a0, 96($sp)		# store LHS into temp space created by A_ASSIGN
	li $t1, 0		# var is a scalar
	la $a0, 56($sp)		# get base address of local array or scalar
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a1, 96($sp)		
	sw $a1, ($a0)		


	li $t1, 0		# var is a scalar
	la $a0, 56($sp)		# get base address of local array or scalar
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a0, ($a0)		# expression is a VAR
	li $v0, 1		# about to print a number
	syscall		# call write number


	la $a0, _L0		# the string address
	li $v0, 4		# about to print string
	syscall		# call write string


	li $a0, 200		# expression is a constant
	sw $a0, 100($sp)		# store LHS into temp space created by A_ASSIGN
	li $a0, 34		# expression is a constant
	move $t1, $a0		# store index expression result into $t1
	sll $t1, $t1, 2		# multiply expression result by 4 to get internal array offset
	la $a0, A		# emit global var (array or scalar)
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a1, 100($sp)		
	sw $a1, ($a0)		


	li $a0, 0		# expression is a constant
	move $t1, $a0		# store index expression result into $t1
	sll $t1, $t1, 2		# multiply expression result by 4 to get internal array offset
	la $a0, A		# emit global var (array or scalar)
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a0, ($a0)		# expression is a VAR
	sw $a0, 108($sp)		# store LHS value
	li $a0, 2		# expression is a constant
	sw $a0, 104($sp)		# store LHS value
	li $a0, 0		# expression is a constant
	move $t1, $a0		# store index expression result into $t1
	sll $t1, $t1, 2		# multiply expression result by 4 to get internal array offset
	la $a0, A		# emit global var (array or scalar)
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a0, ($a0)		# expression is a VAR
	move $a2, $a0		# store RHS into $a2
	lw $a0, 104($sp)		# load stored LHS back into $a0
	mult $a0, $a2		# perform multiplication
	mflo $a0		# store mult result in $a0
	move $a2, $a0		# store RHS into $a2
	lw $a0, 108($sp)		# load stored LHS back into $a0
	add $a0, $a0, $a2		# perform addition
	sw $a0, 112($sp)		# store LHS into temp space created by A_ASSIGN
	li $a0, 2		# expression is a constant
	move $t1, $a0		# store index expression result into $t1
	sll $t1, $t1, 2		# multiply expression result by 4 to get internal array offset
	la $a0, 24($sp)		# get base address of local array or scalar
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a1, 112($sp)		
	sw $a1, ($a0)		


	li $a0, 5		# expression is a constant
	move $t1, $a0		# store index expression result into $t1
	sll $t1, $t1, 2		# multiply expression result by 4 to get internal array offset
	la $a0, A		# emit global var (array or scalar)
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a0, ($a0)		# expression is a VAR
	li $v0, 1		# about to print a number
	syscall		# call write number


	la $a0, _L1		# the string address
	li $v0, 4		# about to print string
	syscall		# call write string


	li $a0, 0		# expression is a constant
	move $t1, $a0		# store index expression result into $t1
	sll $t1, $t1, 2		# multiply expression result by 4 to get internal array offset
	la $a0, A		# emit global var (array or scalar)
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a0, ($a0)		# expression is a VAR
	li $v0, 1		# about to print a number
	syscall		# call write number


	la $a0, _L2		# the string address
	li $v0, 4		# about to print string
	syscall		# call write string


	li $a0, 2		# expression is a constant
	move $t1, $a0		# store index expression result into $t1
	sll $t1, $t1, 2		# multiply expression result by 4 to get internal array offset
	la $a0, 24($sp)		# get base address of local array or scalar
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a0, ($a0)		# expression is a VAR
	li $v0, 1		# about to print a number
	syscall		# call write number


	la $a0, _L3		# the string address
	li $v0, 4		# about to print string
	syscall		# call write string


	li $a0, 0		# expression is a constant
	move $t1, $a0		# store index expression result into $t1
	sll $t1, $t1, 2		# multiply expression result by 4 to get internal array offset
	la $a0, A		# emit global var (array or scalar)
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a0, ($a0)		# expression is a VAR
	move $t1, $a0		# store index expression result into $t1
	sll $t1, $t1, 2		# multiply expression result by 4 to get internal array offset
	la $a0, A		# emit global var (array or scalar)
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a0, ($a0)		# expression is a VAR
	li $v0, 1		# about to print a number
	syscall		# call write number


	la $a0, _L4		# the string address
	li $v0, 4		# about to print string
	syscall		# call write string


	li $a0, 137		# expression is a constant
	sw $a0, 116($sp)		# store LHS into temp space created by A_ASSIGN
	li $t1, 0		# var is a scalar
	la $a0, 44($sp)		# get base address of local array or scalar
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a1, 116($sp)		
	sw $a1, ($a0)		


	li $t1, 0		# var is a scalar
	la $a0, 44($sp)		# get base address of local array or scalar
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a0, ($a0)		# expression is a VAR
	li $v0, 1		# about to print a number
	syscall		# call write number


	la $a0, _L5		# the string address
	li $v0, 4		# about to print string
	syscall		# call write string


_L10:			# top of while
	li $t1, 0		# var is a scalar
	la $a0, 52($sp)		# get base address of local array or scalar
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a0, ($a0)		# expression is a VAR
	sw $a0, 120($sp)		# store LHS value
	li $a0, 10		# expression is a constant
	move $a2, $a0		# store RHS into $a2
	lw $a0, 120($sp)		# load stored LHS back into $a0
	slt $a0, $a0, $a2		# perform less-than operation
	beq $a0, 0, _L11		# exit out of while loop if condition is 0
	li $t1, 0		# var is a scalar
	la $a0, 52($sp)		# get base address of local array or scalar
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a0, ($a0)		# expression is a VAR
	sw $a0, 124($sp)		# store LHS value
	li $a0, 2		# expression is a constant
	move $a2, $a0		# store RHS into $a2
	lw $a0, 124($sp)		# load stored LHS back into $a0
	div $a0, $a2		# perform division in prep for modulo
	mfhi $a0		# store mod result in $a0
	sw $a0, 128($sp)		# store LHS value
	li $a0, 0		# expression is a constant
	move $a2, $a0		# store RHS into $a2
	lw $a0, 128($sp)		# load stored LHS back into $a0
	slt $t1, $a0, $a2		
	slt $t2, $a2, $a0		
	nor $a0, $t1, $t2		
	andi $a0, $a0, 1		
	beq $a0, 0, _L12		# jump to negative (else or null)
	la $a0, _L6		# the string address
	li $v0, 4		# about to print string
	syscall		# call write string


	li $t1, 0		# var is a scalar
	la $a0, 52($sp)		# get base address of local array or scalar
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a0, ($a0)		# expression is a VAR
	li $v0, 1		# about to print a number
	syscall		# call write number


	la $a0, _L7		# the string address
	li $v0, 4		# about to print string
	syscall		# call write string


	j _L13		# exit if
_L12:			# else (or null) section
	la $a0, _L8		# the string address
	li $v0, 4		# about to print string
	syscall		# call write string


	li $t1, 0		# var is a scalar
	la $a0, 52($sp)		# get base address of local array or scalar
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a0, ($a0)		# expression is a VAR
	li $v0, 1		# about to print a number
	syscall		# call write number


	la $a0, _L9		# the string address
	li $v0, 4		# about to print string
	syscall		# call write string


_L13:			# end of if
	li $t1, 0		# var is a scalar
	la $a0, 52($sp)		# get base address of local array or scalar
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a0, ($a0)		# expression is a VAR
	sw $a0, 132($sp)		# store LHS value
	li $a0, 1		# expression is a constant
	move $a2, $a0		# store RHS into $a2
	lw $a0, 132($sp)		# load stored LHS back into $a0
	add $a0, $a0, $a2		# perform addition
	sw $a0, 136($sp)		# store LHS into temp space created by A_ASSIGN
	li $t1, 0		# var is a scalar
	la $a0, 52($sp)		# get base address of local array or scalar
	add $a0, $a0, $t1		# add internal offset to base address
	lw $a1, 136($sp)		
	sw $a1, ($a0)		


	j _L10		# jump back to top of while
_L11:			# end of while
	li $a0, 0		# return has no specific value, set to 0
	lw $ra, ($sp)		# restore old environment RA
	lw $sp, 4($sp)		# return from function, store SP

	li $v0, 10		# exit from main, we are done
	syscall		# exit everything