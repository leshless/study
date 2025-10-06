.data
division_by_zero_error: .string "Division by zero\n"

# a = c*b + d
.text
# read a
li a7, 5
ecall
mv t0, a0

# read b
li a7, 5
ecall
mv t1, a0

# exit if b == 0
beqz t1, error

# t2 := (a < 0)
bge t0, zero, a_pos
neg t0, t0
li t2, 1
a_pos:
	
# t3 := (b < 0)
bge t1, zero, b_pos
neg t1, t1
li t3, 1
b_pos:

# t4 := t2 ^ t3
xor t4, t2, t3

# c := 0
li t5, 0

loop:
	# break if a < b
	blt t0, t1, loop_end
	# a -= b
	sub t0, t0, t1
	# c++
	addi t5, t5, 1
	
	j loop

loop_end:

# if t4, c = -c
beqz t4, c_pos
neg t5, t5
c_pos:

# if t3, d = -d
beqz t3, d_pos
neg t0, t0
d_pos:

# print(c)
li a7, 1
mv a0, t5
ecall

# print(' ')
li a7, 11
li a0, ' '
ecall

# print(d)
li a7, 1
mv a0, t0
ecall

# print('\n')
li a7, 11
li a0, '\n'
ecall

end:
	# exit(1)
	li a7, 10
	li a0, 0
	ecall

error:
	# print(division_by_zero_error)
	li a7, 4
	la a0, division_by_zero_error
	ecall

	# exit(1)
	li a7, 10
	li a0, 1
	ecall