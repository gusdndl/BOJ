#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for(int i=0; i<n; i++)
        cin >> arr[i];

    vector<int> lis;
    for(int i=0; i<n; i++) {
        if(lis.empty() || lis.back() < arr[i])
            lis.push_back(arr[i]);
        else {
            int idx = lower_bound(lis.begin(), lis.end(), arr[i]) - lis.begin();
            lis[idx] = arr[i];
        }
    }

    cout << lis.size();

    return 0;
}
