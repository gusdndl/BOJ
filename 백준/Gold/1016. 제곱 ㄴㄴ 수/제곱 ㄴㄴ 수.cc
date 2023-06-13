#include <iostream>
#include <vector>
#define MAX 1000001

using namespace std;

bool isNotSquareFree[MAX];
vector<long long> squares;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    long long min, max;
    cin >> min >> max;

    for (long long i = 2; i * i <= max; i++) {
        squares.push_back(i * i);
    }

    for (long long &square : squares) {
        long long start = min / square;
        if (min % square != 0) start++;
        while (start * square <= max) {
            isNotSquareFree[start * square - min] = true;
            start++;
        }
    }

    int cnt = 0;
    for (int i = 0; i <= max - min; i++) {
        if (!isNotSquareFree[i]) cnt++;
    }

    cout << cnt;
    return 0;
}
