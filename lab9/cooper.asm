# MIPS CODE GENERATE by Compilers class

.data

_L0: .asciiz	 "\n"
.align 2
.text


.globl main


addNums:				# function definition
	move $a1, $sp		# Activation Record carve out copy SP
	subi $a1 $a1 20		# Activation Record carve out copy size of function
	sw $ra , ($a1)		# Store Return address 
	sw $sp 4($a1)		# Store the old Stack pointer
	move $sp, $a1		# Make SP the current activation record


	sw $t0 8($sp)		# Paramater store start of function
	sw $t1 12($sp)		# Paramater store start of function


	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 8		# VAR local stack pointer plus offset
	lw $a0, ($a0)		# Expression is a VAR
	sw $a0, 16($sp)		# expression store LHS temporarily
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 12		# VAR local stack pointer plus offset
	lw $a0, ($a0)		# Expression is a VAR
	move $a1, $a0		# #right hand side needs to be a1
	lw $a0, 16($sp)		# expression restore LHS from memory
	add $a0, $a0, $a1		# #EXPR ADD
	lw $ra ($sp)		# restore old environment RA
	lw $sp 4($sp)		# Return from function store SP

	jr $ra			# return to the caller
	li $a0, 0		# RETURN has no specified value set to 0
	lw $ra ($sp)		# restore old environment RA
	lw $sp 4($sp)		# Return from function store SP

	jr $ra			# return to the caller

			# END OF FUNCTION



main:				# function definition
	move $a1, $sp		# Activation Record carve out copy SP
	subi $a1 $a1 40		# Activation Record carve out copy size of function
	sw $ra , ($a1)		# Store Return address 
	sw $sp 4($a1)		# Store the old Stack pointer
	move $sp, $a1		# Make SP the current activation record




	li $a0, 5		# expression is a constant
	sw $a0 20($sp)		# Assign store RHS temporarily
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 12		# VAR local stack pointer plus offset
	lw $a1 20($sp)		# Assign get RHS temporarily
	sw $a1 ($a0)		# Assign place RHS into memory
	li $a0, 4		# expression is a constant
	sw $a0 24($sp)		# Assign store RHS temporarily
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 16		# VAR local stack pointer plus offset
	lw $a1 24($sp)		# Assign get RHS temporarily
	sw $a1 ($a0)		# Assign place RHS into memory
			# Setting Up Function Call
			# evaluate  Function Parameters
	li $a0, 5		# expression is a constant
	sw $a0, 32($sp)		# Store call Arg temporarily

	li $a0, 4		# expression is a constant
	sw $a0, 28($sp)		# Store call Arg temporarily

			# place   Parameters into T registers
	lw $a0, 32($sp)		# pull out stored  Arg 
	move $t0, $a0		# move arg in temp 
	lw $a0, 28($sp)		# pull out stored  Arg 
	move $t1, $a0		# move arg in temp 

	jal addNums			# Call the function


	sw $a0 36($sp)		# Assign store RHS temporarily
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 8		# VAR local stack pointer plus offset
	lw $a1 36($sp)		# Assign get RHS temporarily
	sw $a1 ($a0)		# Assign place RHS into memory
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 8		# VAR local stack pointer plus offset
	lw $a0, ($a0)		# Expression is a VAR
	li $v0, 1		# About to print a number
	syscall			# call write number


	la $a0, _L0		# The string address
	li $v0, 4		# About to print a string
	syscall			# call write string


	li $a0, 0		# RETURN has no specified value set to 0
	lw $ra ($sp)		# restore old environment RA
	lw $sp 4($sp)		# Return from function store SP

	li $v0, 10		# Exit from Main we are done
	syscall			# EXIT everything

			# END OF FUNCTION



