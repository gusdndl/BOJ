#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while(T--) {
        long long x, y;
        cin >> x >> y;
        long long distance = y - x;
        long long max_speed = sqrt(distance);
        if(max_speed * max_speed == distance) {
            cout << 2 * max_speed - 1 << "\n";
        }
        else if(max_speed * max_speed < distance && distance <= max_speed * max_speed + max_speed) {
            cout << 2 * max_speed << "\n";
        }
        else {
            cout << 2 * max_speed + 1 << "\n";
        }
    }
    return 0;
}
