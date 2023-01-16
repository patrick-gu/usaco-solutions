#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(void) {
    ll T;
    cin >> T;
    while (T--) {
        ll N, M;
        cin >> N >> M;
        vector<pair<bitset<100>, bool>> ss;
        for (int i = 0; i < M; i++) {
            string s;
            cin >> s;
            string out;
            cin >> out;
            bitset<100> s1{};
            for (int j = 0; j < N; j++) {
                if (s[j] == '1') {
                    s1[j] = 1;
                }
            }
            ss.push_back({s1, out[0] == '1'});
        }
        vector<bool> checked(N);
        for (int i = 0; i < N; i++) {
            for (int bit = 0; bit < N; bit++) {
                if (!checked[bit]) {
                    int s1 = 0, s0 = 0, u1 = 0, u0 = 0;
                    for (int j = 0; j < ss.size(); j++) {
                        if (ss[j].first[bit]) {
                            if (ss[j].second) {
                                s1++;
                            } else {
                                s0++;
                            }
                        } else {
                            if (ss[j].second) {
                                u1++;
                            } else {
                                u0++;
                            }
                        }
                    }
                    if (!s0 || !s1) {
                        for (int j = 0; j < ss.size();) {
                            if (ss[j].first[bit]) {
                                ss.erase(ss.begin() + j);
                            } else {
                                j++;
                            }
                        }
                        checked[bit] = 1;
                        goto done1;
                    } else if (!u0 || !u1) {
                        for (int j = 0; j < ss.size();) {
                            if (!ss[j].first[bit]) {
                                ss.erase(ss.begin() + j);
                            } else {
                                j++;
                            }
                        }
                        checked[bit] = 1;
                        goto done1;
                    }
                }
            }
            break;
        done1:;
        }
        int o0 = 0, o1 = 0;
        for (int i = 0; i < ss.size(); i++) {
            if (ss[i].second)
                o1++;
            else
                o0++;
        }
        if (o0 && o1) {
            cout << "LIE\n";
        } else {
            cout << "OK\n";
        }
    }
}