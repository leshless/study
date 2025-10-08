.macro fact(%n)
    mv a0, %n
    jal ra, factorial
.end_macro

.text:

.globl main
main:
    li s0, 1 # current n value
    li s1, 1 # previous fact(n) value

    loop:
        fact(s0)
        mv s2, a0 

        li a7, 1
        mv a0, s0
        ecall

        li a7, 11
        li a0, ' '
        ecall

        li a7, 1
        mv a0, s2
        ecall

        li a7, 11
        li a0, '\n'
        ecall

        # if this is false, there is an overflow
        div s3, s2, s0
        bne s3, s1 loop_end

        mv s1, s2
        addi s0, s0, 1
        
        j loop
    
    loop_end:

    addi s0, s0, -1

    li a7, 1
    mv a0, s0
    ecall

    li a7, 11
    li a0, '\n'
    ecall

    li a7, 10
    li a0, 0
    ecall

factorial:
    addi sp, sp, -8
    sw ra, 4(sp)
    sw a0, 0(sp)

    # if n == 1; return 1
    li t0, 1
    beq a0, t0, base

    addi a0, a0, -1
    jal ra, factorial

    lw t0, 0(sp)
    mul a0, a0, t0

    j end

    base:
    li a0, 1

    end:
    lw ra, 4(sp)
    addi sp, sp, 8
    ret



