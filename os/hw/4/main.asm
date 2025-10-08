.include "macros.asm"

.data
newline: .string "\n"
argument_exception_message: .string "Bad argument\n"
precision_exception_message: .string "Bad precision\n"

.text
	
.globl main
main:
    read_float(fs0)
    read_float(fs1)

    check_not_negative(fs0)
    bnez a0, .argument_exception

    check_positive(fs1)
    bnez a0, .precision_exception

    sqrt_macro(fs0, fs1)
    fmv.s fs0, fa0

    print_float(fs0)
    print_string(newline)

    exit(0)

.argument_exception:
    print_string(argument_exception_message)
    exit(1)

.precision_exception:
    print_string(precision_exception_message)
    exit(1)
