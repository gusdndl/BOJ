#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;
    
    vector<int> solutions(N);
    for (int i = 0; i < N; i++) {
        cin >> solutions[i];
    }
    
    int left = 0;
    int right = N - 1;
    int minSum = abs(solutions[left] + solutions[right]);
    int answerLeft = left;
    int answerRight = right;
    
    while (left < right) {
        int sum = solutions[left] + solutions[right];
        if (abs(sum) < minSum) {
            minSum = abs(sum);
            answerLeft = left;
            answerRight = right;
        }
        
        if (sum < 0) {
            left++;
        }
        else {
            right--;
        }
    }
    
    cout << solutions[answerLeft] << " " << solutions[answerRight] << endl;
    
    return 0;
}
