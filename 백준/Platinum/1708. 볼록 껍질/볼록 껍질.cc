#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> Point;
vector<Point> p;
vector<Point> stk;
int n;

ll ccw(Point a, Point b, Point c){
    return (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
}

bool cmp(Point a, Point b){
    ll t = ccw(p[0], a, b);
    if(t != 0) return t > 0;
    return a < b;
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    p.resize(n);
    for(int i=0; i<n; i++){
        cin >> p[i].first >> p[i].second;
        if(p[i] < p[0]) swap(p[i], p[0]);
    }
    sort(p.begin() + 1, p.end(), cmp);
    for(auto &i : p){
        while(stk.size() >= 2 && ccw(stk[stk.size()-2], stk.back(), i) <= 0) stk.pop_back();
        stk.push_back(i);
    }
    cout << stk.size();
    return 0;
}
