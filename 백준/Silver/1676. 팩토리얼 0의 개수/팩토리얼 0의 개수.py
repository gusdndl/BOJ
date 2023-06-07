#BOJ 1676
import sys
input = sys.stdin.readline

n = int(input())
cnt = 0
for i in range(1, n+1):
    if i % 5 == 0:
        cnt += 1
    if i % 25 == 0:
        cnt += 1
    if i % 125 == 0:
        cnt += 1

print(cnt)