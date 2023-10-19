import sys
from collections import defaultdict
sys.setrecursionlimit(1000001)

A = defaultdict(list)
vis = [False] * 1000001

# 자신을 포함한 subtree에서, 내가 켜졌을 때의 최소 점등 등대 개수와
# 내가 꺼졌을 때의 최소 점등 등대 개수를 반환합니다.
def dfs(u):
    vis[u] = True
    if not A[u]:
        # u가 leaf라면 내가 켜졌을 떄의 최소 점등 등대 개수는 1
        # 내가 꺼졌을 때의 최소 점등 등대 개수는 0
        return 1, 0
    
    # u가 leaf가 아니라면
    on, off = 1, 0
    for v in [v for v in A[u] if not vis[v]]:
        # 내가 켜졌다면 child들은 켜지든 꺼지든 상관 없습니다. -> 킨 것과 끈 것중 최소값을 취함
        # 내가 꺼졌다면 child들은 무조건 켜져야 합니다.
        # 이 점을 생각해서 leaf들의 정보를 취합, 정리합니다.
        child_on, child_off = dfs(v)
        on += min(child_on, child_off)
        off += child_on
    return on, off

def solution(n, lighthouse):
    for u, v in lighthouse:
        A[u].append(v)
        A[v].append(u)
        
    on, off = dfs(1)
    return min(on, off)