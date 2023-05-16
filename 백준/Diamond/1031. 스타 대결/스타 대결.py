import sys
from collections import deque

n, m = map(int, sys.stdin.readline().split())
col = list(map(int, sys.stdin.readline().split()))
row = list(map(int, sys.stdin.readline().split()))

graph = [[0] * (n + m + 2) for _ in range(n + m + 2)]

for i in range(n):
    graph[0][i + 1] = col[i]

for j in range(m):
    graph[n + j + 1][-1] = row[j]

for i in range(1, n + 1):
    for j in range(n + 1, n + m + 1):
        graph[i][j] = 1

ans = 0
while True:
    prev = [-1] * (n + m + 2)
    queue = deque([0])
    while queue:
        cur = queue.popleft()
        
        if cur == 0:
            for nxt in range(n, 0, -1):
                if (prev[nxt] == -1) and graph[cur][nxt]:
                    prev[nxt] = cur
                    queue.append(nxt)
        
        elif cur <= n:
            for nxt in range(n + m, n, -1):
                if (prev[nxt] == -1) and graph[cur][nxt]:
                    prev[nxt] = cur
                    queue.append(nxt)
        
        else:
            if graph[cur][-1]:
                prev[-1] = cur
                break
            
            for nxt in range(n, 0, -1):
                if (prev[nxt] == -1) and graph[cur][nxt]:
                    prev[nxt] = cur
                    queue.append(nxt)

        if prev[-1] != -1:
            break
    
    if prev[-1] == -1:
        break

    ans += 1
    nxt = -1
    while nxt:
        cur = prev[nxt]
        graph[cur][nxt] -= 1
        graph[nxt][cur] += 1
        nxt = cur

if ans == sum(row):
    for i in range(1, n + 1):
        for j in range(n + 1, n + m + 1):
            if graph[i][j] == 0:
                prev = [-1] * (n + m + 2)
                
                queue = deque()
                for nxt in range(n + m, j, -1):
                    if graph[i][nxt]:
                        prev[nxt] = i
                        queue.append(nxt)
                
                while queue:
                    cur = queue.popleft()

                    if 1 <= cur <= n:
                        for nxt in range(n + m, n, -1):
                            if (prev[nxt] == -1) and graph[cur][nxt]:
                                prev[nxt] = cur
                                queue.append(nxt)
                    
                    else:
                        for nxt in range(n, i, -1):
                            if (prev[nxt] == -1) and graph[cur][nxt]:
                                prev[nxt] = cur
                                queue.append(nxt)
                    
                    if prev[j] != -1:
                        break
                
                if prev[j] != -1:
                    graph[i][j] += 1
                    graph[j][i] -= 1
                    nxt = j
                    while True:
                        cur = prev[nxt]
                        graph[cur][nxt] -= 1
                        graph[nxt][cur] += 1
                        nxt = cur
                        if nxt == i:
                            break

    for i in range(1, n + 1):
        for j in range(n + 1, n + m + 1):
            print(graph[j][i], end='')
        print()
else:
    print(-1)