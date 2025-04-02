"""
Backtracking - Subsets: 6 Approaches with Real-World Project Implementations

Problem:
Given a set of distinct integers, nums, return all possible subsets (the power set).
The solution set must not contain duplicate subsets.

Explanation:
The power set of a set with n elements has 2^n subsets.  Each element can either
be present or absent in a subset.  We can use backtracking to explore all
possible combinations.

Real-World Applications:
1.  Feature Toggling:  In software development, you might have a set of features.
    Subsets represent different combinations of enabled features.
2.  Combinatorial Optimization:  Finding all possible combinations of options,
    like in resource allocation or experiment design.
3.  Data Analysis:  Generating different groupings of data for analysis.
4.  Machine Learning:  Creating training sets with various feature combinations.
5.  Configuration Management:  Generating different configuration sets.
6.  Permissions Management:  Representing different levels of user permissions.
"""

def print_subset(subset, approach_name=""):
    """Helper function to print subsets in a consistent format."""
    print(f"{approach_name}: {subset}")

def subsets_recursive(nums):
    """
    1.  Recursive Backtracking

    Time Complexity: O(N * 2^N) - Each of the 2^N subsets can have up to N elements.
    Space Complexity: O(N) - Depth of the recursion tree can go up to N.

    Project Implementation: Feature Toggling
    Imagine you have a configuration file with features that can be enabled or disabled.
    This approach helps generate all possible combinations of feature configurations.
    """
    result = []

    def backtrack(index, current_subset):
        # Base case: Add the current subset to the result
        result.append(current_subset[:])  # Append a *copy* to avoid modification

        # Explore all possible choices for the remaining elements
        for i in range(index, len(nums)):
            # Include nums[i] in the current subset
            current_subset.append(nums[i])
            # Recursively explore subsets starting from the next element
            backtrack(i + 1, current_subset)
            # Backtrack: Remove nums[i] to explore subsets without it
            current_subset.pop()

    backtrack(0, [])
    return result

def subsets_iterative(nums):
    """
    2.  Iterative Approach

    Time Complexity: O(N * 2^N) - Similar to the recursive approach.
    Space Complexity: O(N) - To store the temporary subset.

    Project Implementation: Combinatorial Optimization
    Consider a scenario where you need to test different combinations of parameters
    in an experiment. This iterative approach generates all possible parameter sets.
    """
    result = [[]]  # Start with an empty subset

    for num in nums:
        new_subsets = []
        for subset in result:
            # For each existing subset, create a new subset by adding the current number
            new_subsets.append(subset + [num])
        result.extend(new_subsets)  # Add the new subsets to the result
    return result

def subsets_bitmasking(nums):
    """
    3.  Bitmasking

    Time Complexity: O(N * 2^N)
    Space Complexity: O(1) -  Ignoring the output list.

    Project Implementation: Data Analysis
    If you're analyzing data with multiple categories, bitmasking can efficiently
    generate all possible combinations of categories for grouping your data.
    """
    result = []
    n = len(nums)
    total_subsets = 2 ** n  # 2 raised to the power of n

    for i in range(total_subsets):
        subset = []
        for j in range(n):
            # Check if the j-th bit is set in the current mask 'i'
            if (i >> j) & 1:
                subset.append(nums[j])
        result.append(subset)
    return result

def subsets_combinations(nums):
    """
    4.  Using Python's `combinations`

    Time Complexity: O(N^2 * 2^N) -  combinations function's time complexity * the cost of copying each combination
    Space Complexity: O(N) - Space used by combinations iterator.

    Project Implementation: Machine Learning (Feature Selection)
    When selecting features for a machine learning model, you might want to evaluate
    the performance of the model with different combinations of features.
    This approach helps generate those combinations.
    """
    from itertools import combinations

    result = []
    for i in range(len(nums) + 1):
        # Generate combinations of length i (0 to n)
        for combo in combinations(nums, i):
            result.append(list(combo))  # Convert tuple to list
    return result

def subsets_reduce(nums):
    """
    5. Using functools.reduce

    Time Complexity: O(N * 2^N)
    Space Complexity: O(2^N)

    Project Implementation: Configuration Management
    Suppose you are building a system where features can be enabled or disabled.
    This approach can generate all possible feature configurations.
    """
    from functools import reduce

    def extend_subsets(subsets, num):
        return subsets + [subset + [num] for subset in subsets]

    # Initial value is [[]], and for each num, extend the subsets
    return reduce(extend_subsets, nums, [[]])

def subsets_yield(nums):
    """
    6. Using Generator (Yield)

    Time Complexity: O(N * 2^N) - Each subset is generated on demand, but overall complexity remains.
    Space Complexity: O(N) -  Due to the depth of recursion.  Memory is used as needed.

    Project Implementation: Permission Management
    In a system with hierarchical permissions, you can use this approach to
    generate all possible combinations of permissions for a user or role.
    """
    def generate_subsets(index, current_subset):
        yield current_subset[:]  # Yield a *copy* of the current subset
        for i in range(index, len(nums)):
            current_subset.append(nums[i])
            yield from generate_subsets(i + 1, current_subset)
            current_subset.pop()

    result = list(generate_subsets(0, [])) # Consume the generator and make it a list.
    return result
if __name__ == "__main__":
    nums = [1, 2, 3]

    print("Input:", nums)
    print("\n--- Subsets ---\n")

    # 1. Recursive Backtracking
    result1 = subsets_recursive(nums)
    for subset in result1:
        print_subset(subset, "Recursive")

    print("\n--- Subsets ---\n")
    # 2. Iterative Approach
    result2 = subsets_iterative(nums)
    for subset in result2:
        print_subset(subset, "Iterative")

    print("\n--- Subsets ---\n")
    # 3. Bitmasking
    result3 = subsets_bitmasking(nums)
    for subset in result3:
        print_subset(subset, "Bitmasking")

    print("\n--- Subsets ---\n")
    # 4. Using Python's `combinations`
    result4 = subsets_combinations(nums)
    for subset in result4:
        print_subset(subset, "Combinations")

    print("\n--- Subsets ---\n")
    # 5. Using functools.reduce
    result5 = subsets_reduce(nums)
    for subset in result5:
        print_subset(subset, "Reduce")

    print("\n--- Subsets ---\n")
    # 6. Using Generator (Yield)
    result6 = subsets_yield(nums)
    for subset in result6:
        print_subset(subset, "Yield")
