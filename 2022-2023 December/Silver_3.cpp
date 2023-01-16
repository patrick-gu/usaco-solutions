#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(void) {
    ll N;
    cin >> N;
    vector<vector<ll>> rs(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            rs[i].push_back(-1);
        }
        for (int j = i; j < N; j++) {
            ll r;
            cin >> r;
            rs[i].push_back(r);
        }
    }
    if (N == 1) {
        // cout << "0\n";
        return 0;
    }
    vector<ll> as = {0, rs[0][1]};
    for (int i = 2; i < N; i++) {
        if (i != as.size()) {
            while (1) {
            }
        }
        if (rs[i - 1][i] == 0) {
            as.push_back(as[i - 1]);
            continue;
        }
        ll added = as[i - 1] + rs[i - 1][i];
        ll subd = as[i - 1] - rs[i - 1][i];
        // cout << "w " << i << " " << added << " " << subd << "\n";
        bool addwork = max(max(added, as[i - 1]), as[i - 2]) -
                           min(min(added, as[i - 1]), as[i - 2]) ==
                       rs[i - 2][i];
        bool subwork = max(max(subd, as[i - 1]), as[i - 2]) -
                           min(min(subd, as[i - 1]), as[i - 2]) ==
                       rs[i - 2][i];
        if (addwork && subwork) {
            if (as[i - 2] != as[i - 1]) {
                // as.push_back(added);
                // goto OK;
                return SIGSEGV;
            }
            for (int j = i - 3; j >= 0; j--) {
                if (as[j] == as[j + 1]) {
                    continue;
                }
                bool addw1 = max(max(added, as[i - 1]), as[j]) -
                                 min(min(added, as[i - 1]), as[j]) ==
                             rs[j][i];
                bool subw1 = max(max(subd, as[i - 1]), as[j]) -
                                 min(min(subd, as[i - 1]), as[j]) ==
                             rs[j][i];
                if (addw1 && subw1) {
                    return SIGSEGV;
                    // as.push_back(added);
                    // goto OK;
                }
                if (addw1) {
                    as.push_back(added);
                    goto OK;
                } else if (subw1) {
                    as.push_back(subd);
                    goto OK;
                } else {
                    // as.push_back(added);
                    // goto OK;
                    // cout << "eeee\n";
                    return SIGSEGV;
                }
            }
            as.push_back(added);
        OK:;
        } else if (addwork) {
            as.push_back(added);
        } else if (subwork) {
            as.push_back(subd);
        } else {
            // cout << "aaaaa\n";
            return SIGSEGV;
        }
    }
    ll maxx = *max_element(as.begin(), as.end());
    ll red = maxx > 1000000000LL ? 1000000000LL - maxx : 0;
    for (int i = 0; i + 1 < as.size(); i++) {
        cout << as[i] - red << " ";
    }
    cout << as.back() - red << "\n";
    // for (ll l : as)
    //     cout << l << " ";
    // cout << "\n";

    // shift to range
}