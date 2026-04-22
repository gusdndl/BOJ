#include <bits/stdc++.h>
using namespace std;

static const int LIM = 1000000000;
static const int ODD_FIXED = 20;
static const int CHOOSE_SMALL_MAX = 5000;

struct State {
    int a;
    int kind; // 0 = fixed B, 1 = interval [lo, hi], 2 = set vals
    int b;
    int lo, hi;
    vector<int> vals;
};

unordered_map<int, int> memo_answer;
unordered_map<int, vector<int>> divisors_cache;
unordered_map<long long, vector<int>> odd_prime_factor_cache;

static inline int dist_to_multiple(long long n, long long x) {
    long long r = n % x;
    return (int)min(r, x - r);
}

static inline int getH(int n) {
    if (2LL * n <= LIM) return n;
    return max(LIM - n, n / 3);
}

int ask(int x) {
    auto it = memo_answer.find(x);
    if (it != memo_answer.end()) return it->second;

    cout << "? " << x << '\n' << flush;

    int y;
    if (!(cin >> y)) exit(0);
    if (y == -1) exit(0);

    memo_answer[x] = y;
    return y;
}

[[noreturn]] void finish_answer(int A, int B) {
    cout << "! " << A << ' ' << B << '\n' << flush;
    exit(0);
}

