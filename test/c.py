import re 
import math

expr1 = re.compile(r"(\[|\()(.*), (.*)(\]|\))")
s = input()
m = expr1.match(s)

fl = (m.group(1) == '[')
fr = (m.group(4) == ']')
l = eval(m.group(2))
r = eval(m.group(3))

if (not fl) and l == math.ceil(l):
    l += 1
else:
    l = math.ceil(l)

if (not fr) and r == math.floor(r):
    r -= 1
else:
    r = math.floor(r)

print(max(r - l + 1, 0))
