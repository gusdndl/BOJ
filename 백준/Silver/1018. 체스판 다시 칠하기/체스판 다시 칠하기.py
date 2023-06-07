#BOJ 1018
import sys
input = sys.stdin.readline

def check(x, y):
    cnt = 0
    for i in range(x, x+8):
        for j in range(y, y+8):
            if (i+j) % 2 == 0:
                if board[i][j] != 'W':
                    cnt += 1
            else:
                if board[i][j] != 'B':
                    cnt += 1
    return min(cnt, 64-cnt)

n, m = map(int, input().split())
board = [list(input()) for _ in range(n)]
ans = 64

for i in range(n-7):
    for j in range(m-7):
        ans = min(ans, check(i, j))

print(ans)
