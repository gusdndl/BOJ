#include <bits/stdc++.h>
using namespace std;

int groupId = 0;

struct SegmentTree {
    int N, M;
    vector<int> tree;
    vector<int> lazy;
    vector<int> groups;
    unordered_map<int, int> mp;
    vector<int> parent;

    SegmentTree(int N, int M) : N(N), M(M), tree(4*N, 0), lazy(4*N, 0), parent(M+1) {
        for (int i = 0; i <= M; i++) parent[i] = i;
        groups.push_back(0);
        mp[0] = 0;
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int x, int y) {
        if (mp.find(y) == mp.end()) return;
        if (mp.find(x) == mp.end()) {
            groups.push_back(x);
            mp[x] = (int)groups.size() - 1;
        }
        int px = find(mp[x]);
        int py = find(mp[y]);
        if (px != py) parent[py] = px;
    }

    void updateLazy(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] = lazy[node];
            if (start != end) {
                lazy[node*2]   = lazy[node];
                lazy[node*2+1] = lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void update(int node, int start, int end, int left, int right, int val) {
        updateLazy(node, start, end);
        if (left > end || right < start) return;
        if (left <= start && end <= right) {
            tree[node] = val;
            if (start != end) {
                lazy[node*2]   = val;
                lazy[node*2+1] = val;
            }
            return;
        }
        update(node*2,   start,           (start+end)/2, left, right, val);
        update(node*2+1, (start+end)/2+1, end,           left, right, val);
        tree[node] = max(tree[node*2], tree[node*2+1]);
    }

    int query(int node, int start, int end, int idx) {
        updateLazy(node, start, end);
        if (idx < start || idx > end) return 0;
        if (start == end) return tree[node];
        int lval = query(node*2,   start,           (start+end)/2, idx);
        int rval = query(node*2+1, (start+end)/2+1, end,           idx);
        return max(lval, rval);
    }

    int query(int x) {
        return find(query(1, 1, N, x));
    }

    int getGroupId(int x) {
        return groups[query(x)];
    }

    void move(int x, int newGroup) {
        if (mp.find(x) == mp.end()) return;
        int idx      = find(mp[x]);
        int oldGroup = groups[idx];
        groups[idx]  = newGroup;
        mp.erase(oldGroup);
        mp[newGroup] = idx;
    }

    void move(int left, int right, int newGroup) {
        groups.push_back(newGroup);
        int newIdx   = (int)groups.size() - 1;
        mp[newGroup] = newIdx;
        update(1, 1, N, left, right, newIdx);
    }
};

vector<int> convert(const string& s) {
    vector<int> res(s.size());
    for (int i = 0; i < (int)s.size(); i++) {
        res[i] = s[i] - 'a';
    }
    return res;
}

vector<string> solution(string s, vector<string> query) {
    vector<int> codes = convert(s);
    int N = (int)codes.size();
    int M = (int)query.size();

    vector<SegmentTree> stArr;
    stArr.reserve(26);
    for (int i = 0; i < 26; i++) {
        stArr.emplace_back(N, M);
    }

    vector<string> answer;

    for (const string& q : query) {
        istringstream iss(q);
        vector<string> tokens;
        string token;
        while (iss >> token) tokens.push_back(token);

        const string& type = tokens[0];

        if (type == "1") {
            int x      = stoi(tokens[1]);
            int y      = stoi(tokens[2]);
            int groupX = stArr[codes[x-1]].getGroupId(x);
            int groupY = stArr[codes[y-1]].getGroupId(y);
            answer.push_back(groupX == groupY ? "YES" : "NO");

        } else if (type == "2") {
            int x = stoi(tokens[1]);
            vector<int> word = convert(tokens[2]);
            unordered_set<int> set(word.begin(), word.end());

            int groupX = stArr[codes[x-1]].getGroupId(x);
            groupId++;
            for (int ch : set) {
                stArr[ch].move(groupX, groupId);
            }

        } else if (type == "3") {
            int x = stoi(tokens[1]);
            int y = stoi(tokens[2]);
            vector<int> word = convert(tokens[3]);
            unordered_set<int> set(word.begin(), word.end());

            groupId++;
            for (int ch : set) {
                stArr[ch].move(x, y, groupId);
            }

        } else if (type == "4") {
            int x = stoi(tokens[1]);
            int y = stoi(tokens[2]);

            int groupX = stArr[codes[x-1]].getGroupId(x);
            int groupY = stArr[codes[y-1]].getGroupId(y);

            if (groupX > groupY) swap(groupX, groupY);

            for (SegmentTree& st : stArr) {
                st.unite(groupX, groupY);
            }

        } else if (type == "5") {
            vector<string> list;
            vector<vector<int>> arr(groupId+1, vector<int>(26, 0));

            for (int i = 1; i <= N; i++) {
                int alpha  = codes[i-1];
                int groupI = stArr[alpha].getGroupId(i);
                arr[groupI][alpha]++;
            }

            for (auto& cnt : arr) {
                string sb;
                for (int i = 0; i < 26; i++) {
                    if (cnt[i] > 0) {
                        sb += (char)('a' + i);
                        sb += ' ';
                        sb += to_string(cnt[i]);
                        sb += ' ';
                    }
                }
                if (!sb.empty()) {
                    sb.pop_back();
                    list.push_back(sb);
                }
            }

            for (const string& item : list) answer.push_back(item);
        }
    }

    return answer;
}