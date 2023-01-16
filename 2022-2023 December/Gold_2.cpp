#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int N;
vector<ll> hs;

int main(void) {
    cin >> N;
    hs = vector<ll>(N);
    for (int i = 0; i < N; i++) {
        cin >> hs[i];
    }
    int Q;
    cin >> Q;
    vector<pair<ll, ll>> ups;
    for (int i = 0; i < Q; i++) {
        int x;
        ll y;
        cin >> x >> y;
        ups.push_back({x - 1, y});
    }

    for (auto [x, y] : ups) {
        hs[x] += y;

        ll acc = 0;
        for (ll i = 0; i < N; i++) {
            ll msy = -2000000LL, msx = 0;
            for (ll j = i + 1; j < N; j++) {
                if ((hs[j] - hs[i]) * msx >= msy * (j - i)) {
                    msy = hs[j] - hs[i];
                    msx = j - i;
                    acc++;
                }
            }
        }

        cout << acc << "\n";
    }
}