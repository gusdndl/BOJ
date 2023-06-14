#include <bits/stdc++.h>
#define COORD first
#define POINT second
#define all_points(v) v.begin(), v.end()
using namespace std;

typedef long long ll;
typedef pair<ll, ll> Point;

int num_points;
vector<Point> points;
vector<ll> coordinates;
vector<vector<int>> adjacency;
ll answer;

vector<int> parent;
vector<ll> max_value;
vector<ll> sum_value;
vector<int> is_cycle;

void initialize() {
    for (int i = 0; i < coordinates.size(); i++) {
        parent[i] = i;
        max_value[i] = coordinates[i];
        sum_value[i] = coordinates[i];
    }
}

int find_parent(int v) {
    return v == parent[v] ? v : parent[v] = find_parent(parent[v]);
}

bool merge(int u, int v) {
    u = find_parent(u);
    v = find_parent(v);
    if (u == v)
        return false;
    parent[u] = v;
    max_value[v] = max(max_value[u], max_value[v]);
    sum_value[v] += sum_value[u];
    is_cycle[v] = is_cycle[u] || is_cycle[v];
    return true;
}

int get_index(ll x) {
    return lower_bound(all_points(coordinates), x) - coordinates.begin();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> num_points;
    points.resize(num_points);
    coordinates.reserve(num_points << 1);
    for (auto& p : points) {
        cin >> p.COORD >> p.POINT;
        coordinates.push_back(p.COORD);
        coordinates.push_back(p.POINT);
    }
    sort(all_points(coordinates));
    coordinates.erase(unique(all_points(coordinates)), coordinates.end());

    adjacency.resize(coordinates.size());
    for (auto p : points) {
        adjacency[get_index(p.COORD)].push_back(get_index(p.POINT));
        adjacency[get_index(p.POINT)].push_back(get_index(p.COORD));
    }

    parent.resize(coordinates.size());
    max_value.resize(coordinates.size());
    sum_value.resize(coordinates.size());
    is_cycle.resize(coordinates.size());

    initialize();

    for (int i = 0; i < num_points; i++) {
        ll x = get_index(points[i].COORD);
        ll y = get_index(points[i].POINT);
        if (!merge(x, y)) {
            is_cycle[find_parent(x)] = 1;
        }
    }

    for (auto p : points) {
        answer += p.COORD + p.POINT;
    }

    for (int i = 0; i < coordinates.size(); i++) {
        if (i != find_parent(i))
            continue;
        if (is_cycle[i])
            answer -= sum_value[i];
        else
            answer -= sum_value[i] - max_value[i];
    }

    cout << answer;

    return 0;
}
