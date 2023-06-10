#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<long long> solutions(N);
    for (int i = 0; i < N; i++) {
        cin >> solutions[i];
    }

    sort(solutions.begin(), solutions.end());

    long long answer = 3e9 + 1;
    vector<long long> result(3);

    for (int i = 0; i < N - 2; i++) {
        int left = i + 1;
        int right = N - 1;

        while (left < right) {
            long long sum = solutions[i] + solutions[left] + solutions[right];
            if (llabs(sum) < answer) {
                answer = llabs(sum);
                result[0] = solutions[i];
                result[1] = solutions[left];
                result[2] = solutions[right];
            }
            
            if (sum < 0) {
                left++;
            }
            else {
                right--;
            }
        }
    }

    sort(result.begin(), result.end());

    for (int i = 0; i < 3; i++) {
        cout << result[i] << ' ';
    }

    return 0;
}
