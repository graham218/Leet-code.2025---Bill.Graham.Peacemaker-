def climbing_stairs_recursive(n: int) -> int:
    """
    Recursive solution to the Climbing Stairs problem.

    Args:
        n: The number of stairs.

    Returns:
        The number of distinct ways to climb to the top.

    This approach directly implements the recursive definition:
    - If n is 0, there's 1 way (staying at the top).
    - If n is 1, there's 1 way (taking one step).
    - Otherwise, the number of ways is the sum of the ways to reach (n-1)
      and (n-2) steps.

    Time Complexity: O(2^n) - Exponential (due to overlapping subproblems)
    Space Complexity: O(n) -  Maximum depth of the recursion tree
    """
    if n == 0:
        return 1
    if n == 1:
        return 1
    return climbing_stairs_recursive(n - 1) + climbing_stairs_recursive(n - 2)

def climbing_stairs_memoization(n: int) -> int:
    """
    Memoization (Top-Down Dynamic Programming) solution.

    Args:
        n: The number of stairs.

    Returns:
        The number of distinct ways to climb to the top.

    This approach improves upon the recursive solution by storing the results of
    subproblems in a memo (dictionary).  Before computing the result for a
    subproblem, it checks if the result is already stored.  This avoids
    redundant computations.

    Time Complexity: O(n) - Each subproblem is solved only once.
    Space Complexity: O(n) - O(n) for the memo and O(n) for the recursion stack.
    """
    memo = {}  # Initialize an empty dictionary to store results

    def climb(n):
        if n == 0:
            return 1
        if n == 1:
            return 1
        if n in memo:  # Check if the result is already memoized
            return memo[n]
        memo[n] = climb(n - 1) + climb(n - 2)  # Store the result in the memo
        return memo[n]

    return climb(n)


def climbing_stairs_tabulation(n: int) -> int:
    """
    Tabulation (Bottom-Up Dynamic Programming) solution.

    Args:
        n: The number of stairs.

    Returns:
        The number of distinct ways to climb to the top.

    This approach builds a table (list) of results for subproblems, starting
    from the base cases (n=0 and n=1) and iteratively computing the results
    for larger subproblems.  The final entry in the table is the result
    for the original problem (n).

    Time Complexity: O(n) - Iterates through the table once.
    Space Complexity: O(n) - Stores the results for each subproblem in the table.
    """
    if n == 0:
        return 1
    if n == 1:
        return 1
    dp = [0] * (n + 1)  # Create a table to store results
    dp[0] = 1  # Base case: 1 way to reach 0 stairs
    dp[1] = 1  # Base case: 1 way to reach 1 stair
    for i in range(2, n + 1):
        dp[i] = dp[i - 1] + dp[i - 2]  # Calculate ways to reach i stairs
    return dp[n]  # Result for n stairs


def climbing_stairs_optimized(n: int) -> int:
    """
    Optimized Tabulation solution (Constant Space).

    Args:
        n: The number of stairs.

    Returns:
        The number of distinct ways to climb to the top.

    This approach is a space-optimized version of the tabulation method.
    Instead of storing the results for all subproblems in a table, it
    only keeps track of the results for the two previous subproblems
    (n-1 and n-2), which are needed to compute the result for the
    current subproblem.  This reduces the space complexity from O(n) to O(1).

    Time Complexity: O(n) - Iterates n times.
    Space Complexity: O(1) - Uses only a constant amount of extra space.
    """
    if n == 0:
        return 1
    if n == 1:
        return 1
    prev1 = 1  # Represents ways to reach (i-1) stairs
    prev2 = 1  # Represents ways to reach (i-2) stairs
    for i in range(2, n + 1):
        current = prev1 + prev2  # Calculate ways to reach i stairs
        prev2 = prev1  # Update prev2
        prev1 = current  # Update prev1
    return prev1  # Result for n stairs

def climbing_stairs_matrix(n: int) -> int:
    """
    Matrix solution to the Climbing Stairs problem.  This approach leverages the
    fact that the number of ways to climb stairs can be represented using a matrix
    exponentiation.  While more complex to understand, it can be more efficient for
    very large values of n (though the difference isn't apparent for typical problem constraints).

    Args:
        n: The number of stairs.

    Returns:
        The number of distinct ways to climb to the top.

    The core idea is to represent the recurrence relation F(n) = F(n-1) + F(n-2)
    as a matrix multiplication:

    [F(n)    ]   =   [1  1]  * [F(n-1)]
    [F(n-1)  ]       [1  0]     [F(n-2)]

    Let M = [[1, 1], [1, 0]].  Then,

    [F(n)    ]   =   M^(n-1) * [F(1)]
    [F(n-1)  ]                  [F(0)]

    Where F(0) = 1 and F(1) = 1.  We can efficiently compute M^(n-1) using
    binary exponentiation.

    Time Complexity: O(log n) - Due to the matrix exponentiation.
    Space Complexity: O(1) - Uses a constant amount of extra space.
    """
    if n == 0:
        return 1
    if n == 1:
        return 1

    def matrix_multiply(A, B):
        """Multiplies two 2x2 matrices."""
        C = [[0, 0], [0, 0]]
        for i in range(2):
            for j in range(2):
                for k in range(2):
                    C[i][j] += A[i][k] * B[k][j]
        return C

    def matrix_power(M, p):
        """Computes M raised to the power p using binary exponentiation."""
        result = [[1, 0], [0, 1]]  # Identity matrix
        while p > 0:
            if p % 2 == 1:
                result = matrix_multiply(result, M)
            M = matrix_multiply(M, M)
            p //= 2
        return result

    M = [[1, 1], [1, 0]]  # The transformation matrix
    M_pow_n_minus_1 = matrix_power(M, n - 1)  # Compute M^(n-1)
    return M_pow_n_minus_1[0][0]  # F(n) is the top-left element of the resulting matrix



if __name__ == "__main__":
    test_cases = [0, 1, 2, 3, 4, 5, 6, 10, 20, 30] # Added more test cases
    for n in test_cases:
        print(f"Number of stairs: {n}")
        print(f"Recursive: {climbing_stairs_recursive(n)}")
        print(f"Memoization: {climbing_stairs_memoization(n)}")
        print(f"Tabulation: {climbing_stairs_tabulation(n)}")
        print(f"Optimized: {climbing_stairs_optimized(n)}")
        print(f"Matrix: {climbing_stairs_matrix(n)}")
        print("-" * 20)
