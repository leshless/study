# Read float into r
.macro read_float(%r)
    li a7, 6
    ecall
    fmv.s %r, fa0
.end_macro

# Print float from r
.macro print_float(%r)
    fmv.s fa0, %r
    li a7, 2
    ecall
.end_macro

# Print string from a
.macro print_string(%a)
    la a0, %a
    li a7, 4
    ecall
.end_macro

.macro print_int(%r)
    mv a0, %r
    li a7, 1
    ecall
.end_macro

# Exit with code i
.macro exit(%i)
    li a0, %i
    li a7, 4
    ecall
.end_macro

# Checks that float number is >= 0
# Sets a0 to 0 if true
.macro check_not_negative(%r)
    fclass.s t0, %r
    li t1, 143

    and a0, t0, t1
.end_macro

# Checks that float number is > 0
# Sets a0 to 0 if true
.macro check_positive(%r)
    fclass.s t0, %r
    li t1, 159

    and a0, t0, t1
.end_macro

# Evaluates square root of r1, with precision r2
# Result in fa0
.macro sqrt_macro(%r1, %r2)
    fmv.s fa0, %r1
    fmv.s fa1, %r2

    jal sqrt
.end_macro