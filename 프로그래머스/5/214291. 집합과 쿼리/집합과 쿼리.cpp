#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define eb emplace_back
#define fst first
#define snd second
using namespace std;
using ll = long long;

int root(vector<int>& rt, int x){
    while(x != rt[x]) x = rt[x] = rt[rt[x]];
    return x;
}

void unite(vector<int>& rt, vector<int>& sz, int a, int b){
    a = root(rt, a), b = root(rt, b);
    if(a == b) return;
    if(sz[a] > sz[b]) swap(a, b);
    rt[a] = b;
    sz[b] += sz[a];
}

vector<string> solution(int n, vector<vector<int>> queries){
    vector<string> ans;
    vector<int> rt(n), sz(n), li(n), hd(n), tl(n), nxt(n, -1), prv(n, -1), tm(n);
    iota(all(rt), 0); iota(all(li), 0); iota(all(hd), 0); iota(all(tl), 0);
    fill(all(sz), 1);
    int ix = n;
    int curr = 1;
    for(auto& q: queries){
        int qi = q[0], x = root(rt, q[1]), y = root(rt, q[2]);
        if(qi == 1){
            if(li[x] == li[y]) continue;
            int i = hd[li[y]];
            while(i != -1){
                unite(rt, sz, i, y);
                i = nxt[i];
            }
            hd[li[y]] = tl[li[y]] = -1;
            y = root(rt, y);
            li[y] = li[x];
            int j = tl[li[x]];
            nxt[j] = y; prv[y] = j; nxt[y] = -1;
            tl[li[x]] = y;
            tm[y] = curr;
        }
        if(qi == 2){
            if(tm[x] > tm[y]) continue;
            int i = x;
            while(1){
                unite(rt, sz, i, x);
                if(i == y) break;
                i = nxt[i];
            }
            if(hd[li[x]] == x && tl[li[x]] == y){
                hd[li[x]] = tl[li[x]] = -1;
            }
            else if(hd[li[x]] == x && tl[li[x]] != y){
                hd[li[x]] = nxt[y];
                prv[nxt[y]] = -1;
            }
            else if(hd[li[x]] != x && tl[li[x]] == y){
                tl[li[x]] = prv[x];
                nxt[prv[x]] = -1;
            }
            else{
                nxt[prv[x]] = nxt[y];
                prv[nxt[y]] = prv[x];
            }
            x = root(rt, x);
            prv[x] = nxt[x] = -1;
            hd.eb(x); tl.eb(x); li[x] = ix++;
            tm[x] = curr;
        }
        if(qi == 3) ans.eb(li[x] == li[y] ? "Yes" : "No");
        curr++;
    }
    return ans;
}