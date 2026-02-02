# Print string from address a
.macro print_string_(%a)
    # Push argument to stack
    la t0, %a
    addi sp, sp, -4
    sw t0, 0(sp)

    # print_string(s)
    jal print_string

    # Release stack
    addi sp, sp, 4
.end_macro

# Print integer in register r
.macro print_int_(%r)
    # Push argument to stack
    addi sp, sp, -4
    sw %r, 0(sp)

    # print_int(int a)
    jal print_int

    # Release stack
    addi sp, sp, 4
.end_macro

# Read integer into register r
.macro read_int_(%r)
    # a = read_int()
    jal read_int

    # Save result to r
    mv %r, a0
.end_macro

# Read array of length r1 and place address to it in r2
.macro read_array_(%r1, %r2)
    # Push argument to stack
    addi sp, sp, -4
    sw %r1, 0(sp)

    # *arr = read_array(n)
    jal read_array

    # Release stack
    addi sp, sp, 4

    # Save pointer to r2
    mv %r2, a0
.end_macro

# Print array pointed at by r1 with size r2
.macro print_array_(%r1, %r2)
    # Push argument to stack
    addi sp, sp, -8
    sw %r1, 4(sp)
    sw %r2, 0(sp)

    # print_array(*arr, n)
    jal print_array

    # Release stack
    addi sp, sp, 8
.end_macro

# Process array pointed at by r1 with size r2
# The resulting array pointer and size are stored back in r1 and r2
.macro process_array_(%r1, %r2)
    # Push argument to stack
    addi sp, sp, -8
    sw %r1, 4(sp)
    sw %r2, 0(sp)

    # *arr, n = process_array(*arr, n)
    jal process_array

    # Release stack
    addi sp, sp, 8

    mv %r1, a0
    mv %r2, a1
.end_macro

# Exit with code i
.macro exit_(%i)
    li a0, %i
    li a7, 4
    ecall
.end_macro

# Jump to l if r > i
.macro jump_greater_(%r, %i, %l)
    li t0, %i
    bgt %r, t0, %l
.end_macro

# Jump to l if r < i
.macro jump_less_(%r, %i, %l)
    li t0, %i
    blt %r, t0, %l
.end_macro