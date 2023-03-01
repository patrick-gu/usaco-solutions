#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 1000000007;

ll np1c2(ll n) {
    return ((n % MOD) * ((n + 1) % MOD) / 2) % MOD;
}

ll mulmod(ll a, ll b) {
    a %= MOD;
    b %= MOD;
    return (a * b) % MOD;
}

int main(void) {
    ll U;
    cin >> U;

    vector<ll> qds(U), qbs(U);
    for (ll i = 0; i < U; i++) {
        cin >> qds[i] >> qbs[i];
    }

    vector<ll> uds = qds;
    sort(uds.begin(), uds.end());
    uds.erase(unique(uds.begin(), uds.end()), uds.end());

    if (U <= 5000) {
        vector<ll> pos = uds, len(uds.size());

        ll ans = 0;
        for (ll i = 0; i < U; i++) {
            ll d = qds[i], b = qbs[i];
            ll di = lower_bound(uds.begin(), uds.end(), d) - uds.begin();
            ans -= np1c2(len[di] - 1);
            ans %= MOD;
            ans -= mulmod(len[di], pos[di]);
            ans %= MOD;
            len[di] = b;
            ans += np1c2(len[di] - 1);
            ans %= MOD;
            ans += mulmod(len[di], pos[di]);
            ans %= MOD;
            for (ll j = di + 1; j < uds.size(); j++) {
                ll target =
                    j == 0 ? uds[j] : max(uds[j], pos[j - 1] + len[j - 1]);
                if (target == pos[j]) {
                    break;
                }
                ans += mulmod(target - pos[j], len[j]);
                ans %= MOD;
                pos[j] = target;
            }

            if (ans < 0) ans += MOD;
            cout << ans << "\n";
        }
        return 0;
    }

    multiset<pair<ll, ll>> rs;

    vector<ll> last(uds.size());
    ll ans = 0;
    for (int i = 0; i < U; i++) {
        ll d = qds[i], b = qbs[i];
        ll di = lower_bound(uds.begin(), uds.end(), d) - uds.begin();
        ll delta = b - last[di];
        // ans -= np1c2(last[di] - 1);
        //         ans -= mulmod(len[di], pos[di]);
        //         ans %= MOD;
        // ans %= MOD;
        last[di] = b;
        ans += np1c2(delta - 1);
        ans %= MOD;
        ans += mulmod(d, delta);
        ans %= MOD;
        // cout << "add " << np1c2(last[di] - 1) + mulmod(d, b) << "\n";
        if (rs.size() == 0) {
            rs.insert({d, d + delta - 1});
            if (ans < 0) ans += MOD;
            cout << ans << "\n";
            continue;
        }
        rs.insert({d, d + delta - 1});
        auto it = rs.upper_bound({d, d - 1});
        it--;
        for (;;) {
            if (it == rs.end()) break;
            auto it2 = it;
            it2++;
            if (it2 == rs.end()) break;
            auto [s1, e1] = *it;
            auto [s2, e2] = *it2;
            if (e1 >= s2) {
                // cout << "merge " << s1 << " " << e1 << " w " << s2 << " " <<
                // e2
                //      << "\n";
                ans += mulmod(e1 + 1 - s2, e2 - s2 + 1);
                ans %= MOD;
                rs.erase(rs.find({s1, e1}));
                rs.erase(rs.find({s2, e2}));
                rs.insert({s1, e1 + 1 - s2 + e2});
                it = rs.upper_bound({s1, s1 - 1});
            } else {
                break;
            }
        }
        it = rs.upper_bound({d, d - 1});
        // it--;
        for (;;) {
            if (it == rs.end()) break;
            auto it2 = it;
            it2++;
            if (it2 == rs.end()) break;
            auto [s1, e1] = *it;
            auto [s2, e2] = *it2;
            if (e1 >= s2) {
                // cout << "merge " << s1 << " " << e1 << " w " << s2 << " " <<
                // e2
                //      << "\n";
                ans += mulmod(e1 + 1 - s2, e2 - s2 + 1);
                ans %= MOD;
                rs.erase(rs.find({s1, e1}));
                rs.erase(rs.find({s2, e2}));
                rs.insert({s1, e1 + 1 - s2 + e2});
                it = rs.upper_bound({s1, s1 - 1});
            } else {
                break;
            }
        }
        if (ans < 0) ans += MOD;
        cout << ans << "\n";
        // auto it = rs.upper_bound({d, d});
        // if (it == rs.begin()) {
        // }
    }
}