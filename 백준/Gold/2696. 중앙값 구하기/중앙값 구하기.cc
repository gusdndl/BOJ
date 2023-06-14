#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while(T--) {
        int M;
        cin >> M;

        priority_queue<int, vector<int>, less<int>> maxHeap;  // Lower half
        priority_queue<int, vector<int>, greater<int>> minHeap;  // Upper half

        vector<int> medians;

        for(int i=1; i<=M; i++) {
            int x;
            cin >> x;

            if(maxHeap.size() > minHeap.size()) {
                minHeap.push(x);
            } else {
                maxHeap.push(x);
            }

            if(!maxHeap.empty() && !minHeap.empty()) {
                if(maxHeap.top() > minHeap.top()) {
                    int a = maxHeap.top(), b = minHeap.top();
                    maxHeap.pop(); minHeap.pop();
                    maxHeap.push(b); minHeap.push(a);
                }
            }

            if(i % 2 == 1) {
                medians.push_back(maxHeap.top());
            }
        }

        cout << medians.size() << "\n";
        for(int i=0; i<medians.size(); i++) {
            if(i != 0 && i % 10 == 0) cout << "\n";
            cout << medians[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}
