import sys
from collections import deque

def solve():
    n = int(sys.stdin.readline())
    queue = deque(range(1, n+1))

    while len(queue) > 1:
        queue.popleft()        # Discard the top card
        queue.append(queue.popleft())  # Move the next card to the bottom

    return queue[0]

print(solve())
