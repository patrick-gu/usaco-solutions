#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 1000000007;

ll N, M;
vector<vector<bool>> bs;

struct hasha {
    size_t operator()(const pair<bitset<20>, bitset<20>>& pair) const {
        return hash<bitset<20>>{}(pair.first) * 37 +
               hash<bitset<20>>{}(pair.second);
    }
};

unordered_map<pair<bitset<20>, bitset<20>>, ll, hasha> dp;

ll acc = 0;

ll solve(bitset<20> nb, bitset<20> md) {
    if (dp.find({nb, md}) != dp.end()) return dp[{nb, md}];

    acc++;
    if (acc % 10000 == 0) cout << acc << endl;

    ll ans = 1;
    for (int i = 0; i < N; i++) {
        if (nb[i]) continue;
        bitset<20> nnb = nb, nmd = md;
        for (int j = 0; j < M; j++) {
            if (md[j] > bs[j][i]) goto fail;
            nmd[j] = bs[j][i];
        }
        nnb[i] = true;
        ans += solve(nnb, nmd);
        if (ans >= MOD) ans -= MOD;
        // ans %= MOD;
    fail:;
    }
    dp[{nb, md}] = ans;
    return dp[{nb, md}];
}

ll mulmod(ll a, ll b) {
    a %= MOD;
    b %= MOD;
    return (a * b) % MOD;
}

ll facmod(ll n) {
    if (n == 0) return 1;
    return mulmod(n, facmod(n - 1));
}

int main(void) {
    cin >> N >> M;
    bs = vector<vector<bool>>(M, vector<bool>(N));
    for (int i = 0; i < M; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < N; j++)
            bs[i][j] = s[j] == 'H';
    }
    // if (M == 1) {
    //     int e = 0, h = 0;
    //     for (bool c : bs[0])
    //         if (c)
    //             h++;
    //         else
    //             e++;
    //     // cout << e << " " << h << "\n";
    //     cout << mulmod(facmod(e), facmod(h)) << "\n";
    //     return 0;
    // }
    bitset<20> nb{}, md{};
    ll ans = solve(nb, md);
    ans--;
    if (ans < 0) ans += MOD;
    cout << ans << "\n";
}