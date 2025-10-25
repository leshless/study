.text

.globl evaluate
evaluate:
    # Prolog (push ra to stack)
    addi sp, sp, -4
    sw ra, 0(sp)

    # Store x in ft0
    fmv.d ft0, fa0

    # Load eps ft1
    fmv.d ft1, fa1

    # Load 1.0 to ft2
    li t0, 1
    fcvt.d.w ft2, t0

    # Load 1.0 to ft3
    li t0, 1
    fcvt.d.w ft3, t0

    # Load m to t0
    mv t0, a0

    # Load 1 to t1
    li t1, 1

    .evaluate_loop:
        # Evaluate another term a_i = a_i-1 * (m - i + 1) * x / i
        mv t2, t0
        sub t2, t2, t1
        addi t2, t2, 1
        fcvt.d.w ft4, t2
        fmul.d ft3, ft3, ft4

        fcvt.d.w ft4, t1
        fdiv.d ft3, ft3, ft4

        fmul.d ft3, ft3, ft0

        # Add term to result
        fadd.d ft2, ft2, ft3

        # Increment i
        addi t1, t1, 1

        # Break if i > m
        bgt t1, t0, .end_evaluate_loop

        # Break if |a_i| < eps * res
        fabs.d ft4, ft3
        fmul.d ft5, ft1, ft2
        flt.d t2, ft4, ft5
        bnez t2, .end_evaluate_loop

        j .evaluate_loop
    .end_evaluate_loop:


    # Return result
    fmv.d fa0, ft2

    # Epilog (pop ra from stack)
    lw ra, 0(sp)
    addi sp, sp, 4
    ret