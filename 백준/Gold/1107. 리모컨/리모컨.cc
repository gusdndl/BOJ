#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int target;
int broken_cnt;
bool broken[10];

int possible(int c) {
    if (c == 0) {
        if (broken[0]) {
            return 0;
        } else {
            return 1;
        }
    }
    int len = 0;
    while (c > 0) {
        if (broken[c % 10]) {
            return 0;
        }
        c /= 10;
        len += 1;
    }
    return len;
}

int main() {
    cin >> target;
    cin >> broken_cnt;
    for (int i = 0; i < broken_cnt; i++) {
        int x;
        cin >> x;
        broken[x] = true;
    }
    int ans = abs(target - 100);
    for (int i = 0; i <= 1000000; i++) {
        int c = i;
        int len = possible(c);
        if (len > 0) {
            int press = len + abs(c - target);
            if (ans > press) {
                ans = press;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}
