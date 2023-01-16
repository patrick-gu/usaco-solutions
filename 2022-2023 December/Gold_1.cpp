#include <bits/stdc++.h>
using namespace std;

int N, A, B;
vector<int> ps;
vector<int> cs;
vector<int> xs;

vector<vector<vector<int>>> dp;

int solve(int fr, int mon, int con) {
    if (fr == N) return 0;
    // cout << "sol " << fr << " " << mon << " " << con << "\n";
    auto& sl = dp[fr][mon][con];
    if (sl != -1) return sl;
    int best = solve(fr + 1, mon, con);
    int x = xs[fr], p = ps[fr], c = cs[fr];
    for (int discount = c - min(c, mon);
         (discount <= c) && (discount * x <= con); discount++) {
        best = max(best,
                   p + solve(fr + 1, mon - c + discount, con - discount * x));
    }
    return sl = best;
}

int main(void) {
    cin >> N >> A >> B;
    for (int i = 0; i < N; i++) {
        int P, C, X;
        cin >> P >> C >> X;
        ps.push_back(P);
        cs.push_back(C);
        xs.push_back(X);
    }
    dp = vector<vector<vector<int>>>(
        N, vector<vector<int>>(A + 1, vector<int>(B + 1, -1)));
    cout << solve(0, A, B) << "\n";
}