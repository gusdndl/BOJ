hour, minute = map(int, input().split())

if minute < 45:
    if hour == 0:
        hour = 23
    else:
        hour -= 1
    print(hour, minute + 15)
else:
    print(hour, minute - 45)