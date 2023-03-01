#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<ll> gdp, hdp;

ll g(const vector<vector<int>>& cs, const vector<int>& cc, int n);

ll h(const vector<vector<int>>& cs, const vector<int>& cc, int n) {
    auto& v = hdp[n];
    if (v != -1) return v;
    if (cs[n].size() == 0) {
        return v = 1LL;
    }
    ll acc = cc[n];
    ll lc = LONG_LONG_MAX;
    for (int c : cs[n]) {
        ll gc = g(cs, cc, c);
        acc += gc;
        lc = min(lc, h(cs, cc, c) - (ll)cc[c] - gc);
    }
    if (lc > 0) exit(SIGSEGV);
    return v = acc + lc;
}

ll g(const vector<vector<int>>& cs, const vector<int>& cc, int n) {
    auto& v = gdp[n];
    if (v != -1) return v;

    // return v = h(cs, cc, n) + cc[n];

    if (cs[n].size() == 0) {
        // cout << "g(" << n << ")=" << (2) << "\n";
        return v = 2LL;
    }
    if (cs[n].size() == 1) {
        // cout << "g(" << n << ")=" << (2) << "\n";
        return v = g(cs, cc, cs[n][0]) + 2LL;
    }
    ll acc = cc[n] + 1;
    ll mm1 = LONG_LONG_MAX;
    ll mm2 = LONG_LONG_MAX;
    for (int c : cs[n]) {
        ll gc = g(cs, cc, c);
        acc += gc + (ll)cc[c];
        ll diff = h(cs, cc, c) - gc - (ll)cc[c];
        if (diff > 0) exit(SIGSEGV);
        if (diff <= mm1) {
            mm2 = mm1;
            mm1 = diff;
        } else if (diff < mm2) {
            mm2 = diff;
        }
    }
    ll ans = acc + mm1 + mm2;
    return v = ans;
    // cout << "g(" << n << ")=" << (acc + mm) << "\n";
    // return acc + mm;
}

void mkcc(vector<int>& cc, const vector<vector<int>>& cs, int cur) {
    cc[cur] = 1;
    for (int e : cs[cur]) {
        mkcc(cc, cs, e);
        cc[cur] += cc[e];
    }
    // cout << "cc " << cur << " " << cc[cur] << "\n";
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<int> ps(N);
    for (int i = 1; i < N; i++) {
        cin >> ps[i];
        ps[i]--;
    }
    ps[0] = -1;
    vector<vector<int>> cs(N);
    for (int i = 1; i < N; i++)
        cs[ps[i]].push_back(i);
    vector<int> cc(N);
    mkcc(cc, cs, 0);
    gdp = vector<ll>(N, -1);
    hdp = vector<ll>(N, -1);
    cout << g(cs, cc, 0) << "\n";
}