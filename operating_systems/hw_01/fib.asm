.text:
main:
    mv t0, zero # (pseudo) mv rd, rs1 -> addi rd, rs1, 0
    li t1, 1 # (pseudo) li rd, imm -> addi rd, zero, imm

    li a7, 5 # (pseudo) li rd, imm -> addi rd, zero, imm
    ecall # ReadInt syscall
    mv t3, a0 # (pseudo) mv rd, rs1 -> addi rd, rs1, 0
    
fib:
    beqz t3, finish  # (pseudo) beqz rs1, addr -> beq rs1, zero, addr
    add t2, t1, t0 # add rd, rs1, rs2
    mv t0, t1 # (pseudo) mv rd, rs1 -> addi rd, rs1, 0
    mv t1, t2 # (pseudo) mv rd, rs1 -> addi rd, rs1, 0
    addi t3, t3, -1 # addi rd, rs1, imm
    j fib # (pseudo) j addr -> jal zero, addr 

finish:
    li a7, 1 # (pseudo) li rd, imm -> addi rd, zero, imm
    mv a0, t0 # (pseudo) mv rd, rs1 -> addi rd, rs1, 0
    ecall # PrintInt syscall