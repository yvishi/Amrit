#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<char> has(n + 1, 0);
        for (int i = 0; i < m; i++) {
            int x;
            cin >> x;
            has[x] = 1;
        }

        // first/last cloud and the largest run of uncovered fields between clouds
        long long first = -1, last = -1, G = 0;
        for (int i = 1; i <= n; i++) {
            if (!has[i]) continue;
            if (first < 0) first = i;
            else G = max(G, (long long)i - last - 1);
            last = i;
        }

        // Shift range visited is [-L, R]; need L >= A, R >= B, L + R >= G.
        // A walk covering [-L, R] costs L + R + min(L, R).
        long long A = first - 1, B = n - last;
        long long ans = min(2 * A + max(B, G - A),   // go left first
                            2 * B + max(A, G - B));  // go right first
        cout << ans << '\n';
    }
    return 0;
}
