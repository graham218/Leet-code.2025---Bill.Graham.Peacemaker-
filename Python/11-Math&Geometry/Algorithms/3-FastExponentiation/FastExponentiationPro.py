import time

def fast_exponentiation_iterative(base, exponent):
    """
    Iterative implementation of fast exponentiation.  This is the most common
    and generally preferred method in real-world applications due to its
    efficiency and minimal memory usage.

    Args:
        base: The base number (can be an integer or a float).
        exponent: The exponent (non-negative integer).

    Returns:
        The result of base raised to the power of exponent.

    Time Complexity: O(log n), where n is the exponent.
    Space Complexity: O(1) - constant space.

    Real-world applications:
    - Cryptography (e.g., RSA algorithm)
    - Scientific computing
    - Financial calculations
    """
    result = 1
    while exponent > 0:
        if exponent % 2 == 1:
            result *= base
        exponent //= 2
        base *= base
    return result

def fast_exponentiation_recursive(base, exponent):
    """
    Recursive implementation of fast exponentiation.  While elegant,
    it's generally less preferred in production code compared to the
    iterative version due to the overhead of recursive function calls
    and the risk of stack overflow for very large exponents.

    Args:
        base: The base number.
        exponent: The exponent (non-negative integer).

    Returns:
        The result of base raised to the power of exponent.

    Time Complexity: O(log n), where n is the exponent.
    Space Complexity: O(log n) due to the recursive call stack.

     Real-world applications:
     -  Teaching and educational purposes.
     -  Situations where code clarity is highly prioritized and the
        exponent is guaranteed to be within reasonable bounds.
    """
    if exponent == 0:
        return 1
    if exponent == 1:
        return base
    if exponent % 2 == 0:
        half_power = fast_exponentiation_recursive(base, exponent // 2)
        return half_power * half_power
    else:
        return base * fast_exponentiation_recursive(base, exponent - 1)

def fast_exponentiation_memoization(base, exponent, memo={}):
    """
    Recursive implementation with memoization.  This addresses the
    stack overflow issue of the pure recursive version by storing
    intermediate results.  It's a good balance between recursion
    and efficiency, suitable for cases where the same base and
    exponent combinations are frequently encountered.

    Args:
        base: The base number.
        exponent: The exponent (non-negative integer).
        memo: A dictionary to store previously computed results.

    Returns:
        The result of base raised to the power of exponent.

    Time Complexity: O(log n), where n is the exponent (due to memoization).
    Space Complexity: O(log n) for the memoization dictionary.

    Real-world applications:
    - Dynamic programming problems
    - Caching of expensive power calculations
    - Optimization of repetitive computations
    """
    if exponent == 0:
        return 1
    if exponent == 1:
        return base

    if (base, exponent) in memo:
        return memo[(base, exponent)]

    if exponent % 2 == 0:
        half_power = fast_exponentiation_memoization(base, exponent // 2, memo)
        result = half_power * half_power
        memo[(base, exponent)] = result
        return result
    else:
        result = base * fast_exponentiation_memoization(base, exponent - 1, memo)
        memo[(base, exponent)] = result
        return result

def fast_exponentiation_binary_method(base, exponent):
    """
    Iterative implementation using the binary representation of the
    exponent.  This is another highly efficient and commonly used
    approach, often considered synonymous with the iterative method.
    It explicitly shows how the exponent's binary form drives the calculation.

    Args:
        base: The base number.
        exponent: The exponent (non-negative integer).

    Returns:
        The result of base raised to the power of exponent.

    Time Complexity: O(log n), where n is the exponent.
    Space Complexity: O(1) - constant space.

    Real-world applications:
    - Embedded systems (efficient use of resources)
    - High-performance computing
    - Cryptography
    """
    result = 1
    power = base
    while exponent > 0:
        if exponent & 1:  # Check if the least significant bit is 1
            result *= power
        exponent >>= 1  # Right shift the exponent
        power *= power
    return result

def fast_exponentiation_builtin(base, exponent):
    """
    Utilizes Python's built-in exponentiation operator (**).  This is
    often the simplest and most concise way to perform exponentiation
    in Python.  The underlying implementation is highly optimized
    and often uses a fast exponentiation algorithm.

    Args:
        base: The base number.
        exponent: The exponent (non-negative integer).

    Returns:
        The result of base raised to the power of exponent.

    Time Complexity: O(log n) in most Python implementations.
    Space Complexity: O(1) - constant space.

    Real-world applications:
    - General-purpose programming
    - Rapid prototyping
    - Scripting
    - Most general Python use cases where performance is not the *absolute* top priority
    """
    return base ** exponent

def fast_exponentiation_optimized_for_small_exponent(base, exponent):
    """
    Optimized for scenarios where the exponent is likely to be small.
    This method uses a simple loop for small exponents, which can be
    faster than the more complex logarithmic methods for very small n.
    For larger exponents, it falls back to the iterative method.

    Args:
        base: The base number.
        exponent: The exponent (non-negative integer).

    Returns:
        The result of base raised to the power of exponent.

    Time Complexity: O(n) for small exponents, O(log n) for larger exponents
    Space Complexity: O(1)

    Real-world applications:
    - Situations where the exponent is statistically likely to be small
    - Performance tuning for specific use cases
    - Microcontroller applications
    """
    if 0 <= exponent <= 3: # Optimized for exponents 0, 1, 2, and 3
        result = 1
        for _ in range(exponent):
            result *= base
        return result
    else:
        return fast_exponentiation_iterative(base, exponent) # Fallback to the iterative method

if __name__ == "__main__":
    # Example usage and demonstration
    base = 2
    exponents = [3, 10, 100, 1000, 10000] # Test with different sized exponents

    for exponent in exponents:
        print(f"\nBase: {base}, Exponent: {exponent}")

        start_time = time.time()
        result_iterative = fast_exponentiation_iterative(base, exponent)
        time_taken_iterative = time.time() - start_time
        print(f"Iterative Result: {result_iterative}, Time: {time_taken_iterative:.6f} seconds")

        start_time = time.time()
        result_recursive = fast_exponentiation_recursive(base, exponent)
        time_taken_recursive = time.time() - start_time
        print(f"Recursive Result: {result_recursive}, Time: {time_taken_recursive:.6f} seconds")

        start_time = time.time()
        result_memo = fast_exponentiation_memoization(base, exponent)
        time_taken_memo = time.time() - start_time
        print(f"Memoization Result: {result_memo}, Time: {time_taken_memo:.6f} seconds")

        start_time = time.time()
        result_binary = fast_exponentiation_binary_method(base, exponent)
        time_taken_binary = time.time() - start_time
        print(f"Binary Method Result: {result_binary}, Time: {time_taken_binary:.6f} seconds")

        start_time = time.time()
        result_builtin = fast_exponentiation_builtin(base, exponent)
        time_taken_builtin = time.time() - start_time
        print(f"Built-in Result: {result_builtin}, Time: {time_taken_builtin:.6f} seconds")

        start_time = time.time()
        result_optimized = fast_exponentiation_optimized_for_small_exponent(base, exponent)
        time_taken_optimized = time.time() - start_time
        print(f"Optimized Result: {result_optimized}, Time: {time_taken_optimized:.6f} seconds")


    # Example with a different base
    base = 1.5
    exponent = 5
    print(f"\nBase: {base}, Exponent: {exponent}")
    result = fast_exponentiation_iterative(base, exponent)
    print(f"Iterative Result: {result:.6f}")  # Output: 7.593750

