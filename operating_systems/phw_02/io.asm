.text

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

.globl read_double
read_double:
    # Prolog (push ra to stack)
    addi sp, sp, -4
    sw ra, 0(sp)    

    # Call ReadDouble
    li a7, 7
    ecall

    # Epilog (pop ra from stack)
    lw ra, 0(sp)
    addi sp, sp, 4
    ret

.globl print_string
print_string:
    # Prolog (push ra to stack)
    addi sp, sp, -4
    sw ra, 0(sp)  

    # Call PrintString
    li a7, 4
    ecall

    # Epilog (pop ra from stack)
    lw ra, 0(sp)
    addi sp, sp, 4
    ret

.globl print_double
print_double:
    # Prolog (push ra to stack)
    addi sp, sp, -4
    sw ra, 0(sp)  

    # Call PrintDouble
    li a7, 3
    ecall

    # Epilog (pop ra from stack)
    lw ra, 0(sp)
    addi sp, sp, 4
    ret