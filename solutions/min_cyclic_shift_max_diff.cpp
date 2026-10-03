// Minimum over cyclic shifts of max |b_i - b_{i+1}|.
// View a as a cycle with n edges |a_i - a_{(i+1) mod n}|. A cyclic shift
// removes exactly one edge (the wrap-around), so the best shift drops the
// largest edge: answer = second largest cyclic edge. O(n) per test.
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
        vector<long long> a(n);
        for (auto &x : a) cin >> x;
        long long m1 = -1, m2 = -1;
        for (int i = 0; i < n; i++) {
            long long d = llabs(a[i] - a[(i + 1) % n]);
            if (d > m1) m2 = m1, m1 = d;
            else if (d > m2) m2 = d;
        }
        cout << m2 << '\n';
    }
}
