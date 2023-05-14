a = int(input())
b = list(map(int, input().split()))

total = 0
toekn = max(b)
for i in range(a):
    b[i] = b[i] / toekn * 100

for i in range(a):
    total += b[i]
print(total / a)
