#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<pair<int, int>> lines(n);
    for(int i = 0; i < n; i++) cin >> lines[i].first >> lines[i].second;

    sort(lines.begin(), lines.end());

    vector<int> lis;
    vector<int> idx(n + 1);
    vector<int> trace(n + 1, -1);
    for(int i = 0; i < n; i++) {
        if(lis.empty() || lis.back() < lines[i].second) {
            idx[lis.size()] = i;
            if(!lis.empty()) trace[i] = idx[lis.size()-1];
            lis.push_back(lines[i].second);
        } else {
            auto it = lower_bound(lis.begin(), lis.end(), lines[i].second);
            *it = lines[i].second;
            idx[it - lis.begin()] = i;
            if(it - lis.begin() > 0) trace[i] = idx[it - lis.begin() - 1];
        }
    }

    cout << n - lis.size() << "\n";

    vector<bool> ans(n, true);
    for(int i = idx[lis.size() - 1]; i != -1; i = trace[i]) ans[i] = false;
    for(int i = 0; i < n; i++) if(ans[i]) cout << lines[i].first << "\n";

    return 0;
}
