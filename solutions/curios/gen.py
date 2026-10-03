"""Test generator for curios.

  python3 gen.py all MAXN            every string of length 1..MAXN, every k in [1, 2n]
  python3 gen.py rand SEED T MAXN    T random tests with n <= MAXN, k in [1, 2n]
"""
import itertools
import random
import sys


def emit(tests):
    print(len(tests))
    for n, k, s in tests:
        print(n, k)
        print(s)


def main():
    mode = sys.argv[1]
    tests = []
    if mode == "all":
        max_n = int(sys.argv[2])
        for n in range(1, max_n + 1):
            for chars in itertools.product("GI", repeat=n):
                s = "".join(chars)
                tests.extend((n, k, s) for k in range(1, 2 * n + 1))
    else:
        seed, t, max_n = map(int, sys.argv[2:5])
        rng = random.Random(seed)
        for _ in range(t):
            n = rng.randint(1, max_n)
            p = rng.random()  # glass density varies a lot between tests
            s = "".join("G" if rng.random() < p else "I" for _ in range(n))
            # Small k is where the interesting cases are, but cover the full range too.
            k = rng.randint(1, min(2 * n, rng.choice([2, 4, 8, 2 * n])))
            tests.append((n, k, s))
    emit(tests)


if __name__ == "__main__":
    main()
