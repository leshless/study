.include "macros.asm"

.data
length_prompt: .string "Enter length of the array: "
array_prompt: .string "Enter array: "
input_array_message: .string "Input array: "
result_array_message: .string "Result array: "
length_error_message: .string "Length of the array should be in range [0, 10]\n"

.text

.globl main
main:
    print_string_(length_prompt)
    read_int_(s0)

    jump_greater_(s0, 10, .length_error)
    jump_less_(s0, 0, .length_error)

    print_string_(array_prompt)
    read_array_(s0, s1)

    print_string_(input_array_message)
    print_array_(s1, s0)

    process_array_(s1, s0)

    print_string_(result_array_message)
    print_array_(s1, s0)

    exit_(0)

    .length_error:
        print_string_(length_error_message)
        exit_(1)