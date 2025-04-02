import math
import numpy as np
from itertools import compress
from multiprocessing import Pool

def sieve_basic(n):
    """Basic Sieve of Eratosthenes"""
    primes = [True] * (n + 1)
    primes[0], primes[1] = False, False
    for i in range(2, int(n**0.5) + 1):
        if primes[i]:
            for j in range(i * i, n + 1, i):
                primes[j] = False
    return [i for i, is_prime in enumerate(primes) if is_prime]


def sieve_optimized(n):
    """Optimized Sieve: Skips even numbers after 2"""
    if n < 2:
        return []
    primes = [True] * (n + 1)
    primes[0], primes[1] = False, False
    for i in range(4, n + 1, 2):
        primes[i] = False
    for i in range(3, int(n**0.5) + 1, 2):
        if primes[i]:
            primes[i * i: n + 1: i * 2] = [False] * len(range(i * i, n + 1, i * 2))
    return [i for i, is_prime in enumerate(primes) if is_prime]


def sieve_numpy(n):
    """Using NumPy for efficient array processing"""
    if n < 2:
        return []
    primes = np.ones(n + 1, dtype=bool)
    primes[:2] = False
    for i in range(2, int(n**0.5) + 1):
        if primes[i]:
            primes[i * i:n + 1:i] = False
    return np.nonzero(primes)[0].tolist()


def sieve_bitset(n):
    """Using a boolean bitset approach with itertools.compress"""
    if n < 2:
        return []
    primes = [True] * (n + 1)
    primes[0], primes[1] = False, False
    for i in range(2, int(math.sqrt(n)) + 1):
        if primes[i]:
            primes[i * i:n + 1:i] = [False] * len(range(i * i, n + 1, i))
    return list(compress(range(n + 1), primes))


def segmented_sieve(limit):
    """Segmented Sieve of Eratosthenes for large numbers"""
    prime_list = sieve_basic(int(math.sqrt(limit)))
    primes = []
    low, high = 2, limit
    segment = [True] * (high - low + 1)
    for p in prime_list:
        start = max(p * p, (low + p - 1) // p * p)
        for j in range(start, high + 1, p):
            segment[j - low] = False
    primes.extend([low + i for i in range(high - low + 1) if segment[i]])
    return primes


def mark_non_primes(start, n, base_primes):
    """Marks non-primes in a segment starting from 'start'."""
    segment = [True] * ((n - start) + 1)
    for p in base_primes:
        begin = max(p * p, (start + p - 1) // p * p)
        for j in range(begin, n + 1, p):
            segment[j - start] = False
    return [start + i for i, is_prime in enumerate(segment) if is_prime]


def parallel_sieve(n):
    """Parallelized sieve using multiprocessing"""
    base_primes = sieve_basic(int(math.sqrt(n)))

    step = n // 4  # Divide work into 4 segments
    ranges = [(i, min(i + step, n)) for i in range(2, n, step)]

    with Pool() as pool:
        result = pool.starmap(mark_non_primes, [(r[0], r[1], base_primes) for r in ranges])

    return [2] + sorted(set(base_primes + [num for sublist in result for num in sublist]))


# Display outputs for a sample range
n = 100
print("Basic Sieve:", sieve_basic(n))
print("Optimized Sieve:", sieve_optimized(n))
print("NumPy Sieve:", sieve_numpy(n))
print("Bitset Sieve:", sieve_bitset(n))
print("Segmented Sieve:", segmented_sieve(n))
print("Parallel Sieve:", parallel_sieve(n))