def can_jump_greedy(nums):
    """
    Greedy Approach:
    Iterate through the array, keeping track of the farthest reachable index.

    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    if not nums:
        return False  # Empty array, cannot jump

    max_reach = 0
    for i, num in enumerate(nums):
        if i > max_reach:
            return False  # Current index is beyond reach
        max_reach = max(max_reach, i + num)  # Update farthest reachable
        if max_reach >= len(nums) - 1:
            return True # Goal is reachable

    return True

def can_jump_dp_top_down(nums):
    """
    Dynamic Programming (Top-Down with Memoization):
    Use recursion with memoization to avoid redundant calculations.

    Time Complexity: O(n) - due to memoization
    Space Complexity: O(n) - for the memoization array and recursion stack
    """
    if not nums:
        return False

    n = len(nums)
    memo = [None] * n  # None: unvisited, True: reachable, False: unreachable
    memo[n - 1] = True  # Last index is always reachable

    def can_reach(index):
        if memo[index] is not None:
            return memo[index]  # Return memoized result

        if index >= n:  #Handle the case where index goes out of bound
            return False

        max_jump = nums[index]
        for jump in range(1, max_jump + 1):
            next_index = index + jump
            if next_index < n and can_reach(next_index):
                memo[index] = True
                return True

        memo[index] = False
        return False

    return can_reach(0)

def can_jump_dp_bottom_up(nums):
    """
    Dynamic Programming (Bottom-Up):
    Iterate from the end, determining reachability of each position.

    Time Complexity: O(n^2)
    Space Complexity: O(n)
    """
    if not nums:
        return False

    n = len(nums)
    reachable = [False] * n
    reachable[n - 1] = True  # Last index is reachable

    for i in range(n - 2, -1, -1):
        for j in range(1, nums[i] + 1):
            if i + j < n and reachable[i + j]:
                reachable[i] = True
                break  # Important: Optimization, no need to check further jumps

    return reachable[0]

def can_jump_recursive(nums):
    """
    Recursive Approach (without memoization):
    Explore all possible jump combinations.  This will exceed time limit for larger inputs

    Time Complexity: O(2^n) -  Exponential in the worst case
    Space Complexity: O(n) -  Due to the recursion stack
    """
    if not nums:
        return False

    def can_reach(index):
        if index == len(nums) - 1:
            return True  # Reached the last index

        if index >= len(nums): #Handle the case where index goes out of bound.
            return False

        max_jump = nums[index]
        for jump in range(1, max_jump + 1):
            if can_reach(index + jump):
                return True
        return False

    return can_reach(0)

def can_jump_optimized_greedy(nums):
    """
    Optimized Greedy Approach:
    Similar to the first greedy approach, but slightly optimized.

    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    if not nums:
        return False

    n = len(nums)
    if n <= 1:
        return True # if there is only one element, we are already there.

    max_reach = 0
    for i in range(n):
        if i > max_reach:
            return False
        max_reach = max(max_reach, i + nums[i])
        if max_reach >= n - 1:
            return True
    return False

# Example Usage and Testing:
if __name__ == "__main__":
    test_cases = [
        [2, 3, 1, 1, 4],
        [3, 2, 1, 0, 4],
        [0],
        [2, 0, 0],
        [2, 5, 0, 0], # Added test case
        [1, 1, 1, 1, 0]
    ]

    print("Jump Game Results:")
    for i, nums in enumerate(test_cases):
        print(f"\nTest Case {i+1}: nums = {nums}")

        # Greedy Approach
        result_greedy = can_jump_greedy(nums)
        print(f"Greedy Approach: {result_greedy}")

        # DP Top-Down
        result_dp_top_down = can_jump_dp_top_down(nums)
        print(f"DP (Top-Down): {result_dp_top_down}")

        # DP Bottom-Up
        result_dp_bottom_up = can_jump_dp_bottom_up(nums)
        print(f"DP (Bottom-Up): {result_dp_bottom_up}")

        # Recursive Approach
        result_recursive = can_jump_recursive(nums)
        print(f"Recursive: {result_recursive}")

        # Optimized Greedy
        result_optimized_greedy = can_jump_optimized_greedy(nums)
        print(f"Optimized Greedy: {result_optimized_greedy}")
