#BOJ 1920
import sys
input = sys.stdin.readline

def binary_search(arr, target, start, end):
    if start > end:
        return 0
    mid = (start + end) // 2
    if arr[mid] == target:
        return 1
    elif arr[mid] > target:
        return binary_search(arr, target, start, mid-1)
    else:
        return binary_search(arr, target, mid+1, end)
    
N = int(input())
A = list(map(int, input().split()))
M = int(input())

A.sort()

for i in list(map(int, input().split())):
    print(binary_search(A, i, 0, N-1))

    