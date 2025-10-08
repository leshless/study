.include "macros.asm"

.text

.globl sqrt
sqrt:
    # ft0: n
    fmv.s ft0, fa0

    # ft1: x_i
    li t0, 1
    fcvt.s.w ft1, t0

    # ft3: 2
    li t0, 2
    fcvt.s.w ft3, t0

    # ft4: p
    fmv.s ft4, fa1

    fclass.s t0, ft0
    andi t0, t0, 24 # (1 << 4) | (1 << 3)
    bnez t0, .is_zero

.cycle:
    # x_i+1 = ((n / x_i) + x_i) / 2
    fmv.s ft2, ft0
    fdiv.s ft2, ft2, ft1
    fadd.s ft2, ft2, ft1
    fdiv.s ft2, ft2, ft3


    # |x_i - x_i+1| V p
    fsub.s ft5, ft1, ft2
    fabs.s ft5, ft5


    fmv.s ft1, ft2

    fle.s t0, ft4, ft5
    bnez t0, .cycle

.end:
    fmv.s fa0, ft1
    ret

.is_zero:
    fmv.w.x fa0, zero
    ret