long long mod_inv(long long a, long long mod) {
    long long b = mod, u = 1, v = 0;
    while (b) {
        long long t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    u %= mod;
    if (u < 0) u += mod;
    return u;
}

bool crt_merge(long long a1, long long m1, long long a2, long long m2, long long &a, long long &m) {
    long long g = std::gcd(m1, m2);
    long long diff = a2 - a1;
    if (diff % g != 0) return false;

    long long p = m1 / g;
    long long q = m2 / g;
    long long rhs = diff / g;

    long long t = 0;
    if (q != 1) {
        long long inv = mod_inv((p % q + q) % q, q);
        t = ((rhs % q + q) % q) * inv % q;
    }

    m = m1 / g * m2;
    __int128 aa = (__int128)a1 + (__int128)m1 * t;
    a = (long long)(aa % m);
    if (a < 0) a += m;
    return true;
}

const vector<int>& get_divisors(int v) {
    auto it = divisors_cache.find(v);
    if (it != divisors_cache.end()) return it->second;

    vector<int> res;
    for (int i = 1; 1LL * i * i <= v; ++i) {
        if (v % i == 0) {
            res.push_back(i);
            if (1LL * i * i != v) res.push_back(v / i);
        }
    }
    sort(res.begin(), res.end());

    auto inserted = divisors_cache.emplace(v, std::move(res));
    return inserted.first->second;
}

const vector<int>& get_odd_prime_divisors(long long v) {
    static const vector<int> empty;
    if (v <= 1) return empty;

    auto it = odd_prime_factor_cache.find(v);
    if (it != odd_prime_factor_cache.end()) return it->second;

    vector<int> res;
    long long x = v;
    while ((x & 1LL) == 0) x >>= 1;

    for (long long p = 3; p * p <= x; p += 2) {
        if (x % p == 0) {
            if (p <= LIM) res.push_back((int)p);
            while (x % p == 0) x /= p;
        }
    }
    if (x > 1 && x <= LIM) res.push_back((int)x);

    sort(res.begin(), res.end());
    res.erase(unique(res.begin(), res.end()), res.end());

    auto inserted = odd_prime_factor_cache.emplace(v, std::move(res));
    return inserted.first->second;
}

vector<int> generate_candidates(const array<int, 31> &small, int mode) {
    // mode == 0 : exact mode for B > 15
    // mode >= 3 : fixed modulo mode
    vector<pair<long long, long long>> states = {{0, 1}};

    for (int x = 2; x <= 30; ++x) {
        vector<int> allowed;
        allowed.reserve(x);

        for (int r = 0; r < x; ++r) {
            int d = min(r, x - r);
            if (mode == 0) {
                if (d == small[x]) allowed.push_back(r);
            } else {
                if (d % mode == small[x]) allowed.push_back(r);
            }
        }

        vector<pair<long long, long long>> nxt;
        nxt.reserve(states.size() * max<int>(1, (int)allowed.size()));

        for (auto [a, mod] : states) {
            for (int r : allowed) {
                long long na, nm;
                if (!crt_merge(a, mod, r, x, na, nm)) continue;
                if (nm > LIM) {
                    if (1 <= na && na <= LIM) nxt.push_back({na, nm});
                } else {
                    nxt.push_back({na, nm});
                }
            }
        }

        sort(nxt.begin(), nxt.end());
        nxt.erase(unique(nxt.begin(), nxt.end()), nxt.end());
        states.swap(nxt);

        if (states.empty()) break;
    }

    vector<int> vals;
    for (auto [a, mod] : states) {
        if (mod > LIM) {
            vals.push_back((int)a);
        } else {
            long long cur = (a == 0 ? mod : a);
            for (; cur <= LIM; cur += mod) vals.push_back((int)cur);
        }
    }

    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    return vals;
}

bool apply_query(State &st, int x, int y) {
    int v = dist_to_multiple(st.a, x);

    if (st.kind == 0) {
        return v % st.b == y;
    }

    if (st.kind == 1) {
        if (y > v) return false;

        if (y == v) {
            st.lo = max(st.lo, v + 1);
            return st.lo <= st.hi;
        }

        int diff = v - y;
        const auto &divs = get_divisors(diff);

        vector<int> nxt;
        nxt.reserve(divs.size());
        for (int d : divs) {
            if (d >= st.lo && d <= st.hi && d > y) nxt.push_back(d);
        }
        if (nxt.empty()) return false;

        st.kind = 2;
        st.vals = std::move(nxt);
        st.lo = st.hi = 0;
        return true;
    }

    vector<int> nxt;
    nxt.reserve(st.vals.size());
    for (int b : st.vals) {
        if (v % b == y) nxt.push_back(b);
    }
    st.vals.swap(nxt);
    return !st.vals.empty();
}

void parity_update(vector<pair<int, int>> &intervals, int x, int want) {
    int h = (x - 1) / 2;
    vector<pair<int, int>> res;

    for (auto [L, R] : intervals) {
        int q0 = (L + h) / x;
        int q1 = (R + h) / x;
        int q = q0 + ((want - (q0 & 1) + 2) & 1);

        for (; q <= q1; q += 2) {
            int l = max(L, q * x - h);
            int r = min(R, (q + 1) * x - h - 1);
            if (l <= r) {
                if (!res.empty() && res.back().second + 1 >= l) {
                    res.back().second = max(res.back().second, r);
                } else {
                    res.push_back({l, r});
                }
            }
        }
    }

    intervals.swap(res);
}

vector<int> enumerate_parity_candidates(const vector<pair<int, int>> &intervals, int parity) {
    vector<int> vals;
    for (auto [l, r] : intervals) {
        int first = ((l & 1) == parity ? l : l + 1);
        for (int v = first; v <= r; v += 2) vals.push_back(v);
    }
    return vals;
}

bool state_less(const State &a, const State &b) {
    if (a.a != b.a) return a.a < b.a;
    if (a.kind != b.kind) return a.kind < b.kind;
    if (a.kind == 0) return a.b < b.b;
    if (a.kind == 1) {
        if (a.lo != b.lo) return a.lo < b.lo;
        return a.hi < b.hi;
    }
    return a.vals < b.vals;
}

bool state_equal(const State &a, const State &b) {
    if (a.a != b.a || a.kind != b.kind) return false;
    if (a.kind == 0) return a.b == b.b;
    if (a.kind == 1) return a.lo == b.lo && a.hi == b.hi;
    return a.vals == b.vals;
}

void dedup_states(vector<State> &states) {
    sort(states.begin(), states.end(), state_less);
    states.erase(unique(states.begin(), states.end(), state_equal), states.end());
}

vector<int> get_alive_a(const vector<State> &states) {
    vector<int> alive;
    alive.reserve(states.size());
    for (auto &st : states) alive.push_back(st.a);
    sort(alive.begin(), alive.end());
    alive.erase(unique(alive.begin(), alive.end()), alive.end());
    return alive;
}

vector<int> possible_outputs(const State &st, int x) {
    int v = dist_to_multiple(st.a, x);

    if (st.kind == 0) return {v % st.b};

    if (st.kind == 2) {
        vector<int> outs;
        outs.reserve(st.vals.size());
        for (int b : st.vals) outs.push_back(v % b);
        sort(outs.begin(), outs.end());
        outs.erase(unique(outs.begin(), outs.end()), outs.end());
        return outs;
    }

    if (v < st.lo) return {v};

    // choose_query에서 interval state에 대해 사용하는 x는 작거나 a 근처라서 v가 작다.
    vector<int> outs;
    if (st.hi - st.lo <= 256) {
        outs.reserve(st.hi - st.lo + 1);
        for (int b = st.lo; b <= st.hi; ++b) outs.push_back(v % b);
        sort(outs.begin(), outs.end());
        outs.erase(unique(outs.begin(), outs.end()), outs.end());
        return outs;
    }

    outs.resize(v + 1);
    iota(outs.begin(), outs.end(), 0);
    return outs;
}

int choose_query(const vector<State> &states) {
    vector<int> cand;
    cand.reserve(CHOOSE_SMALL_MAX + states.size() * 64);

    for (int x = 2; x <= CHOOSE_SMALL_MAX; ++x) {
        if (!memo_answer.count(x)) cand.push_back(x);
    }

    for (auto &st : states) {
        long long a = st.a;

        for (int t = -20; t <= 20; ++t) {
            long long x = a + t;
            if (2 <= x && x <= LIM && !memo_answer.count((int)x)) cand.push_back((int)x);
        }

        long long extra[4] = {2LL * a - 3, 2LL * a - 1, 2LL * a + 1, 2LL * a + 3};
        for (long long x : extra) {
            if (2 <= x && x <= LIM && !memo_answer.count((int)x)) cand.push_back((int)x);
        }

        if (st.kind == 0 && st.b == 2) {
            for (int x : get_odd_prime_divisors(2LL * a - 1)) {
                if (!memo_answer.count(x)) cand.push_back(x);
            }
            for (int x : get_odd_prime_divisors(2LL * a - 3)) {
                if (!memo_answer.count(x)) cand.push_back(x);
            }
        }
    }

    sort(cand.begin(), cand.end());
    cand.erase(unique(cand.begin(), cand.end()), cand.end());

    int best_x = cand[0];
    tuple<int, int, int, int> best_score{INT_MAX, INT_MAX, INT_MAX, INT_MAX};

    for (int x : cand) {
        unordered_map<int, vector<int>> bucketA;
        unordered_map<int, int> bucketStateCnt;

        for (auto &st : states) {
            auto outs = possible_outputs(st, x);
            for (int y : outs) {
                bucketA[y].push_back(st.a);
                bucketStateCnt[y]++;
            }
        }

        int worstA = 0;
        int worstState = 0;

        for (auto &it : bucketA) {
            auto &vec = it.second;
            sort(vec.begin(), vec.end());
            vec.erase(unique(vec.begin(), vec.end()), vec.end());
            worstA = max(worstA, (int)vec.size());
            worstState = max(worstState, bucketStateCnt[it.first]);
        }

        auto score = make_tuple(worstA, worstState, -(int)bucketA.size(), x);
        if (score < best_score) {
            best_score = score;
            best_x = x;
            if (worstA == 1) break;
        }
    }

    return best_x;
}

int x_for_exact_distance(int a, int k) {
    if (k <= LIM - a) return a + k;
    return a - k;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    array<int, 31> small{};
    int mx = 0;
    bool all_zero = true;

    for (int x = 2; x <= 30; ++x) {
        small[x] = ask(x);
        mx = max(mx, small[x]);
        if (small[x] != 0) all_zero = false;
    }

    if (all_zero) finish_answer(0, 1);

    vector<pair<int, int>> large_queries;
    int cur = LIM + 1;
    for (int i = 0; i < ODD_FIXED; ++i) {
        cur = (cur + 1) / 2;
        if ((cur & 1) == 0) ++cur;
        large_queries.push_back({cur, ask(cur)});
    }

    vector<State> states;

    // B = 2 전용 빠른 분기
    if (mx <= 1) {
        int parity = small[2];
        vector<pair<int, int>> intervals = {{1, LIM}};
        bool ok = true;

        for (auto [x, y] : large_queries) {
            if (y > 1) {
                ok = false;
                break;
            }
            parity_update(intervals, x, y ^ parity);
            if (intervals.empty()) {
                ok = false;
                break;
            }
        }

        if (ok) {
            auto vals = enumerate_parity_candidates(intervals, parity);

            for (int x = 3; x <= 29; x += 2) {
                int y = small[x];
                vector<int> nxt;
                nxt.reserve(vals.size());
                for (int v : vals) {
                    if ((dist_to_multiple(v, x) & 1) == y) nxt.push_back(v);
                }
                vals.swap(nxt);
            }

            for (int v : vals) {
                State st{};
                st.a = v;
                st.kind = 0;
                st.b = 2;
                states.push_back(std::move(st));
            }
        }
    }

    // B = 3..15
    for (int m = max(3, mx + 1); m <= 15; ++m) {
        auto cand = generate_candidates(small, m);
        for (int a : cand) {
            State st{};
            st.a = a;
            st.kind = 0;
            st.b = m;

            bool alive = true;
            for (auto [x, y] : large_queries) {
                if (!apply_query(st, x, y)) {
                    alive = false;
                    break;
                }
            }
            if (alive) states.push_back(std::move(st));
        }
    }

    // B > 15
    auto exact = generate_candidates(small, 0);
    for (int a : exact) {
        State st{};
        st.a = a;
        st.kind = 1;
        st.lo = 16;
        st.hi = getH(a) + 1;

        bool alive = true;
        for (auto [x, y] : large_queries) {
            if (!apply_query(st, x, y)) {
                alive = false;
                break;
            }
        }
        if (alive) states.push_back(std::move(st));
    }

    dedup_states(states);

    while (true) {
        auto alive = get_alive_a(states);
        if ((int)alive.size() == 1) break;

        // B=2에서 끝까지 남는 n, n-2 진짜 동치쌍 처리
        if ((int)states.size() == 2 &&
            states[0].kind == 0 && states[1].kind == 0 &&
            states[0].b == 2 && states[1].b == 2 &&
            abs(states[0].a - states[1].a) == 2) {

            int n = max(states[0].a, states[1].a);
            vector<int> candx;

            for (int x : get_odd_prime_divisors(2LL * n - 1)) {
                if (!memo_answer.count(x)) candx.push_back(x);
            }
            for (int x : get_odd_prime_divisors(2LL * n - 3)) {
                if (!memo_answer.count(x)) candx.push_back(x);
            }

            sort(candx.begin(), candx.end());
            candx.erase(unique(candx.begin(), candx.end()), candx.end());

            if (candx.empty()) {
                finish_answer(min(states[0].a, states[1].a), 2);
            }

            int x = candx[0];
            int y = ask(x);

            vector<State> nxt;
            nxt.reserve(states.size());
            for (auto st : states) {
                if (apply_query(st, x, y)) nxt.push_back(std::move(st));
            }
            states.swap(nxt);
            continue;
        }

        int x = choose_query(states);
        int y = ask(x);

        vector<State> nxt;
        nxt.reserve(states.size());
        for (auto st : states) {
            if (apply_query(st, x, y)) nxt.push_back(std::move(st));
        }
        states.swap(nxt);
    }

    int A = get_alive_a(states)[0];

    // A가 정해지면 B는 정확한 거리 질의로 이분탐색
    int lo = 1;
    int hi = getH(A) + 1;

    while (hi - lo > 1) {
        int mid = (lo + hi) / 2;
        int x = x_for_exact_distance(A, mid);
        int y = ask(x);

        if (y == mid) lo = mid;
        else hi = mid;
    }

    finish_answer(A, hi);
}
