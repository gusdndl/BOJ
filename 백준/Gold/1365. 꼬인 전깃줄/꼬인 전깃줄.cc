#include <iostream>
#include <algorithm>
#include <vector>
#define MAX 100001

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int N, pole[MAX];
    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> pole[i];
    }

    vector<int> LIS;
    LIS.push_back(pole[0]);

    for (int i = 1; i < N; i++) {
        if (LIS.back() < pole[i]) {
            LIS.push_back(pole[i]);
        } else {
            int idx = lower_bound(LIS.begin(), LIS.end(), pole[i]) - LIS.begin();
            LIS[idx] = pole[i];
        }
    }
    
    cout << N - LIS.size();
    return 0;
}
