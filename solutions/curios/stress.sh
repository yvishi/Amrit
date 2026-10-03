#!/usr/bin/env bash
# Cross-checks curios.cpp against the brute force (small n) and the O(n*k^2) DP (larger n).
set -euo pipefail
cd "$(dirname "$0")"
BUILD=${BUILD:-$(mktemp -d)}
mkdir -p "$BUILD"

for f in curios brute dp; do
    g++ -O2 -std=c++17 -Wall -Wextra -o "$BUILD/$f" "$f.cpp"
done

check() {  # check <reference> <description> <gen args...>
    local ref=$1 desc=$2
    shift 2
    python3 gen.py "$@" > "$BUILD/in.txt"
    "$BUILD/curios" < "$BUILD/in.txt" > "$BUILD/out.txt"
    "$BUILD/$ref" < "$BUILD/in.txt" > "$BUILD/ref.txt"
    if ! cmp -s "$BUILD/out.txt" "$BUILD/ref.txt"; then
        echo "MISMATCH vs $ref on: $desc (input in $BUILD/in.txt)"
        exit 1
    fi
    echo "ok   $desc vs $ref: $(head -1 "$BUILD/in.txt") tests, $(grep -c YES "$BUILD/out.txt") YES"
}

check brute "exhaustive n<=12" all 12
for seed in 1 2 3 4 5; do
    check brute "random n<=18 seed $seed" rand "$seed" 300 18
done
for seed in 1 2 3 4 5; do
    check dp "random n<=120 seed $seed" rand "$seed" 300 120
done
echo "all checks passed"
