.text

.globl print_string
print_string:
    # Prolog (push ra to stack)
    addi sp, sp, -4
    sw ra, 0(sp)    

    # Call PrintString
    lw a0, 4(sp)
    li a7, 4
    ecall

    # Epilog (pop ra from stack)
    lw ra, 0(sp)
    addi sp, sp, 4
    ret

.globl print_int
print_int:
    # Prolog (push ra to stack)
    addi sp, sp, -4
    sw ra, 0(sp)    

    # Call PrintInt
    lw a0, 4(sp)
    li a7, 1
    ecall

    # Epilog (pop ra from stack)
    lw ra, 0(sp)
    addi sp, sp, 4
    ret

.globl read_int
read_int:
    # Prolog (push ra to stack)
    addi sp, sp, -4
    sw ra, 0(sp)    

    # Call ReadInt
    li a7, 5
    ecall

    # Epilog (pop ra from stack)
    lw ra, 0(sp)
    addi sp, sp, 4
    ret