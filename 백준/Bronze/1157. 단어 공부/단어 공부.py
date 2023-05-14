string = input()

string = string.lower()
set_string = []
chk = []
for i in string:
    if i not in set_string:
        set_string.append(i)

num = 0
for i in set_string:
    if num < string.count(i):
        num = string.count(i)
    chk.append(string.count(i))


if chk.count(num) > 1:
    print("?")

else:
    print(set_string[chk.index(num)].upper())