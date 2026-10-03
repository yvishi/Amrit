// Independent O(n * k^2) checker for curios.cpp, for mid-sized n where the
// brute force is too slow. It does not use the phase argument: it tracks the set
// of reachable (state of bag A, state of bag B) pairs, where a state is FREE
// (no glass yet) or the remaining budget 0..k of the bag's lowest glass.
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        string s;
        cin >> n >> k >> s;

        const int FREE = k + 1;  // states 0..k are budgets, k+1 means "no glass yet"
        const int S = k + 2;
        vector<char> cur(S * S, 0), nxt(S * S);
        cur[FREE * S + FREE] = 1;

        // Returns the new state of a bag after dropping curio c into it, or -1.
        auto put = [&](int state, char c) {
            if (state == FREE) return c == 'G' ? k : FREE;
            int w = c == 'G' ? 1 : 2;
            return state >= w ? state - w : -1;
        };

        for (char c : s) {
            fill(nxt.begin(), nxt.end(), 0);
            for (int a = 0; a < S; a++)
                for (int b = 0; b < S; b++) {
                    if (!cur[a * S + b]) continue;
                    int na = put(a, c), nb = put(b, c);
                    if (na >= 0) nxt[na * S + b] = 1;
                    if (nb >= 0) nxt[a * S + nb] = 1;
                }
            swap(cur, nxt);
        }

        bool ok = any_of(cur.begin(), cur.end(), [](char x) { return x; });
        cout << (ok ? "YES" : "NO") << '\n';
    }
}
