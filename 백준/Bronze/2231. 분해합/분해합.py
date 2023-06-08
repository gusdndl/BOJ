N = int(input())

def sum_digit(number):
    return sum(int(i) for i in str(number))

for i in range(1, N+1):
    if i + sum_digit(i) == N:
        print(i)
        break
else:
    print(0)
