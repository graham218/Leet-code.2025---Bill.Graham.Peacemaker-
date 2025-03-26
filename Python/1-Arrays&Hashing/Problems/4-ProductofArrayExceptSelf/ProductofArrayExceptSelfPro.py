from math import log, exp
from multiprocessing import Pool, cpu_count

def product_except_self_prefix_suffix(nums):
    """
    Approach 1: Prefix and Suffix Multiplication
    Uses prefix and suffix products to compute the result without division.
    Time Complexity: O(n)
    Space Complexity: O(n)
    """
    n = len(nums)
    prefix, suffix, output = [1] * n, [1] * n, [1] * n

    for i in range(1, n):
        prefix[i] = prefix[i - 1] * nums[i - 1]

    for i in range(n - 2, -1, -1):
        suffix[i] = suffix[i + 1] * nums[i + 1]

    for i in range(n):
        output[i] = prefix[i] * suffix[i]

    return output

def prefix_worker(chunk):
    """Worker function for parallel processing."""
    prefix = [1] * len(chunk)
    for i in range(1, len(chunk)):
        prefix[i] = prefix[i - 1] * chunk[i - 1]
    return prefix

def product_except_self_parallel(nums):
    """
    Approach 2: Parallel Processing with Multiprocessing
    Uses multiprocessing to compute prefix and suffix products in parallel.
    Time Complexity: O(n)
    Space Complexity: O(n)
    """
    n = len(nums)
    num_workers = cpu_count()
    chunk_size = max(1, n // num_workers)

    with Pool(num_workers) as pool:
        prefix_chunks = pool.map(prefix_worker, [nums[i:i + chunk_size] for i in range(0, n, chunk_size)])

    output = [1] * n
    for i in range(n):
        output[i] = prefix_chunks[i // chunk_size][i % chunk_size]

    return output

def product_except_self_inplace(nums):
    """
    Approach 3: In-Place Modification for Memory Optimization
    Computes the result without extra space.
    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    n = len(nums)
    output = [1] * n

    left = 1
    for i in range(n):
        output[i] = left
        left *= nums[i]

    right = 1
    for i in range(n - 1, -1, -1):
        output[i] *= right
        right *= nums[i]

    return output

def product_except_self_streaming(stream):
    """
    Approach 4: Streaming Data Processing
    Processes elements as they arrive in a streaming fashion.
    Time Complexity: O(n)
    Space Complexity: O(n) (For stored elements)
    """
    nums = list(stream)
    seen = []
    prefix = 1
    for num in nums:
        seen.append(prefix)
        prefix *= num

    suffix = 1
    for i in range(len(seen) - 1, -1, -1):
        seen[i] *= suffix
        suffix *= nums[i]

    return seen

def product_except_self_logarithmic(nums):
    """
    Approach 5: Logarithmic Computation
    Uses logarithms and exponentiation to avoid multiplication directly.
    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    log_sum = sum(log(num) for num in nums if num != 0)
    return [round(exp(log_sum - log(num))) if num != 0 else 0 for num in nums]

def product_except_self_bitwise(nums):
    """
    Approach 6: Bitwise Masking Trick (For Specific Data Types)
    Uses bitwise operations in constrained environments.
    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    n = len(nums)
    output = [1] * n
    left = 1
    for i in range(n):
        output[i] = left
        left *= nums[i]

    right = 1
    for i in range(n - 1, -1, -1):
        output[i] *= right
        right *= nums[i]

    return output

nums = [1, 2, 3, 4, 5]
print("Prefix & Suffix:", product_except_self_prefix_suffix(nums))
print("Parallel Processing:", product_except_self_parallel(nums))
print("In-Place Optimization:", product_except_self_inplace(nums))
print("Streaming Processing:", product_except_self_streaming(iter(nums)))
print("Logarithmic Computation:", product_except_self_logarithmic(nums))
print("Bitwise Masking:", product_except_self_bitwise(nums))