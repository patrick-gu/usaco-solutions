#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<int> sieve(5000050, true);

bool isprime(int n) {
    return sieve[n];
}

int main(void) {
    sieve[0] = sieve[1] = 0;
    for (int i = 2; i < 5000050; i++) {
        if (sieve[i]) {
            for (int j = i * 2; j < 5000050; j += i) {
                sieve[j] = 0;
            }
        }
    }

    set<int> mod3pr;
    for (int i = 3; i < 5000050; i += 4) {
        if (isprime(i)) {
            mod3pr.insert(i);
        }
    }

    set<int> mod1pr;
    for (int i = 5; i < 5000050; i += 4) {
        if (isprime(i)) {
            mod1pr.insert(i);
        }
    }

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> as;
        for (int i = 0; i < N; i++) {
            int a;
            cin >> a;
            as.push_back(a);
        }

        bool outcome = false;
        bool loseable = false;
        int shortlose = INT_MAX;
        int shortloseat = 0;
        for (int i = 0; i < N; i++) {
            if (as[i] % 4 == 0) {
                loseable = true;
                if (as[i] == 0) {
                    outcome = 0;
                    goto done;
                }
            }
        }
        if (!loseable) {
            outcome = 1;
            goto done;
        }
        for (int i = 0; i < N; i++) {
            if (as[i] % 4 == 0) {
                if ((as[i] / 2) < shortlose) {
                    shortlose = as[i] / 2;
                    shortloseat = i;
                }
            }
        }

        outcome = 0;
        for (int i = 0; i < N; i++) {
            // cout << "i " << i << " " << as[i] << "\n";
            if (as[i] % 4 == 0) {
                continue;
            }
            int win = 0;
            if (as[i] <= 3) {
                win = 1;
            }
            if (as[i] % 4 == 2) {
                win = as[i] / 2;
            } else if (as[i] % 4 == 1) {
                auto it = mod1pr.upper_bound(as[i]);
                it--;
                // cout << "sel " << (*it) << "\n";
                win = (as[i] - (*it)) / 2 + 1;
            } else if (as[i] % 4 == 3) {
                auto it = mod3pr.upper_bound(as[i]);
                it--;
                win = (as[i] - (*it)) / 2 + 1;
            }
            // cout << "w " << win << "\n";
            if (win % 2 == 0) {
                // cout << "fail\n";
                // return SIGSEGV;
                while (1) {
                }
            }
            if (i < shortloseat) {
                if (win - 1 <= shortlose) {
                    outcome = 1;
                    break;
                }
            } else {
                if (shortlose > win) {
                    outcome = 1;
                    break;
                }
            }
        }

        goto done;
    done:
        if (outcome)
            cout << "Farmer John\n";
        else
            cout << "Farmer Nhoj\n";
    }
}