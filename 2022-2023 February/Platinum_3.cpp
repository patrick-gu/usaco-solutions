#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll N;
string s;
vector<set<ll>> es;
vector<ll> ps;

void setp(ll p) {
    for (ll c : es[p]) {
        if (c == ps[p]) continue;
        ps[c] = p;
        setp(c);
    }
}

vector<ll> dp1, dp0;
ll k;

ll solve0(ll p);

ll solve1(ll p) {
    if (dp1[p] != -1) return dp1[p];
    ll acc = 1LL + k;
    for (ll c : es[p]) {
        if (c == ps[p]) continue;
        acc += min(solve0(c), solve1(c) - k);
    }
    return dp1[p] = acc;
}

ll solve0(ll p) {
    if (dp0[p] != -1) return dp0[p];
    if (s[p] == '1') return dp0[p] = solve1(p);
    ll acc = 0;
    for (ll c : es[p]) {
        if (c == ps[p]) continue;
        acc += solve0(c);
    }
    return dp0[p] = min(solve1(p), acc);
}

int main(void) {
    cin >> N;
    cin >> s;
    es = vector<set<ll>>(N);
    for (ll i = 0; i < N - 1; i++) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        es[a].insert(b);
        es[b].insert(a);
    }
    ps = vector<ll>(N);
    ps[0] = -1;
    setp(0);
    dp1 = vector<ll>(N, -1), dp0 = vector<ll>(N, -1);
    for (k = 1; k <= N; k++) {
        dp1.assign(N, -1);
        dp0.assign(N, -1);
        cout << solve0(0) << "\n";
    }
}