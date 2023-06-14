#include <bits/stdc++.h>
#define FIRST first
#define SECOND second
#define ALL(v) v.begin(), v.end()
#define COMPRESS(v) sort(ALL(v)), v.erase(unique(ALL(v)), v.end())
using namespace std;

typedef long long LL;
typedef pair<LL, LL> Pair;

int N, M, K;
Pair arr[202020];
vector<Pair> vec[404040];
LL answer;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M;
    K = N + M;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i].FIRST;
        arr[i].SECOND = 0;
    }
    for (int i = 1; i <= M; i++) {
        cin >> arr[i + N].FIRST;
        arr[i + N].SECOND = 1;
    }
    sort(arr + 1, arr + K + 1);

    int now = K;
    for (int i = 1; i <= K; i++) {
        if (arr[i].SECOND == 0) {
            vec[now++].push_back(arr[i]);
        } else {
            vec[--now].push_back(arr[i]);
        }
    }
    for (int i = 0; i < 404040; i++) {
        if (vec[i].size()) {
            LL total = 0;
            for (int j = 1; j < vec[i].size(); j += 2) {
                total += abs(vec[i][j].FIRST - vec[i][j - 1].FIRST);
            }
            if (!(vec[i].size() & 1)) {
                answer += total;
                continue;
            }
            LL minimum = total;
            for (int j = vec[i].size() - 1; j - 2 >= 0; j -= 2) {
                total += abs(vec[i][j].FIRST - vec[i][j - 1].FIRST) - abs(vec[i][j - 1].FIRST - vec[i][j - 2].FIRST);
                minimum = min(minimum, total);
            }
            answer += minimum;
        }
    }
    cout << answer;
}
