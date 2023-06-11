#include<bits/stdc++.h>
using namespace std;
const int MAX=1e6+5;
int t,n,m,tree[2*MAX],a[MAX],pos[MAX];
void update(int i,int diff){
    while(i<2*MAX){
        tree[i]+=diff;
        i+=(i&-i);
    }
}
int sum(int i){
    int ans=0;
    while(i>0){
        ans+=tree[i];
        i-=(i&-i);
    }
    return ans;
}
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin>>t;
    while(t--){
        cin>>n>>m;
        fill(tree,tree+2*MAX,0);
        for(int i=1;i<=n;++i){
            update(i+m,1);
            a[i]=i+m;
            pos[i]=i+m;
        }
        for(int i=m;i>=1;--i){
            int x;cin>>x;
            cout<<sum(a[x]-1)<<" ";
            update(a[x],-1);
            a[x]=i;
            update(a[x],1);
        }
        cout<<"\n";
    }
}
