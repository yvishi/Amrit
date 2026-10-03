// Curios: glass (weight 1) / iron (weight 2), two bags, a glass breaks if the
// weight above it ever exceeds k.
//
// Key observation: inside one bag, only the lowest glass matters. Every glass
// placed later in the same bag has strictly less weight above it. So each bag is
//   * free:   no glass yet, so anything put in costs nothing, or
//   * active: remaining budget r = k - (weight placed after its first glass).
//
// Phase 1: before the first glass, both bags are free and irons cost nothing.
// Phase 2: the first glass activates bag A (budget k) while bag B stays free.
//          Every iron goes to B for free (putting it in A only wastes budget).
//          Every glass either goes to A (budget - 1) or activates B (budget k).
// Phase 3: both bags are active with budgets rA, rB, and order no longer
//          matters. The remaining c1 glasses and c2 irons fit iff
//              c1 + 2*c2 <= rA + rB   and   c2 <= rA/2 + rB/2.
//
// So try every glass as "the one that activates B", plus "B is never
// activated". O(n) per test case.
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

        vector<int> glass;
        for (int i = 0; i < n; i++)
            if (s[i] == 'G') glass.push_back(i);
        int m = glass.size();

        vector<int> ironsAfter(n + 1, 0);
        for (int i = n - 1; i >= 0; i--) ironsAfter[i] = ironsAfter[i + 1] + (s[i] == 'I');

        // B never gets a glass: every glass after the first one lands in A.
        bool ok = m <= 1 || m - 1 <= k;

        // glass[0] activates A, glass[j] activates B, glass[1..j-1] went into A.
        for (int j = 1; j < m && !ok; j++) {
            int usedA = j - 1;
            if (usedA > k) break;
            int rA = k - usedA, rB = k;
            int c1 = m - 1 - j;
            int c2 = ironsAfter[glass[j] + 1];
            if (c1 + 2 * c2 <= rA + rB && c2 <= rA / 2 + rB / 2) ok = true;
        }

        cout << (ok ? "YES" : "NO") << '\n';
    }
}
