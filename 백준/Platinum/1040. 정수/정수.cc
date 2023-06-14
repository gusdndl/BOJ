#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long llong;
int mem[2][1 << 10][18], len, counter;
int recursive(int lower, int set, int depth, int* arr) {
    if (depth == len)
        return counter == 0;
    int& ref = mem[lower][set][depth];
    if (ref != -1) return ref;
    ref = 0;
    int i, Start = lower ? arr[depth] : 0;
    for (i = Start; i < 10; i++) {
        if ((1 << i) & set)
            ref |= recursive(lower && i == Start, set, depth + 1, arr);
        else if (counter) {
            counter--;
            ref |= recursive(lower && i == Start, set | (1 << i), depth + 1, arr);
            counter++;
        }
    }
    return ref;
}
void func(int lower, int set, int depth, int* arr) {
    if (depth == len) return;
    int& ref = mem[lower][set][depth];
    int i, Start = lower ? arr[depth] : 0;
    for (i = Start; i < 10; i++) {
        if (((1 << i) & set)) {
            if (recursive(lower && i == Start, set, depth + 1, arr)) {
                printf("%d", i);
                func(lower && i == Start, set, depth + 1, arr);
                break;
            }
        }
        else if (counter) {
            counter--;
            if (recursive(lower && i == Start, set | (1 << i), depth + 1, arr)) {
                printf("%d", i);
                func(lower && i == Start, set | (1 << i), depth + 1, arr);
                break;
            }
            counter++;
        }
    }
}
int main() {
    int K, arr[18], i;
    llong N, temp;
    scanf("%lld%d", &N, &K);
    temp = N;
    for (i = 0; temp; i++) {
        arr[i] = temp % 10;
        temp /= 10;
    }
    len = max(i, K);
    if (i >= K) {
        for (i = 0; i < len / 2; i++) {
            temp = arr[i];
            arr[i] = arr[len - 1 - i];
            arr[len - 1 - i] = temp;
        }
    }
    else {
        arr[0] = 1;
        for (i = 1; i < len; i++) arr[i] = 0;
    }
    counter = K;
    memset(mem, -1, sizeof mem);
    if (recursive(1, 0, 0, arr))
        func(1, 0, 0, arr);
    else {
        arr[0] = 1;
        len++;
        for (i = 1; i < len; i++) arr[i] = 0;
        memset(mem, -1, sizeof mem);
        recursive(1, 0, 0, arr);
        func(1, 0, 0, arr);
    }
    return 0;
}
