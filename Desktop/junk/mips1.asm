.data
IntArray: .word 0x1,0x2,0x4,0xFF,0xFE,0xFA,0x7,0x9,0x8,0xFD # initial values of
							    # integer array
size: .word 10 # number of integers in IntArray
result: .space 4 # declare 4 bytes of storage to hold integer result (greatest integer)


.text

la $s0, IntArray	#load array
lw $v0, result		#load max
addi $t0, $zero, 0	#initialize counter
addi $t1, $zero, 10	#initialize loop count

lw $v0, 0($s0)		#load first element into result

loop:
add $t0, $t0, 1		#increment the counter
beq $t0, $t1, done	#if count = size, jump out of loop

sll $t2, $t0, 2		#adjust pointer offset
add $t2, $t2, $s0
lw $t3, 0($t2)		#grab the new array element
slt $t4, $v0, $t3	#check if it is greater than current max
beq $t4, $zero, loop	#if not, loop again

addi $v0, $t3, 0	#if so, update result
j loop			#loop again

#finish
done:

