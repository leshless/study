import subprocess
import pytest
import re

EPS = 0.001

RARS_JAR = "/home/leshless/.rars.jar"
RARS_SOURCE_FILES = ["main.asm", "evaluate.asm", "io.asm"]
X_ERROR_MESSAGE = "Value of x should be in range (-1, 1)"
M_ERROR_MESSAGE = "Value of m should be non-negative"

result_regex = re.compile(r".*Result: (.*)")

class XValueError(Exception):
    pass

class MValueError(Exception):
    pass

def run_rars(x, m):
    cmd = ["java", "-jar", RARS_JAR] + RARS_SOURCE_FILES
    inp = f"{x}\n{m}\n"

    result = subprocess.run(cmd, input=inp, capture_output=True, text=True)

    res = None

    for line in result.stdout.split("\n"):
        if X_ERROR_MESSAGE in line:
            raise XValueError

        if M_ERROR_MESSAGE in line:
            raise MValueError

        match = result_regex.match(line) 
        if match != None:
            res = float(match.group(1))

    return res

def get_expected_res(x, m):
    return (1 + x)**m

class TestSqrt:
    @pytest.mark.parametrize(
        "x,m",
        [
            (0.1, 100),
            (0.01, 50),
            (0.5, 10),
            (0.001, 1000),
            (0.0, 100),
            (-0.1, 100),
            (0.1, 0),
            (0.1, 1),
            (0.05, 2),
            (0.01, 1000),
            (-0.01, 100),
            (0.2, 50),
            (-0.2, 30),
            (0.001, 0),
            (0.0, 0),
        ],
    )
    def test_happy_path(self, x, m):
        res = run_rars(x, m)
        expected_res = get_expected_res(x, m)
 
        assert abs(res - expected_res) < expected_res * EPS

    @pytest.mark.parametrize(
        "x,m",
        [
            (1.0, 100),
            (-1.0, 100),
            (100000.0, 100),
            (-100000.0, 100),
        ],
    )
    def test_bad_x_value(self, x, m):
        with pytest.raises(XValueError):
            run_rars(x, m)

    @pytest.mark.parametrize(
        "x,m",
        [
            (0.2, -50),
            (-0.2, -30),
            (0.001, -1),
        ],
    )
    def test_bad_m_value(self, x, m):
        with pytest.raises(MValueError):
            run_rars(x, m)