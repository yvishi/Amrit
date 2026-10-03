#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int m = 3 * n;
        vector<long long> a(m);
        for (auto &v : a) cin >> v;
        sort(a.rbegin(), a.rend());
        vector<long long> P(m + 1, 0);
        for (int i = 0; i < m; i++) P[i + 1] = P[i] + a[i];

        // n1 teams scored as 6x, n2 as 4x+4y, the rest as 3(x+y+z).
        // Weights 6,4,3 go to the largest ratings in that order.
        auto f = [&](int n1, int n2) {
            return 2 * P[n1] + P[n1 + 2 * n2] + 3 * P[m - 2 * n1 - n2];
        };

        long long ans = LLONG_MIN;
        for (int n1 = 0; n1 <= n; n1++) {
            // f is concave in n2: binary search for its peak
            int lo = 0, hi = n - n1;
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                if (f(n1, mid + 1) > f(n1, mid)) lo = mid + 1;
                else hi = mid;
            }
            ans = max(ans, f(n1, lo));
        }
        cout << ans << '\n';
    }
    return 0;
}
