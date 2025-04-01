"""
You are climbing a staircase. It takes n steps to reach the top.
Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

Constraints:
    1 <= n <= 45

Example 1:
    Input: n = 2
    Output: 2
    Explanation: There are two ways to climb to the top.
    1. 1 step + 1 step
    2. 2 steps

Example 2:
    Input: n = 3
    Output: 3
    Explanation: There are three ways to climb to the top.
    1. 1 step + 1 step + 1 step
    2. 1 step + 2 steps
    3. 2 steps + 1 step
"""

import time
from functools import lru_cache

def climbing_stairs_recursive(n: int) -> int:
    """
    1. Recursive Approach (Plain Recursion)
    - Time Complexity: O(2^n) - Exponential, very slow for larger n.
    - Space Complexity: O(n) - Depth of the recursion tree.
    - Real-world application: Demonstrating basic recursion, good for teaching,
      but not efficient for practical applications.  Could be used in a very
      limited scenario where n is guaranteed to be small, like a simple
      configuration setting with very few options.
    """
    if n == 1:
        return 1
    if n == 2:
        return 2
    return climbing_stairs_recursive(n - 1) + climbing_stairs_recursive(n - 2)

def climbing_stairs_memoization(n: int) -> int:
    """
    2. Memoization (Top-Down Dynamic Programming)
    - Time Complexity: O(n) - Each subproblem is solved only once.
    - Space Complexity: O(n) -  O(n) for the memoization cache and O(n) for recursion stack.
    - Real-world application: Optimizing recursive functions that have
      overlapping subproblems.  For example, in a complex workflow
      engine where tasks depend on previous tasks, memoization can be
      used to cache the results of expensive task calculations,
      preventing redundant computations when the same task is encountered
      multiple times in the workflow.
    """
    memo = {}  # Initialize a dictionary to store computed results

    def _climb(n):
        if n == 1:
            return 1
        if n == 2:
            return 2
        if n in memo:
            return memo[n]  # Return result if already computed
        memo[n] = _climb(n - 1) + _climb(n - 2)  # Compute and store
        return memo[n]

    return _climb(n)

def climbing_stairs_tabulation(n: int) -> int:
    """
    3. Tabulation (Bottom-Up Dynamic Programming)
    - Time Complexity: O(n) - Iterative solution with a single loop.
    - Space Complexity: O(n) - Uses a table (list) of size n+1.
    - Real-world application:  Efficiently solving optimization problems
      where the solution can be built up from smaller subproblems.
      For example, in financial modeling, calculating the optimal
      investment strategy over a period of time can use tabulation
      to store and reuse the optimal solutions for shorter time periods,
      leading to the optimal solution for the entire period.
    """
    if n == 1:
        return 1
    if n == 2:
        return 2
    dp = [0] * (n + 1)  # Create a table to store results
    dp[1] = 1
    dp[2] = 2
    for i in range(3, n + 1):
        dp[i] = dp[i - 1] + dp[i - 2]  # Build up the solution
    return dp[n]

def climbing_stairs_optimized(n: int) -> int:
    """
    4. Optimized Tabulation (Constant Space)
    - Time Complexity: O(n) - Iterative solution with a single loop.
    - Space Complexity: O(1) - Uses only a few variables.
    - Real-world application:  Any scenario where memory usage is a critical
      constraint, such as in embedded systems or mobile devices with
      limited RAM.  For example, calculating Fibonacci numbers (which has
      the same recurrence relation) in a low-memory environment for
      generating a sequence of values for a display or control system.
    """
    if n == 1:
        return 1
    if n == 2:
        return 2
    a = 1  # Represents dp[i-2]
    b = 2  # Represents dp[i-1]
    for i in range(3, n + 1):
        temp = a + b  # Calculate dp[i]
        a = b      # Update for the next iteration
        b = temp
    return b

def climbing_stairs_matrix(n: int) -> int:
    """
    5. Matrix Method (Advanced)
    - Time Complexity: O(log n) - Uses matrix exponentiation.
    - Space Complexity: O(1) - Uses a constant amount of space.
    - Real-world application:  Efficiently calculating terms in linear
      recurrence relations, such as Fibonacci numbers or, in this case,
      climbing stairs.  This can be useful in applications where these
      sequences are used, and performance is critical, such as in
      algorithmic trading, where quick calculation of financial
      indicators based on recurrence relations is necessary.  Useful when
      'n' is very large.
    """
    def matrix_multiply(A, B):
        C = [[0, 0], [0, 0]]
        for i in range(2):
            for j in range(2):
                for k in range(2):
                    C[i][j] += A[i][k] * B[k][j]
        return C

    def matrix_power(M, n):
        if n == 0:
            return [[1, 0], [0, 1]]  # Identity matrix
        if n == 1:
            return M
        result = matrix_power(M, n // 2)
        result = matrix_multiply(result, result)
        if n % 2 == 1:
            result = matrix_multiply(result, M)
        return result

    if n <= 2:
        return n
    M = [[1, 1], [1, 0]]
    result_matrix = matrix_power(M, n - 1)
    return result_matrix[0][0]

def climbing_stairs_lru_cache(n: int) -> int:
    """
    6. Using lru_cache (Memoization with Decorator)
    - Time Complexity: O(n) - Each subproblem is solved only once.
    - Space Complexity: O(n) -  O(n) for the cache
    - Real-world application:  Simplifying memoization in any function
      that has overlapping subproblems.  For example, in a web application
      that calculates complex user statistics, @lru_cache can be used to
      automatically cache the results of these calculations based on
      user ID and other parameters, improving performance and reducing
      database load.
    """
    @lru_cache(maxsize=None)  # Use a decorator for memoization
    def _climb(n):
        if n == 1:
            return 1
        if n == 2:
            return 2
        return _climb(n - 1) + _climb(n - 2)

    return _climb(n)

if __name__ == "__main__":
    n = 10  # Number of stairs

    print(f"Climbing Stairs with {n} steps:")
    print("-" * 30)

    # 1. Recursive Approach
    start_time = time.time()
    result_recursive = climbing_stairs_recursive(n)
    end_time = time.time()
    print(f"1. Recursive: {result_recursive}, Time: {end_time - start_time:.6f} seconds")

    # 2. Memoization
    start_time = time.time()
    result_memoization = climbing_stairs_memoization(n)
    end_time = time.time()
    print(f"2. Memoization: {result_memoization}, Time: {end_time - start_time:.6f} seconds")

    # 3. Tabulation
    start_time = time.time()
    result_tabulation = climbing_stairs_tabulation(n)
    end_time = time.time()
    print(f"3. Tabulation: {result_tabulation}, Time: {end_time - start_time:.6f} seconds")

    # 4. Optimized Tabulation
    start_time = time.time()
    result_optimized = climbing_stairs_optimized(n)
    end_time = time.time()
    print(f"4. Optimized: {result_optimized}, Time: {end_time - start_time:.6f} seconds")

    # 5. Matrix Method
    start_time = time.time()
    result_matrix = climbing_stairs_matrix(n)
    end_time = time.time()
    print(f"5. Matrix: {result_matrix}, Time: {end_time - start_time:.6f} seconds")

    # 6. LRU Cache
    start_time = time.time()
    result_lru_cache = climbing_stairs_lru_cache(n)
    end_time = time.time()
    print(f"6. LRU Cache: {result_lru_cache}, Time: {end_time - start_time:.6f} seconds")
