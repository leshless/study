import subprocess
import pytest
import re

RARS_JAR = "/home/leshless/.rars.jar"
RARS_SOURCE_FILES = ["main.asm", "array.asm", "io.asm"]
ARRAY_LENGTH_ERROR_MESSAGE = "Length of the array should be in range [0, 10]"

input_array_regex = re.compile(r".*Input array: (.*)")
result_array_regex = re.compile(r".*Result array: (.*)")

class ArrayLengthError(Exception):
    pass

def run_rars(n, numbers):
    cmd = ["java", "-jar", RARS_JAR] + RARS_SOURCE_FILES
    inp = f"{n}\n{"\n".join(list(map(str, numbers)))}\n"

    result = subprocess.run(cmd, input=inp, capture_output=True, text=True)

    input_numbers = None
    result_numbers = None

    for line in result.stdout.split("\n"):
        if ARRAY_LENGTH_ERROR_MESSAGE in line:
            raise ArrayLengthError

        match = input_array_regex.match(line) 
        if match != None:
            input_numbers = list(map(int, match.group(1).split()))

        match = result_array_regex.match(line) 
        if match != None:
            result_numbers = list(map(int, match.group(1).split()))
    
    return input_numbers, result_numbers

def get_result_numbers(numbers):
    numbers = list(reversed(numbers))
    
    j = None
    for i in range(len(numbers)):
        if numbers[i] > 0:
            j = i
            break

    if j != None:
        del numbers[j]
    
    return numbers

class TestSqrt:
    @pytest.mark.parametrize(
        "numbers",
        [
            [],
            [1],
            [0],
            [-1],
            [1, 2, 3],
            [3, 2, 1],
            [0, 0, 0],
            [-5, -4, -3],
            [5, 0, -4, 6, 8],
            [-1, 2, -3, 4, -5],
            [10, 9, -4, 6, 8],
            [1, 1, 1, 1],
            [-1, -1, -1, -1],
            [2, -2, 2, -2, 2],
            [1, 0, 2, 0, 3],
            [1000000, -1, 1000000],
            [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], 
            [10, -9, 8, -7, 6, -5, 4, -3, 2, -1], 
            [1, -2, 3, -4, 5],
            [-2, -1, 0, 1, 2],
        ],
    )
    def test_happy_path(self, numbers):
        input_numbers, result_numbers = run_rars(len(numbers), numbers)

        assert numbers == input_numbers
        assert get_result_numbers(numbers) == result_numbers

    @pytest.mark.parametrize(
        "n,numbers",
        [
            (-1, []),
            (-1000, []),
            (11, [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]),
            (100, [1 for _ in range(100)]),
        ],
    )
    def test_bad_length(self, n, numbers):
        with pytest.raises(ArrayLengthError):
            input_numbers, result_numbers = run_rars(n, numbers)