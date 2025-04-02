def subsets_recursive(nums):
    """
    Approach 1: Recursive Backtracking

    This approach uses a recursive helper function to explore all possible combinations.
    For each element, we have two choices: include it in the current subset or exclude it.

    Time Complexity: O(2^n), where n is the number of elements in nums.
    Space Complexity: O(n) for the recursion stack.  The output list, which can have up to 2^n subsets, is not considered part of the auxiliary space.
    """
    result = []

    def backtrack(index, current_subset):
        # Base case: when we have processed all elements, add the current subset to the result
        if index == len(nums):
            result.append(list(current_subset))  # Append a *copy*!
            return

        # Recursive case:
        # 1. Exclude the current element
        backtrack(index + 1, current_subset)

        # 2. Include the current element
        current_subset.append(nums[index])
        backtrack(index + 1, current_subset)
        current_subset.pop()  # Backtrack: remove the element to explore other possibilities

    backtrack(0, [])
    return result


def subsets_iterative(nums):
    """
    Approach 2: Iterative Approach

    This approach iteratively builds the subsets.  Starting with an empty set,
    for each number in nums, we create new subsets by adding the number to
    all existing subsets.

    Time Complexity: O(2^n)
    Space Complexity: O(2^n)
    """
    result = [[]]  # Start with an empty set
    for num in nums:
        new_subsets = []
        for subset in result:
            # Create a new subset by adding the current number to an existing subset
            new_subsets.append(subset + [num])
        result.extend(new_subsets)  # Add all the newly formed subsets
    return result



def subsets_bitmasking(nums):
    """
    Approach 3: Bitmasking

    This approach uses bit manipulation to generate all possible subsets.
    Each subset can be represented by a binary string of length n, where n is
    the number of elements in nums.  If the i-th bit is 1, the i-th element
    is included in the subset.

    Time Complexity: O(n * 2^n)
    Space Complexity: O(2^n)
    """
    n = len(nums)
    result = []
    for i in range(2**n):  # Iterate through all possible bitmasks (0 to 2^n - 1)
        subset = []
        for j in range(n):
            # Check if the j-th bit is set in the current bitmask
            if (i >> j) & 1:
                subset.append(nums[j])
        result.append(subset)
    return result


def subsets_combinations(nums):
    """
    Approach 4: Using itertools.combinations

    This approach leverages the `combinations` function from the `itertools`
    library to generate subsets of all possible lengths.

    Time Complexity: O(2^n) in total, but the complexity of combinations function varies.
    Space Complexity: O(2^n)
    """
    from itertools import combinations

    result = []
    for i in range(len(nums) + 1):  # Iterate through all possible subset lengths
        for combination in combinations(nums, i):
            result.append(list(combination))
    return result

def subsets_reduce(nums):
    """
    Approach 5: Using functools.reduce

    This approach uses functools.reduce to iteratively build the subsets.  It's a functional
    approach, accumulating subsets.

    Time Complexity: O(2^n)
    Space Complexity: O(2^n)
    """
    from functools import reduce

    def extend_subsets(subsets, num):
        return subsets + [subset + [num] for subset in subsets]

    # Handle the case of empty input
    if not nums:
        return [[]]

    return reduce(extend_subsets, nums, [[]]) # start with [[]]


if __name__ == "__main__":
    nums = [1, 2, 3]

    print("Input:", nums)

    print("\nApproach 1: Recursive Backtracking")
    result1 = subsets_recursive(nums)
    print("Subsets:", result1)

    print("\nApproach 2: Iterative Approach")
    result2 = subsets_iterative(nums)
    print("Subsets:", result2)

    print("\nApproach 3: Bitmasking")
    result3 = subsets_bitmasking(nums)
    print("Subsets:", result3)

    print("\nApproach 4: Using itertools.combinations")
    result4 = subsets_combinations(nums)
    print("Subsets:", result4)

    print("\nApproach 5: Using functools.reduce")
    result5 = subsets_reduce(nums)
    print("Subsets:", result5)
