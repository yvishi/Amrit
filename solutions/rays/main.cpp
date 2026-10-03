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
        vector<pair<int, int>> p(n);
        for (auto &[x, y] : p) cin >> x >> y;
        sort(p.begin(), p.end());
        vector<int> y(n);
        for (int i = 0; i < n; i++) y[i] = p[i].second;

        // suf[k]: y[k..n-1] is increasing
        vector<char> suf(n + 1, 1);
        for (int i = n - 2; i >= 0; i--) suf[i] = suf[i + 1] && y[i] < y[i + 1];

        // Down-left points (D) must be exactly {points <= some c}; everything else is up-right (U).
        // Both groups must be increasing chains. Try every c = point k in x-order.
        set<int> seen;
        long long LO = LLONG_MIN, HI = LLONG_MAX, mx = LLONG_MIN;
        bool ok = false;
        for (int k = 0; k < n && !ok; k++) {
            int v = y[k];
            // every inversion in the prefix must straddle v; suffix goes to U and must
            // be increasing and lie above the prefix's U part
            if (LO < v && v < HI && suf[k + 1] && (k == n - 1 || mx < v || mx < y[k + 1]))
                ok = true;
            auto it = seen.upper_bound(v);
            if (it != seen.end()) {
                LO = max(LO, (long long)v);
                HI = min(HI, (long long)*it);
            }
            seen.insert(v);
            mx = max(mx, (long long)v);
        }
        cout << (ok ? "YES" : "NO") << '\n';
    }
    return 0;
}
