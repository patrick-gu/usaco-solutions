#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(void) {
    ll N, M;
    cin >> N >> M;
    // I don't know why, but I have to do this
    if (N <= 16) {
        vector<pair<int, int>> ps;
        for (int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            ps.push_back({u - 1, v - 1});
        }
        vector<unordered_set<int>> eds(N);
        for (auto [u, v] : ps) {
            eds[u].insert(v);
            eds[v].insert(u);
        }
        set<pair<int, int>> q;
        for (int i = 0; i < N; i++) {
            q.insert({eds[i].size(), i});
        }
        ll best = 0;
        for (int i = 1; q.size(); i++) {
            while (q.size()) {
                auto [edc, n] = *q.begin();
                if (edc >= i) break;
                q.erase(q.begin());
                for (int adj : eds[n]) {
                    q.erase(q.find({eds[adj].size(), adj}));
                    eds[adj].erase(eds[adj].find(n));
                    q.insert({eds[adj].size(), adj});
                }
                eds[n].clear();
            }
            vector<int> ids(N, -1);
            int acc = 1;
            int biggest = 0;
            for (auto [edc, n] : q) {
                if (ids[n] != -1) continue;
                int acc1 = 0;
                deque<int> q1;
                q1.push_back(n);
                while (q1.size()) {
                    int cur = q1.front();
                    q1.pop_front();
                    if (ids[cur] != -1) {
                        if (ids[cur] != acc) return SIGSEGV;
                        continue;
                    }
                    ids[cur] = acc;
                    acc1++;
                    for (int adj : eds[cur]) {
                        q1.push_back(adj);
                    }
                }
                biggest = max(biggest, acc1);

                acc++;
            }
            best = max(best, ((ll)biggest) * ((ll)i));
        }
        cout << best << "\n";
    } else {
        vector<pair<int, int>> ps;
        for (int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            ps.push_back({u - 1, v - 1});
        }
        vector<unordered_set<int>> eds(N);
        for (auto [u, v] : ps) {
            eds[u].insert(v);
            eds[v].insert(u);
        }
        ll best = 0;

        vector<set<pair<int, int>>> qs(1);
        for (int i = 0; i < N; i++) {
            qs[0].insert({eds[i].size(), i});
        }

        for (int i = 1; qs.size(); i++) {
            vector<set<pair<int, int>>> qs1;
            vector<int> ids(N, -1);
            ll biggest = 0;
            for (auto& q : qs) {
                bool mod = 0;
                while (q.size()) {  // at most O(N)
                    auto [edc, n] = *q.begin();
                    if (edc >= i) break;
                    mod = 1;
                    q.erase(q.begin());
                    for (int adj : eds[n]) {  // O(M) total
                        q.erase(q.find({eds[adj].size(), adj}));
                        eds[adj].erase(eds[adj].find(n));
                        q.insert({eds[adj].size(), adj});
                    }
                    eds[n].clear();
                }
                if (!q.size()) continue;
                if (!mod) {
                    qs1.push_back(q);
                    biggest = max(biggest, (ll)q.size());
                    continue;
                }
                int acc = 0;
                for (auto [edc, n] : q) {  // O(N) each
                    if (ids[n] != -1) continue;
                    int acc1 = 0;
                    deque<int> q1;
                    q1.push_back(n);
                    set<pair<int, int>> q2;
                    while (q1.size()) {
                        int cur = q1.front();
                        q1.pop_front();
                        if (ids[cur] != -1) {
                            if (ids[cur] != acc) return SIGSEGV;
                            continue;
                        }
                        ids[cur] = acc;
                        acc1++;
                        q2.insert({eds[cur].size(), cur});
                        for (int adj : eds[cur]) {
                            q1.push_back(adj);
                        }
                    }
                    biggest = max(biggest, (ll)acc1);

                    acc++;
                    qs1.push_back(q2);
                }
            }

            qs = qs1;
            best = max(best, ((ll)biggest) * ((ll)i));
        }
        cout << best << "\n";
    }
}