#include <bits/stdc++.h>
#define FIRST_ELEMENT first
#define SECOND_ELEMENT second
#define ALL_ELEMENTS(v) v.begin(), v.end()
#define ADD_ELEMENT push_back
using namespace std;

typedef long long ll;
typedef pair<ll, ll> Point;

struct CustomStruct {
    int x, y, z;
    CustomStruct(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}
    bool operator < (const CustomStruct &t) const {
        if (x != t.x) return x < t.x;
        if (y != t.y) return y < t.y;
        return z < t.z;
    }
};

int k, n;
int arr[4][202020];
vector<CustomStruct> temp;
vector<Point> points;
set<Point> st[202020];

int solve() {
    int answer = 0;
    for (int i = 0; i < n; i++) {
        int left = 1, right = answer + 1;
        while (left < right) {
            int middle = (left + right) / 2;
            auto it = st[middle].lower_bound(points[i]);
            if (it == st[middle].begin())
                right = middle;
            else {
                if (prev(it)->SECOND_ELEMENT < points[i].SECOND_ELEMENT)
                    left = middle + 1;
                else
                    right = middle;
            }
        }
        answer = max(answer, left);
        auto it = st[left].insert(points[i]).first;
        it++;
        while (it != st[left].end() && it->SECOND_ELEMENT >= points[i].SECOND_ELEMENT) {
            auto tempIt = it;
            it++;
            st[left].erase(tempIt);
        }
    }
    return answer;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> k >> n;
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= n; j++) {
            if (k < i)
                arr[i][j] = arr[i - 1][j];
            else
                cin >> arr[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        temp.ADD_ELEMENT({arr[1][i], arr[2][i], arr[3][i]});
    }
    sort(ALL_ELEMENTS(temp));
    for (auto &i : temp) {
        points.ADD_ELEMENT({i.y, i.z});
    }
    cout << solve();
}
