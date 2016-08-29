.data
g: .word 4 # initial value of variable g
h: .word 5 # initial value of variable h
i: .word 1 # initial value of variable i
j: .word 2 # initial value of variable j
f: .space 4 # declare 4 bytes of storage to hold integer result

 
   .text
   
lw $a0, g		#load all variables
lw $a1, h
lw $a2, i
lw $a3, j
addi $s0, $zero, 0

add $t0, $a0, $a1	#add G and H
move $s0, $t0		#store in F
add $t0, $a2, $a3	#add I and J
sub $s0, $s0, $t0	#substract from F

move $v0, $s0		#move F to result