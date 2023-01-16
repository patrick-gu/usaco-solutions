#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(void) {
    ll N;
    cin >> N;
    vector<ll> cc;
    for (int i = 0; i < N; i++) {
        ll c;
        cin >> c;
        cc.push_back(c);
    }
    sort(cc.begin(), cc.end());
    ll best = 0;
    ll bestt = 0;
    for (ll i = N - 1; i >= 0; i--) {
        ll cur = (N - i) * cc[i];
        if (cur >= best) {
            best = cur;
            bestt = cc[i];
        }
    }
    cout << best << " " << bestt << "\n";
}