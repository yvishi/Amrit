#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;
const int N = 200001;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // inv[i] = i^{-1} mod p, H[i] = 1 + 1/2 + ... + 1/i mod p
    vector<long long> inv(N + 1), H(N + 1, 0);
    inv[1] = 1;
    for (int i = 2; i <= N; i++) inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    for (int i = 1; i <= N; i++) H[i] = (H[i - 1] + inv[i]) % MOD;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        long long ans = 0;
        for (int j = 1; j <= n; j++) {
            long long a;
            cin >> a;
            // expected number of merges a_j takes part in = H(j-1) + H(n-j)
            ans = (ans + a % MOD * ((H[j - 1] + H[n - j]) % MOD)) % MOD;
        }
        cout << ans << '\n';
    }
    return 0;
}
