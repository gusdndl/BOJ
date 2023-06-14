#include <bits/stdc++.h>
#define ARRAY_SIZE 4005
#define enable_fast_io ios_base::sync_with_stdio(0)
#define x first
#define y second
#define push_to_vector push_back
#define all_of_vector(v) v.begin(), v.end()
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pair_ll;
const ll INF = 1e13;
const ll MODULO = 1000;

ll greatest_common_divisor(ll a, ll b){
    if(a%b) return greatest_common_divisor(b, a%b);
    return b;
}

ll arraySize, valueModulo, counter;
ll arrayElements[ARRAY_SIZE];

ll divide_and_conquer(ll left, ll right){
    ll midPoint=(right-left+2)/2;
    if(midPoint<=1) return arrayElements[left];
    ll halfSize[3] = {0,};
    for(int i=0; i<3; i++)
        halfSize[i] = divide_and_conquer(left+i*(midPoint/2), left+i*(midPoint/2)+midPoint-2)/(midPoint/2);
    if(halfSize[0]%2==halfSize[1]%2) return (halfSize[0]+halfSize[1])*(midPoint/2);
    else if(halfSize[0]%2==halfSize[2]%2){
        for(int i=0; i<midPoint/2; i++)
            swap(arrayElements[left+i+midPoint/2], arrayElements[left+i+midPoint]);
        return (halfSize[0]+halfSize[2])*(midPoint/2);
    }
    else{
        for(int i=0; i<midPoint/2; i++)
            swap(arrayElements[left+i], arrayElements[left+i+midPoint]);
        return (halfSize[2]+halfSize[1])*(midPoint/2);
    }
}

int main() {
    enable_fast_io; cin.tie(0); cout.tie(0);
    cin >> arraySize;
    for(int i=0; i<2*arraySize-1; i++)
        cin >> arrayElements[i];
    divide_and_conquer(0,2*(arraySize-1));
    for(int i=0; i<arraySize; i++)
        cout << arrayElements[i] << ' ';
}
