import sys
input = sys.stdin.readline
MIN_NUM = sys.maxsize


def dist_point(a, b):
    return (a[0]-b[0])**2 + (a[1]-b[1])**2


def brute(start, end):
    tmp = MIN_NUM
    for i in range(start, end+1):
        for j in range(i+1, end+1):
            tmp = min(tmp, dist_point(point_list[i], point_list[j]))
    return tmp


def area_point(avg, start, end,  min_both):
    tmp = min_both
    lcnt = 0
    rcnt = 0
    while avg-lcnt-1 >= start and min_both > (point_list[avg][0] - point_list[avg-lcnt-1][0])**2:
        lcnt += 1
    while avg + rcnt+1 <= end and min_both > (point_list[avg][0] - point_list[avg+rcnt+1][0])**2:
        rcnt += 1

    x_candidate = point_list[avg-lcnt: avg+rcnt+1]
    x_candidate = sorted(x_candidate, key=lambda x: x[1])

    for i in range(len(x_candidate)-1):
        for j in range(i+1, len(x_candidate)):
            if min_both > (x_candidate[i][1] - x_candidate[j][1])**2:
                tmp = min(tmp, dist_point(x_candidate[i], x_candidate[j]))
            else:
                break
    return tmp


tc = int(input())
point_list = []
for __ in range(tc):
    point_list.append(list(map(int, input().split())))

point_list = sorted(point_list, key=lambda x: (x[0]))


def solution(start, end):
    cnt = 1
    tmp = MIN_NUM

    if end - start + 1 <= 3:
        return brute(start, end)

    else:
        avg = (start+end)//2
        min_left = solution(start, avg-1)
        min_right = solution(avg+1, end)
        min_both = min(min_left, min_right)

        tmp = area_point(avg, start, end, min_both)

        return min(tmp, min_left, min_right)


print(solution(0, tc-1))