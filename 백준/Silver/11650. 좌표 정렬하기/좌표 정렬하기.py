n = int(input())
coords = []

for _ in range(n):
    x, y = map(int, input().split())
    coords.append((x, y))

coords.sort()

for coord in coords:
    print(coord[0], coord[1])
