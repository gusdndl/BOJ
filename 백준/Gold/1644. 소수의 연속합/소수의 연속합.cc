#include <iostream>
#include <vector>
using namespace std;

#define MAX 4000001

bool check[MAX]; // to mark non-prime numbers
vector<int> prime; // to store prime numbers

int main() {
    int N;
    cin >> N;

    for(int i=2; i<=N; i++) {
        if(!check[i]) {
            prime.push_back(i);
            for(int j=i*2; j<=N; j+=i) check[j] = true;
        }
    }

    int start = 0, end = 0, sum = 0, cnt = 0;

    while(true) {
        if(sum >= N) sum -= prime[start++];
        else if(end == prime.size()) break;
        else sum += prime[end++];
        if(sum == N) cnt++;
    }

    cout << cnt << "\n";

    return 0;
}
