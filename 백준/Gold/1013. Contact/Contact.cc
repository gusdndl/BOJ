#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    regex re("(100+1+|01)+");
    int T;
    cin >> T;
    while (T--) {
        string signal;
        cin >> signal;
        if (regex_match(signal, re)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
