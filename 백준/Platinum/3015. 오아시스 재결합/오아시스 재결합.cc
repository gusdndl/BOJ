#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n;
    cin >> n;

    stack<pair<int, int>> s;
    ll res = 0;

    for(int i = 0; i < n; i++) {
        int h;
        cin >> h;

        pair<int, int> p = make_pair(h, 1);
        while(!s.empty()) {
            if(s.top().first <= h) {
                res += (ll)s.top().second;
                if(s.top().first == h) p.second += s.top().second;
                s.pop();
            } else break;
        }
        if(!s.empty()) res++;
        s.push(p);
    }
    
    cout << res << "\n";
    
    return 0;
}
