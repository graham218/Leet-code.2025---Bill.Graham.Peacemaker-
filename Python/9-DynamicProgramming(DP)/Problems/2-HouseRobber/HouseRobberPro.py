"""
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed,
the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected
and it will automatically contact the police if two adjacent houses were robbed on the same night.

Given a list of non-negative integers representing the amount of money in each house, determine the maximum amount of
money you can rob tonight without alerting the police.

Example 1:
Input: [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
             Total amount you can rob = 1 + 3 = 4.

Example 2:
Input: [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2) and then rob house 3 (money = 9).
             Total amount you can rob = 2 + 9 = 11.
             Or rob house 0 (money = 2) and house 2 (money = 9) and house 4 (money = 1).
             Total amount you can rob = 2 + 9 + 1 = 12.

Constraints:
0 <= nums.length <= 100
0 <= nums[i] <= 400
"""
from typing import List

class HouseRobber:
    """
    A class containing multiple solutions to the House Robber problem,
    demonstrating different dynamic programming approaches.
    """

    def __init__(self):
        pass  # No initialization needed for this class

    def rob_recursive_memoization(self, nums: List[int]) -> int:
        """
        1. Recursive Approach with Memoization (Top-Down DP)

        This approach uses recursion to explore all possible combinations of robbing houses.
        To avoid redundant calculations, it employs memoization (a dictionary called `memo`)
        to store the maximum amount of money that can be robbed starting from each house.

        Args:
            nums: A list of integers representing the amount of money in each house.

        Returns:
            The maximum amount of money that can be robbed.

        Time Complexity: O(n), where n is the number of houses.  Each subproblem (each house)
                         is solved only once due to memoization.
        Space Complexity: O(n) for the memoization dictionary and O(n) for the recursion call stack.
        """
        memo = {}  # Dictionary to store results of subproblems

        def _rob(i):
            if i < 0:
                return 0  # Base case: no houses left
            if i == 0:
                return nums[0] # Base case: one house
            if i in memo:
                return memo[i]  # Return memoized result if available

            # Calculate the maximum of two choices:
            # 1. Rob the current house (nums[i]) and the houses before the previous one (i-2)
            # 2. Skip the current house and rob the houses before the current one (i-1)
            memo[i] = max(_rob(i - 2) + nums[i], _rob(i - 1))
            return memo[i]

        return _rob(len(nums) - 1)  # Start recursion from the last house

    def rob_iterative_dp_array(self, nums: List[int]) -> int:
        """
        2. Iterative Approach with DP Array (Bottom-Up DP)

        This approach uses a dynamic programming array `dp` to store the maximum amount of money
        that can be robbed up to each house.  It iteratively builds the solution from the
        base cases (first one or two houses) to the final solution (all houses).

        Args:
            nums: A list of integers representing the amount of money in each house.

        Returns:
            The maximum amount of money that can be robbed.

        Time Complexity: O(n), where n is the number of houses.  The loop iterates n times.
        Space Complexity: O(n) for the DP array `dp`.
        """
        if not nums:
            return 0  # Empty array, no houses to rob
        if len(nums) <= 2:
            return max(nums) # Handle 1 or 2 houses

        dp = [0] * len(nums)  # DP array to store maximum robbed amounts
        dp[0] = nums[0]  # Base case: max rob for the first house
        dp[1] = max(nums[0], nums[1])  # Base case: max rob for the first two houses

        for i in range(2, len(nums)):
            # Calculate the maximum of two choices:
            # 1. Rob the current house (nums[i]) and the houses before the previous one (i-2)
            # 2. Skip the current house and rob the houses before the current one (i-1)
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1])

        return dp[-1]  # The last element of dp is the result for all houses

    def rob_iterative_optimized(self, nums: List[int]) -> int:
        """
        3. Iterative Approach with Optimized Space (Constant Space DP)

        This approach is similar to the iterative DP array approach, but it optimizes
        the space complexity by using only two variables (`prev1` and `prev2`) to store
        the necessary intermediate results, instead of an entire array.

        Args:
            nums: A list of integers representing the amount of money in each house.

        Returns:
            The maximum amount of money that can be robbed.

        Time Complexity: O(n), where n is the number of houses.  The loop iterates n times.
        Space Complexity: O(1).  Only two variables are used.
        """
        if not nums:
            return 0  # Empty array, no houses to rob
        if len(nums) <= 2:
            return max(nums) # Handle 1 or 2 houses

        prev1 = nums[0]  # Max rob for the first house
        prev2 = max(nums[0], nums[1])  # Max rob for the first two houses

        for i in range(2, len(nums)):
            # Calculate the maximum of two choices:
            # 1. Rob the current house (nums[i]) and the houses before the previous one (prev1)
            # 2. Skip the current house and rob the houses before the current one (prev2)
            current = max(prev1 + nums[i], prev2)
            prev1 = prev2  # Update prev1 to the previous prev2
            prev2 = current  # Update prev2 to the current result

        return prev2  # The final prev2 holds the result for all houses

    def rob_recursive_optimized(self, nums: List[int]) -> int:
        """
        4. Recursive Approach with Optimized State Variables

        This approach uses recursion, but instead of a memoization table, it passes
        the results of the previous two states (prev1, prev2) as arguments to the
        recursive function.  This eliminates the need for extra space for memoization
        and avoids the overhead of dictionary lookups.

        Args:
            nums: A list of integers representing the amount of money in each house.

        Returns:
            The maximum amount of money that can be robbed.

        Time Complexity: O(n). Each house is visited at most once.
        Space Complexity: O(n) in the worst case due to the recursion depth.  In best case O(1).
        """

        def _rob(i, prev1, prev2):
            if i < 0:
                return prev1
            if i == 0:
                return max(prev1, nums[0])

            # Calculate the maximum of two choices:
            # 1. Rob the current house (nums[i]) and the houses before the previous one (prev1)
            # 2. Skip the current house and rob the houses before the current one (prev2)
            current = max(prev1 + nums[i], prev2)
            return _rob(i - 1, prev2, current)

        if not nums:
            return 0
        return _rob(len(nums) - 1, 0, 0)  # Start recursion with initial values

    def rob_with_interval(self, nums: List[int]) -> int:
        """
        5. Rob with Interval

        This approach divides the problem into two subproblems:
        1. Rob the houses from 0 to n-2 (excluding the last house).
        2. Rob the houses from 1 to n-1 (excluding the first house).
        The maximum of the two results is the final answer.  This approach handles
        edge cases effectively and can be useful in scenarios where the first
        and last houses have a special relationship (e.g., they are adjacent in a circular street).

        Args:
            nums: A list of integers representing the amount of money in each house.

        Returns:
            The maximum amount of money that can be robbed.
        """
        def _rob_interval(sub_nums):
            """Helper function to rob a sub-interval of houses."""
            if not sub_nums:
                return 0
            if len(sub_nums) <= 2:
                return max(sub_nums)

            dp = [0] * len(sub_nums)
            dp[0] = sub_nums[0]
            dp[1] = max(sub_nums[0], sub_nums[1])
            for i in range(2, len(sub_nums)):
                dp[i] = max(dp[i - 2] + sub_nums[i], dp[i - 1])
            return dp[-1]

        if not nums:
            return 0
        if len(nums) == 1:
            return nums[0]

        # Rob houses excluding the last house, and excluding the first house.
        return max(_rob_interval(nums[:-1]), _rob_interval(nums[1:]))

    def rob_with_start_end(self, nums: List[int], start: int, end: int) -> int:
        """
        6. Rob with Start and End Indices (Generalized Interval Robbing)

        This is a generalization of the "Rob with Interval" approach.  It allows
        you to specify the start and end indices of the houses to be considered.
        This is useful if you want to rob a specific segment of houses within a larger
        array, which might be the case in more complex scenarios or when dealing with
        subproblems in a divide-and-conquer strategy.

        Args:
            nums: A list of integers representing the amount of money in each house.
            start: The starting index of the houses to rob (inclusive).
            end: The ending index of the houses to rob (inclusive).

        Returns:
            The maximum amount of money that can be robbed within the specified interval.
        """
        if start > end:
            return 0  # Invalid interval
        if start == end:
            return nums[start]  # Only one house in the interval
        if end - start == 1:
            return max(nums[start], nums[end]) # Only two houses

        dp = [0] * (end - start + 1)  # DP array for the interval
        dp[0] = nums[start]  # Base case for the first house in the interval
        dp[1] = max(nums[start], nums[start + 1])  # Base case for the first two houses

        for i in range(2, end - start + 1):
            # Calculate the maximum of two choices:
            # 1. Rob the current house and the houses before the previous one
            # 2. Skip the current house and rob the houses before the current one
            dp[i] = max(dp[i - 2] + nums[start + i], dp[i - 1])
        return dp[-1]

