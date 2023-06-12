import sys
sys.setrecursionlimit(10**6)

def solve(in_start, in_end, post_start, post_end):
    if(in_start > in_end) or (post_start > post_end):
        return

    parents[post_end] = True
    print(post_order[post_end], end=" ")

    if in_start == in_end:
        return

    root_idx_inorder = in_position[post_order[post_end]]
    left_count = root_idx_inorder - in_start

    solve(in_start, root_idx_inorder - 1, post_start, post_start + left_count - 1)
    solve(root_idx_inorder + 1, in_end, post_start + left_count, post_end - 1)

n = int(sys.stdin.readline())
in_order = list(map(int, sys.stdin.readline().split()))
post_order = list(map(int, sys.stdin.readline().split()))

in_position = [0] * (n + 1)
parents = [False] * (n + 1)

for i in range(n):
    in_position[in_order[i]] = i

solve(0, n - 1, 0, n - 1)
