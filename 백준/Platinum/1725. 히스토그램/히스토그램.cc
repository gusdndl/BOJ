#include<bits/stdc++.h>
using namespace std;

int N, h[100002], ans;
stack<int> s;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>N;
    for(int i=1;i<=N;i++) cin>>h[i];

    s.push(0);
    for(int i=1;i<=N+1;i++){
        while(!s.empty() && h[s.top()] > h[i]){
            int j=s.top(); s.pop();
            int w=i-s.top()-1;
            ans=max(ans, h[j]*w);
        }
        s.push(i);
    }
    cout<<ans;
    return 0;
}
