import sys

def ccw(p1, p2, p3):
    return (p2[0] - p1[0]) * (p3[1] - p1[1]) - (p2[1] - p1[1]) * (p3[0] - p1[0])

def is_intersect(p1, p2, p3, p4):
    f1 = max(min(p1[0], p2[0]), min(p3[0], p4[0]))
    f2 = min(max(p1[0], p2[0]), max(p3[0], p4[0]))
    f3 = max(min(p1[1], p2[1]), min(p3[1], p4[1]))
    f4 = min(max(p1[1], p2[1]), max(p3[1], p4[1]))
    a = ccw(p1, p2, p3) * ccw(p1, p2, p4)
    b = ccw(p3, p4, p1) * ccw(p3, p4, p2)
    if a == 0 and b == 0:
        if f1 > f2 or f3 > f4:
            return False
    return a <= 0 and b <= 0

def find(a):
    if a == parent[a]:
        return a
    parent[a] = find(parent[a])
    return parent[a]

def union(a, b):
    a = find(a)
    b = find(b)
    if a != b:
        parent[b] = a
        group_size[a] += group_size[b]

N = int(sys.stdin.readline())
parent = [i for i in range(N)]
group_size = [1 for _ in range(N)]
lines = []
line_data = []

for i in range(N):
    x1, y1, x2, y2 = map(int, sys.stdin.readline().split())
    lines.append((x1, y1, x2, y2))
    line_data.append((min(x1, x2), i))
    line_data.append((max(x1, x2), i))

line_data.sort()

connected = set()
for _, idx in line_data:
    for con in list(connected):
        if max(lines[con][0], lines[con][2]) < min(lines[idx][0], lines[idx][2]):
            connected.remove(con)
        elif is_intersect((lines[idx][0], lines[idx][1]), (lines[idx][2], lines[idx][3]), 
                          (lines[con][0], lines[con][1]), (lines[con][2], lines[con][3])):
            union(idx, con)
    connected.add(idx)

num_groups = set()
max_size = 0
for i in range(N):
    num_groups.add(find(i))
    max_size = max(max_size, group_size[find(i)])

print(len(num_groups))
print(max_size)
