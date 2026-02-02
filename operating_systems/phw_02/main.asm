.include "macros.asm"

.data
x_prompt: .string "Enter x: "
m_prompt: .string "Enter m: "
result_message: .string "Result: "
x_error_message: .string "Value of x should be in range (-1, 1)"
m_error_message: .string "Value of m should be non-negative"
nl: .string "\n"

.text

.globl main
main:
    print_string_(x_prompt)
    read_double_(fs0)
    jump_greater_or_equal_double_abs(fs0, 1, .x_error)

    print_string_(m_prompt)
    read_int_(s0)
    jump_less_int(s0, 0, .m_error)

    evaluate_(s0, fs0, fs1)

    print_string_(result_message)
    print_double_(fs1)
    print_string_(nl)

    exit_(0)

    .x_error:
        print_string_(x_error_message)
        print_string_(nl)
        exit_(1)
    
    .m_error:
        print_string_(m_error_message)
        print_string_(nl)
        exit_(1)