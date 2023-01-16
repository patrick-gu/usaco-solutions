#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(void) {
    ll T;
    cin >> T;
    while (T--) {
        ll N, K;
        cin >> N >> K;
        string s;
        cin >> s;
        string ans(N, '.');
        int acc = 0;
        for (int i = 0; i < N;) {
            if (s[i] == 'G') {
                acc++;
                int opt = i + K;
                if (opt >= N) {
                    ans.back() = 'G';
                    break;
                }
                ans[opt] = 'G';
                i = opt + K + 1;

            } else {
                i++;
            }
        }
        for (int i = 0; i < N;) {
            if (s[i] == 'H') {
                acc++;
                int opt = i + K;
                if (opt >= N - 1) {
                    if (ans.back() == 'G') {
                        if (ans[ans.size() - 2] == 'G') {
                            while (1) {
                            }
                        }
                        ans[ans.size() - 2] = 'H';

                    } else {
                        ans.back() = 'H';
                    }
                    break;
                }
                // if (ans[opt] == 'G') {
                //     int j = opt - 1;
                //     while (1) {
                //     }
                // }
                ans[opt] = 'H';
                i = opt + K + 1;
            } else {
                i++;
            }
        }

        // int gs = -1, hs = -1;
        // int acc = 0;
        // string ans;
        for (int i = 0; i < N; i++) {
            // if (s[i] == 'G') {
            //     if (gs < i) {
            //         gs = i + K;
            //         acc++;
            //         ans.push_back('G');
            //     } else {
            //         ans.push_back('.');
            //     }
            // } else {
            //     if (hs < i) {
            //         hs = i + K;
            //         acc++;
            //         ans.push_back('H');
            //     } else {
            //         ans.push_back('.');
            //     }
            // }
        }
        cout << acc << "\n" << ans << "\n";
    }
}