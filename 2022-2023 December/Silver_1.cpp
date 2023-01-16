#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(void) {
    ll N;
    cin >> N;
    vector<ll> hs;
    for (ll i = 0; i < N; i++) {
        ll h;
        cin >> h;
        hs.push_back(h);
    }
    vector<pair<ll, ll>> rs;
    for (ll i = 0; i < N - 1; i++) {
        ll u, v;
        cin >> u >> v;
        u--;
        v--;
        rs.push_back({u, v});
    }
    vector<set<ll>> es(N);
    for (auto [u, v] : rs) {
        es[u].insert(v);
        es[v].insert(u);
    }
    ll each = accumulate(hs.begin(), hs.end(), 0LL) / N;
    deque<tuple<ll, ll, ll>> actspush;
    deque<tuple<ll, ll, ll>> actspull;
    set<pair<ll, ll>> nodeq;
    for (int i = 0; i < N; i++) {
        nodeq.insert({es[i].size(), i});
    }
    while (nodeq.size()) {
        auto [ecnt1, n1] = *nodeq.begin();
        ll ecnt = ecnt1;
        ll n = n1;
        nodeq.erase(nodeq.begin());
        if (ecnt == 0) {
            if (nodeq.size() > 0) return SIGSEGV;
            if (hs[n] != each) {
                while (1) {
                }
            }
            break;
        } else if (ecnt != 1 || es[n].size() != 1) {
            return SIGSEGV;
        }

        ll adj = *es[n].begin();
        es[n].clear();
        nodeq.erase(nodeq.find({es[adj].size(), adj}));
        es[adj].erase(es[adj].find(n));
        nodeq.insert({es[adj].size(), adj});
        if (hs[n] < each) {
            ll need = each - hs[n];
            actspull.push_front({adj, n, need});
            hs[n] = each;
            hs[adj] -= need;
        } else if (hs[n] > each) {
            ll surp = hs[n] - each;
            actspush.push_back({n, adj, surp});
            hs[n] = each;
            hs[adj] += surp;
        }
    }
    cout << actspush.size() + actspull.size() << "\n";
    for (auto [f, t, c] : actspush)
        cout << (f + 1) << " " << (t + 1) << " " << c << "\n";
    for (auto [f, t, c] : actspull)
        cout << (f + 1) << " " << (t + 1) << " " << c << "\n";
}