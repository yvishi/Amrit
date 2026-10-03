#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int x, a, b;
        cin >> x >> a >> b;
        // Below 80%: a sec/percent up to 80, then 20 percent at b sec each.
        // At or above 80%: only b sec/percent up to 100.
        int ans = (x < 80) ? (80 - x) * a + 20 * b
                           : (100 - x) * b;
        cout << ans << '\n';
    }
    return 0;
}
