#include <iostream>
#include <vector>
using namespace std;

const int mod = 1000000;
const int period = 15 * mod / 10;
vector<int> fibo(period+1);

void calcFibo() {
    fibo[0] = 0; 
    fibo[1] = 1;
    for(int i = 2; i <= period; i++) {
        fibo[i] = fibo[i-1] + fibo[i-2];
        fibo[i] %= mod;
    }
}

int main() {
    long long N;
    cin >> N;
    calcFibo();
    cout << fibo[N % period] << endl;
    return 0;
}
