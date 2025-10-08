import math
import subprocess
import pytest


RARS_JAR = "/home/leshless/.rars.jar"
RARS_SOURCE_FILES = ["main.asm", "sqrt.asm"]
ARGUMENT_EXCEPTION_MESSAGE = "Bad argument"
PRECISION_EXCEPTION_MESSAGE = "Bad precision"


class ArgumentException(Exception):
    pass


class PrecisionException(Exception):
    pass


def run_rars(x, eps):
    cmd = ["java", "-jar", RARS_JAR] + RARS_SOURCE_FILES
    inp = f"{x}\n{eps}\n"

    result = subprocess.run(cmd, input=inp, capture_output=True, text=True)
    for line in result.stdout.split("\n"):
        if ARGUMENT_EXCEPTION_MESSAGE in line:
            raise ArgumentException
        if PRECISION_EXCEPTION_MESSAGE in line:
            raise PrecisionException

        try:
            result = float(line)
            return result
        except ValueError:
            continue

    raise ValueError


class TestSqrt:
    @pytest.mark.parametrize(
        "x,eps",
        [
            (0.0, 1e-6),
            (1.0, 1e-6),
            (2.0, 1e-6),
            (2.0, 1e-4),
            (10.0, 1e-6),
            (12345.678, 1e-5),
            (1e-8, 1e-8),
            (1e8, 1e-4),
            (4.0, 1e-6),          
            (9.0, 1e-6),          
            (0.25, 1e-7),         
            (0.01, 1e-8),         
            (1e-12, 1e-12),       
            (1e-6, 1e-8),         
            (1e6, 1e-3),          
            (1e12, 1e-2),         
            (3.14159265, 1e-7),   
            (2.718281828, 1e-7),  
            (123456789.0, 1e-2),  
            (5.0, 5e-1),          
            (50.0, 1e-5),         
            (7.0, 1e-6),          
        ],
    )
    def test_happy_path(self, x, eps):
        result = run_rars(x, eps)
        assert math.isclose(result, math.sqrt(x), abs_tol=eps)

    @pytest.mark.parametrize(
        "x,eps",
        [
            (-0.1, 1e-6),
            (-1e-12, 1e-6),       
            (-1.0, 1e-6),         
            (-123.456, 1e-6),     
        ],
    )
    def test_argument_exception(self, x, eps):
        with pytest.raises(ArgumentException):
            result = run_rars(x, eps)

    @pytest.mark.parametrize(
        "x,eps",
        [
            (0.1, -1e-6),
            (0.1, 0.0),           
            (0.1, -1e-12),        
            (0.1, 1e308),         
        ],
    )
    def test_precision_exception(self, x, eps):
        with pytest.raises(PrecisionException):
            result = run_rars(x, eps)