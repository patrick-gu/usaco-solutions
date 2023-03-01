#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(void) {
    int N, Q;
    cin >> N >> Q;
    string lr;
    cin >> lr;
    string spec;
    cin >> spec;
    vector<bool> spec1;
    for (char c : spec)
        spec1.push_back(c == '1');

    vector<int> las, ras, assoc;
    for (int i = 0; i < N * 2; i++)
        if (lr[i] == 'L') {
            assoc.push_back(las.size());
            las.push_back(i);
        } else {
            assoc.push_back(ras.size());
            ras.push_back(i);
        }

    vector<vector<int>> sp(N, vector<int>(N, INT_MAX));
    for (int i = 0; i < N; i++) {
        sp[i][i] = 0;
        for (int j = i; j < N; j++) {
            for (int k = j + 1; k < N && las[k] < ras[j]; k++) {
                sp[i][k] = min(sp[i][k], sp[i][j] + 1);
            }
        }
    }

    while (Q--) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        int ans = spec1[a] + spec1[b];
        int len = sp[a][b];
        for (int i = a + 1; i < b; i++) {
            if (spec1[i] && (sp[a][i] + sp[i][b] == len)) {
                ans++;
            }
        }
        cout << len << " " << ans << "\n";
    }
}