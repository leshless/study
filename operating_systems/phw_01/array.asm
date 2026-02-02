.include "macros.asm"

.data
    nl: .string "\n"
    spc: .string " "

.text
.globl read_array
read_array:
    # Prolog (push ra to stack)
    addi sp, sp, -12
    sw ra, 8(sp)

    # Call malloc(4*n)
    li a7, 9
    lw a0, 12(sp)
    li t0, 4
    mul a0, a0, t0
    ecall

    # Save array address to stack 
    sw a0, 4(sp)

    # Use counter
    sw zero, 0(sp)

    .loop:
        # Break if i == n
        lw t0, 0(sp)
        lw t1, 12(sp)
        beq t0, t1, .break

        read_int_(t0)

        # Evaluate *nums[i]
        lw t1, 0(sp)
        li t2, 4
        mul t1, t1, t2
        lw t2, 4(sp)
        add t1, t1, t2

        # nums[i] = current
        sw a0, 0(t1)

        # i++   
        lw t0, 0(sp)
        addi t0, t0, 1
        sw t0, 0(sp)

        j .loop

    .break:


    # t1 is return value
    lw a0, 4(sp)

    # Epilog (pop ra from stack)
    lw ra, 8(sp)
    addi sp, sp, 12
    ret

.globl print_array
print_array:
    # Prolog (push ra to stack)
    addi sp, sp, -8
    sw ra, 4(sp)
    
    # Use counter
    sw zero, 0(sp)

    .loop1:
        # Break if i == n
        lw t0, 0(sp)
        lw t1, 8(sp)
        beq t0, t1, .break1

        # Evaluate *nums[i]
        lw t1, 0(sp)
        li t2, 4
        mul t1, t1, t2
        lw t2, 12(sp)
        add t1, t1, t2

        # current = nums[i]
        lw t0, 0(t1)

        print_int_(t0)
        print_string_(spc)

        # i++   
        lw t0, 0(sp)
        addi t0, t0, 1
        sw t0, 0(sp)

        j .loop1

    .break1:

    print_string_(nl)

    # Epilog (pop ra from stack)
    lw ra, 4(sp)
    addi sp, sp, 8
    ret


.globl process_array
process_array:
    # Prolog (push ra to stack)
    addi sp, sp, -20
    sw ra, 16(sp)

    # Stack should look like this:
    #     +0    +4    +8    +12 +16  +20  +24
    # |removed|new_i|old_i|*new|ret|old_n|*old|
    # ^sp

    # Break if n == 0
    lw t0, 20(sp)
    beqz t0, .end2

    # Call malloc(4*n) for new array
    li a7, 9
    lw a0, 20(sp)
    li t0, 4
    mul a0, a0, t0
    ecall

    # Save pointer to new array
    sw a0, 12(sp)
    
    # Use index of old array
    lw t0, 20(sp)
    addi t0, t0, -1
    sw t0, 8(sp)

    # Use index of new array
    sw zero, 4(sp)

    # Use "removed" flag
    sw zero, 0(sp)

    # Stack should look like this:
    #     +0    +4    +8    +12 +16  +20  +24
    # |removed|new_i|old_i|*new|ret|old_n|*old|
    # ^sp

    .loop2:
        # Break if old_i == -1
        lw t0, 8(sp)
        bltz t0, .break2

        # Evaluate *old[old_i]
        lw t1, 8(sp)
        li t2, 4
        mul t1, t1, t2
        lw t2, 24(sp)
        add t1, t1, t2

        # Current = old[old_i]
        lw t0, 0(t1)

        # Add if old[old_i] <= 0
        blez t0, .add
        
        # Add if already removed one
        lw t1, 0(sp)
        bnez t1 .add

        # Ignore in other case
        .ignore:
            # Assign removed to 1
            mv t0, zero
            addi t0, t0, 1
            sw t0, 0(sp)
            
            j .endif
        .add:
            # Evaluate *new[new_i]
            lw t1, 4(sp)
            li t2, 4
            mul t1, t1, t2
            lw t2, 12(sp)
            add t1, t1, t2

            # new[new_i] = current
            sw t0, 0(t1)

            # new_i++
            lw t0, 4(sp)
            addi t0, t0, 1
            sw t0, 4(sp)

        .endif:

        # old_i-- 
        lw t0, 8(sp)
        addi t0, t0, -1
        sw t0, 8(sp)

        j .loop2

    .break2:

    # Return *new
    lw a0, 12(sp)
    # Return new_i
    lw a1, 4(sp)

    # Epilog (pop ra from stack)
    .end2:
        lw ra, 16(sp)
        addi sp, sp, 20
        ret