#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        long long c;
        cin >> n >> c;
        vector<int> p(n + 1);
        vector<long long> a(n + 1);
        for (int i = 1; i <= n; i++) cin >> p[i];
        for (int i = 1; i <= n; i++) cin >> a[i];

        vector<char> vis(n + 1, 0);
        long long ans = 0;
        for (int i = 1; i <= n; i++) {
            if (vis[i]) continue;
            // Per cycle: fix everyone (k-1 swaps) or fix only those with a > c (1 swap each).
            long long S = 0, pos = 0, k = 0;
            for (int j = i; !vis[j]; j = p[j]) {
                vis[j] = 1;
                S += a[j];
                pos += max(0LL, a[j] - c);
                k++;
            }
            ans += max(S - (k - 1) * c, pos);
        }
        cout << ans << '\n';
    }
    return 0;
}
