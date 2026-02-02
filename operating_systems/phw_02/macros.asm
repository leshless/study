# Read integer into register r
.macro read_int_(%r)
    # a = read_int()
    jal read_int

    # Save result to r
    mv %r, a0
.end_macro

# Read double into floating-point register f
.macro read_double_(%f)
    # a = read_double()
    jal read_double

    fmv.d %f, fa0
.end_macro

# Print string from address a
.macro print_string_(%a)
    # Move adress to a0
    la a0, %a

    # print_string(char* s)
    jal print_string

    # Release stack
    addi sp, sp, 4
.end_macro

# Print double from floating-point register f
.macro print_double_(%f)
    # Move argument to fa0
    fmv.d fa0, %f

    # print_double(double d)
    jal print_double
.end_macro

# Call evalueate with eps=0.001 and save result ot floating-point register %f2
.macro evaluate_(%r, %f1, %f2)
    # Move m to a0
    mv a0, %r

    # Move x to fa0
    fmv.d fa0, %f1
    # Load 0.001 to fa1
    li t0, 1
    fcvt.d.w ft0, t0
    li t1, 1000
    fcvt.d.w ft1, t1
    fdiv.d fa1, ft0, ft1

    # res = evaluate(double x, double eps, int m)
    jal evaluate

    # Move result to %f2
    fmv.d %f2, fa0
.end_macro


# Exit with code i
.macro exit_(%i)
    li a0, %i
    li a7, 4
    ecall
.end_macro

# Jump to label %l if integer register $r is less or equal to %i
.macro jump_less_int($r, %i, %l)
    # Load immediate %i to t0
    li t0, %i

    # Compare $r with %i
    blt $r, t0, %l
.end_macro

# Jump to label %l if absolute value of floating-point register $f is greater or equal to %i
.macro jump_greater_or_equal_double_abs($f, %i, %l)
    # Take absolute value of $f
    fmv.d ft0, $f
    fabs.d ft0, ft0

    # Load immediate %i to ft1
    li t0, %i
    fcvt.d.w ft1, t0

    # Compare |$f| with %i
    fge.d t1, ft0, ft1

    bne t1, zero, %l
.end_macro