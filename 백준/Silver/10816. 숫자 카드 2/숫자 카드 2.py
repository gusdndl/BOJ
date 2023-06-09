from sys import stdin
from collections import Counter

_ = stdin.readline()
N = list(map(int, stdin.readline().split()))
_ = stdin.readline()
M = list(map(int, stdin.readline().split()))

counter = Counter(N)

for i in M:
    print(counter[i], end=' ')
