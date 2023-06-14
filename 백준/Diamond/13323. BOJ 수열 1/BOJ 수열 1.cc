#include <iostream>
#include <queue>
using namespace std;

int main() {
    int n;
    int input;
    long long total_movement = 0;
    priority_queue<int> pq;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> input;
        input -= i;

        if (!pq.empty() && pq.top() > input) {
            pq.push(input); // Make sure to push the number before updating the result
            total_movement += pq.top() - input;
            pq.pop();
            pq.push(input);
        } else {
            pq.push(input);
        }
    }
    cout << total_movement << '\n';

    return 0;
}
