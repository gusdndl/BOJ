#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

typedef long long ll;

ll numPeople, numEvents, numQueries;
ll x[300030], y[300030], z[300030];
ll lowerBound[300030], upperBound[300030], fenwickTree[300030], goals[300030];
vector<vector<ll>> uniqueEvents, queries;

void update(ll pos, ll val) {
    while (pos <= numEvents) {
        fenwickTree[pos] += val;
        pos += (pos & -pos);
    }
}

ll query(int pos) {
    ll ret = 0;
    while (pos > 0) {
        ret += fenwickTree[pos];
        pos -= (pos & -pos);
    }
    return ret;
}

void processEvent(int eventIndex) {
    if (y[eventIndex] >= x[eventIndex]) {
        update(x[eventIndex], z[eventIndex]);
        update(y[eventIndex] + 1, -z[eventIndex]);
    } else {
        update(1, z[eventIndex]);
        update(y[eventIndex] + 1, -z[eventIndex]);
        update(x[eventIndex], z[eventIndex]);
    }
}

int main() {
    scanf("%lld%lld", &numPeople, &numEvents);
    uniqueEvents.resize(numPeople + 1);
    for (int i = 1, t; i <= numEvents; i++) {
        scanf("%lld", &t);
        uniqueEvents[t].push_back(i);
    }
    for (int i = 1; i <= numPeople; i++) {
        scanf("%lld", &goals[i]);
    }
    scanf("%lld", &numQueries);
    queries.resize(numQueries + 1);
    for (int i = 1; i <= numQueries; i++) {
        scanf("%lld%lld%lld", &x[i], &y[i], &z[i]);
    }
    for (int i = 1; i <= numPeople; i++) {
        lowerBound[i] = 1;
        upperBound[i] = numQueries + 1;
    }
    bool isUpdated = true;
    while (isUpdated) {
        isUpdated = false;
        memset(fenwickTree, 0, sizeof(fenwickTree));
        for (int i = 1; i <= numPeople; i++) {
            if (lowerBound[i] < upperBound[i]) {
                queries[(lowerBound[i] + upperBound[i]) >> 1].push_back(i);
                isUpdated = true;
            }
        }
        for (int i = 1; i <= numQueries; i++) {
            processEvent(i);
            while (!queries[i].empty()) {
                int idx = queries[i].back();
                queries[i].pop_back();
                ll sum = 0;
                for (auto next : uniqueEvents[idx]) {
                    sum += query(next);
                    if (sum >= goals[idx]) break;
                }
                if (sum >= goals[idx]) {
                    upperBound[idx] = i;
                } else {
                    lowerBound[idx] = i + 1;
                }
            }
        }
    }
    for (int i = 1; i <= numPeople; i++) {
        if (lowerBound[i] == numQueries + 1) {
            puts("NIE");
        } else {
            printf("%d\n", lowerBound[i]);
        }
    }
    return 0;
}
