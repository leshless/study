
s = input()
res = ""
while s:
    f = s[0]
    li = s.rfind(f)
    res += s[li+1:]
    s = s[1:li]

print(res)