n = int(input())

for _ in range(n):
    ps = input()
    stack = []

    for p in ps:
        if p == '(':
            stack.append(p)
        elif p == ')':
            if not stack or stack.pop() != '(':
                print('NO')
                break
    else:
        if not stack:
            print('YES')
        else:
            print('NO')
