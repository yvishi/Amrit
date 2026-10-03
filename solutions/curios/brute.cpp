// Brute force for curios.cpp: try every bag assignment (2^(n-1), bag of the
// first curio fixed by symmetry) and compute the largest weight that ever sits
// above a glass. The answer is YES iff the best assignment needs at most k.
// Only usable for small n; results are cached per string so that many k values
// for the same string stay cheap.
#include <bits/stdc++.h>
using namespace std;

int minNeededK(const string& s) {
    int n = s.size();
    int best = INT_MAX;
    for (int mask = 0; mask < (1 << (n - 1)); mask++) {
        int above[2] = {0, 0}, need = 0;
        for (int i = n - 1; i >= 0; i--) {
            int bag = i == 0 ? 0 : (mask >> (i - 1)) & 1;
            if (s[i] == 'G') need = max(need, above[bag]);
            above[bag] += s[i] == 'G' ? 1 : 2;
        }
        best = min(best, need);
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unordered_map<string, int> memo;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        string s;
        cin >> n >> k >> s;
        auto it = memo.find(s);
        int need = it != memo.end() ? it->second : memo[s] = minNeededK(s);
        cout << (need <= k ? "YES" : "NO") << '\n';
    }
}