def main():
    """
    Main function to demonstrate the House Robber solutions with example inputs.
    """
    robber = HouseRobber()  # Create an instance of the HouseRobber class
    houses1 = [1, 2, 3, 1]
    houses2 = [2, 7, 9, 3, 1]
    houses3 = [2, 1, 4, 5, 3, 1, 1, 9] # Added test case
    houses4 = [] # Empty list
    houses5 = [5] # Single element list

    print("Example 1: houses = [1, 2, 3, 1]")
    print(f"1. Recursive with Memoization: {robber.rob_recursive_memoization(houses1)}")
    print(f"2. Iterative DP Array: {robber.rob_iterative_dp_array(houses1)}")
    print(f"3. Iterative Optimized: {robber.rob_iterative_optimized(houses1)}")
    print(f"4. Recursive Optimized: {robber.rob_recursive_optimized(houses1)}")
    print(f"5. Rob with Interval: {robber.rob_with_interval(houses1)}")
    print(f"6. Rob with Start/End: {robber.rob_with_start_end(houses1, 0, len(houses1) - 1)}")
    print("-" * 30)

    print("Example 2: houses = [2, 7, 9, 3, 1]")
    print(f"1. Recursive with Memoization: {robber.rob_recursive_memoization(houses2)}")
    print(f"2. Iterative DP Array: {robber.rob_iterative_dp_array(houses2)}")
    print(f"3. Iterative Optimized: {robber.rob_iterative_optimized(houses2)}")
    print(f"4. Recursive Optimized: {robber.rob_recursive_optimized(houses2)}")
    print(f"5. Rob with Interval: {robber.rob_with_interval(houses2)}")
    print(f"6. Rob with Start/End: {robber.rob_with_start_end(houses2, 0, len(houses2) - 1)}")
    print("-" * 30)

    print("Example 3: houses = [2, 1, 4, 5, 3, 1, 1, 9]")
    print(f"1. Recursive with Memoization: {robber.rob_recursive_memoization(houses3)}")
    print(f"2. Iterative DP Array: {robber.rob_iterative_dp_array(houses3)}")
    print(f"3. Iterative Optimized: {robber.rob_iterative_optimized(houses3)}")
    print(f"4. Recursive Optimized: {robber.rob_recursive_optimized(houses3)}")
    print(f"5. Rob with Interval: {robber.rob_with_interval(houses3)}")
    print(f"6. Rob with Start/End: {robber.rob_with_start_end(houses3, 0, len(houses3) - 1)}")
    print("-" * 30)

    print("Example 4: houses = []")
    print(f"1. Recursive with Memoization: {robber.rob_recursive_memoization(houses4)}")
    print(f"2. Iterative DP Array: {robber.rob_iterative_dp_array(houses4)}")
    print(f"3. Iterative Optimized: {robber.rob_iterative_optimized(houses4)}")
    print(f"4. Recursive Optimized: {robber.rob_recursive_optimized(houses4)}")
    print(f"5. Rob with Interval: {robber.rob_with_interval(houses4)}")
    print(f"6. Rob with Start/End: {robber.rob_with_start_end(houses4, 0, len(houses4) - 1)}")
    print("-" * 30)

    print("Example 5: houses = [5]")
    print(f"1. Recursive with Memoization: {robber.rob_recursive_memoization(houses5)}")
    print(f"2. Iterative DP Array: {robber.rob_iterative_dp_array(houses5)}")
    print(f"3. Iterative Optimized: {robber.rob_iterative_optimized(houses5)}")
    print(f"4. Recursive Optimized: {robber.rob_recursive_optimized(houses5)}")
    print(f"5. Rob with Interval: {robber.rob_with_interval(houses5)}")
    print(f"6. Rob with Start/End: {robber.rob_with_start_end(houses5, 0, len(houses5) - 1)}")
    print("-" * 30)

if __name__ == "__main__":
    main()
