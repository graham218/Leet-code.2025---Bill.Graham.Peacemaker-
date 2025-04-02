def can_jump_greedy_1(nums):
    """
    Approach 1: Basic Greedy Approach

    This is the most straightforward greedy solution.  We iterate through the array,
    keeping track of the furthest reachable index.  If we ever reach an index
    that we can't reach, we return False.

    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    n = len(nums)
    max_reach = 0  # Furthest index reachable
    for i in range(n):
        if i > max_reach:  # If current index is beyond our reach, we can't win
            return False
        max_reach = max(max_reach, i + nums[i])  # Update furthest reachable
    return True

def can_jump_greedy_2(nums):
    """
    Approach 2: Optimized Greedy Approach

    This is a slightly optimized version of the greedy approach. Instead of checking `i > max_reach`
    in every iteration, we check it after updating `max_reach`. This can potentially reduce the
    number of checks, although the time complexity remains the same.

    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    n = len(nums)
    max_reach = 0
    for i in range(n):
        max_reach = max(max_reach, i + nums[i])
        if i == max_reach and i < n - 1 and nums[i] == 0:
            return False
        if max_reach >= n - 1:
            return True
    return max_reach >= n - 1

def can_jump_greedy_3(nums):
    """
    Approach 3:  Greedy - Backward Iteration

    This approach iterates backward from the end of the array.  It tracks the
    leftmost "good" position (a position from which the end can be reached).
    If we reach the start of the array and it's a "good" position, we can win.

    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    n = len(nums)
    last_good_pos = n - 1  # Last good position is initially the end
    for i in range(n - 2, -1, -1):  # Iterate backwards
        if i + nums[i] >= last_good_pos:
            last_good_pos = i  # Update leftmost good position
    return last_good_pos == 0  # If the first position is good, we can win

def can_jump_dp_4(nums):
    """
    Approach 4: Dynamic Programming (Top-Down with Memoization)

    This approach uses dynamic programming with memoization (top-down).
    It's less efficient than the greedy approaches, but demonstrates a different
    problem-solving technique.  We use a `memo` array to store whether
    each position is reachable.

    Time Complexity: O(n^2)  (in the worst case)
    Space Complexity: O(n)
    """
    n = len(nums)
    memo = [0] * n  # 0: unknown, 1: good, -1: bad
    memo[n - 1] = 1  # Last position is always reachable

    def can_reach(index):
        if memo[index] != 0:
            return memo[index] == 1  # Return True if good, False if bad

        max_jump = min(index + nums[index], n - 1)  # Max jump from current index
        for next_pos in range(index + 1, max_jump + 1):
            if can_reach(next_pos):  # If any next position is reachable
                memo[index] = 1  # Current position is also reachable
                return True
        memo[index] = -1  # Otherwise, current position is not reachable
        return False

    return can_reach(0)

def can_jump_dp_5(nums):
    """
    Approach 5: Dynamic Programming (Bottom-Up)

    This approach uses dynamic programming with a bottom-up approach.
    We build up a table of reachable positions from the end of the array
    to the beginning.

    Time Complexity: O(n^2)
    Space Complexity: O(n)
    """
    n = len(nums)
    reachable = [False] * n
    reachable[n - 1] = True  # Last position is reachable

    for i in range(n - 2, -1, -1):
        for j in range(i + 1, min(i + nums[i], n - 1) + 1):
            if reachable[j]:
                reachable[i] = True
                break  # Important optimization: No need to check further if reachable
    return reachable[0]

def can_jump_optimized(nums):
    """
    Approach 6: Optimized Solution (variation of Greedy Approach 2)

    This method optimizes the greedy approach by combining the updating of max_reach and the check
    if the current index is greater than max_reach into a single loop.  It's concise and efficient.

    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    n = len(nums)
    max_reach = 0
    for i in range(n):
        if i > max_reach:
            return False
        max_reach = max(max_reach, i + nums[i])
    return True
# Example Usage and Testing
if __name__ == "__main__":
    test_cases = [
        [2, 3, 1, 1, 4],
        [3, 2, 1, 0, 4],
        [0],
        [2, 0, 0],
        [2, 5, 0, 0],
        [1, 1, 1, 0, 0]
    ]

    for i, nums in enumerate(test_cases):
        print(f"\nTest Case {i+1}: nums = {nums}")
        print("-" * 30)

        result1 = can_jump_greedy_1(nums)
        print(f"Greedy Approach 1: {result1}")

        result2 = can_jump_greedy_2(nums)
        print(f"Greedy Approach 2: {result2}")

        result3 = can_jump_greedy_3(nums)
        print(f"Greedy Approach 3 (Backward): {result3}")

        result4 = can_jump_dp_4(nums)
        print(f"DP Approach 4 (Top-Down): {result4}")

        result5 = can_jump_dp_5(nums)
        print(f"DP Approach 5 (Bottom-Up): {result5}")

        result6 = can_jump_optimized(nums)
        print(f"Optimized Approach 6: {result6}")
