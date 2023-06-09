#include<iostream>
#include<set>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int T; // number of test cases
    cin >> T;

    while(T--) {
        multiset<int> ms; // dual priority queue

        int k; // number of operations
        cin >> k;

        while(k--) {
            char operation; 
            int number;
            cin >> operation >> number;

            if(operation == 'I') {
                ms.insert(number);
            } else if(operation == 'D' && !ms.empty()) {
                if(number == -1) {
                    ms.erase(ms.begin()); // delete minimum element
                } else {
                    auto end = ms.end();
                    end--;
                    ms.erase(end); // delete maximum element
                }
            }
        }

        if(ms.empty()) {
            cout << "EMPTY" << "\n";
        } else {
            auto end = ms.end();
            end--;
            cout << *end << " " << *ms.begin() << "\n"; // print maximum and minimum
        }
    }

    return 0;
}
