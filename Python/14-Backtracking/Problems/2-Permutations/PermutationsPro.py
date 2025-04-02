from typing import List, Deque
from collections import deque
import itertools
import math

def get_permutations_recursive(nums: List[int]) -> List[List[int]]:
    """
    1. Recursive Approach

    - Time Complexity: O(n! * n) - n! for the number of permutations, n for copying each permutation.
    - Space Complexity: O(n) - Depth of the recursion tree.  Does not include the output list.

    Real-world application:
    - Generating all possible schedules for a task, where the order of tasks matters.
    - Creating different orderings for automated testing sequences.
    """
    def permute(nums, l, r, result):
        if l == r:
            result.append(nums[:])  # Append a *copy* of the current state
        else:
            for i in range(l, r + 1):
                nums[l], nums[i] = nums[i], nums[l]  # Swap
                permute(nums, l + 1, r, result)
                nums[l], nums[i] = nums[i], nums[l]  # Backtrack (restore original order)

    result = []
    permute(nums, 0, len(nums) - 1, result)
    return result

def get_permutations_itertools(nums: List[int]) -> List[List[int]]:
    """
    2. Using itertools.permutations()

    - Time Complexity: O(n! * n) - n! for the number of permutations, n for converting the iterator to a list.
    - Space Complexity: O(n!) -  itertools.permutations() generates all n! permutations.

    Real-world application:
    - Quickly generating all possible orderings for a small set of options.
    - Useful in combinatorial problems where permutations are needed.
    """
    return [list(p) for p in itertools.permutations(nums)] # Convert tuples to lists

def get_permutations_heap(nums: List[int]) -> List[List[int]]:
    """
    3. Heap's Algorithm

    - Time Complexity: O(n!) - Generates all permutations.
    - Space Complexity: O(n) -  Operates in-place.

    Real-world application:
     - Generating permutations in a specific order, useful for some algorithmic problems.
     - Efficiently generating permutations when memory is a concern.
    """
    def permute(n, nums, result):
        if n == 1:
            result.append(nums[:])
            return

        for i in range(n):
            permute(n - 1, nums, result)
            if n % 2 == 0:
                nums[i], nums[n - 1] = nums[n - 1], nums[i]
            else:
                nums[0], nums[n - 1] = nums[n - 1], nums[0]

    result = []
    permute(len(nums), nums, result)
    return result

def get_permutations_backtracking(nums: List[int]) -> List[List[int]]:
    """
    4. Backtracking Approach (Explicit)

    - Time Complexity: O(n! * n)
    - Space Complexity: O(n)

    Real-world application:
    - Solving constraint satisfaction problems where order matters.
    - Generating all possible configurations, like in a game.
    """
    def backtrack(combination, remaining, result):
        if not remaining:
            result.append(combination[:])
            return

        for i in range(len(remaining)):
            combination.append(remaining[i])
            next_remaining = remaining[:i] + remaining[i+1:]
            backtrack(combination, next_remaining, result)
            combination.pop()

    result = []
    backtrack([], nums, result)
    return result

def get_permutations_insert(nums: List[int]) -> List[List[int]]:
    """
    5. Insertion-based Approach

    - Time Complexity: O(n! * n)
    - Space Complexity: O(n! * n) -  Potentially stores all permutations.

    Real-world application:
    - Building permutations incrementally, useful in some dynamic programming scenarios.
    - Generating permutations where the order of adding elements is significant.
    """
    if not nums:
        return [[]]

    first = nums[0]
    rest = nums[1:]
    perms = get_permutations_insert(rest)
    result = []
    for perm in perms:
        for i in range(len(perm) + 1):
            new_perm = perm[:i] + [first] + perm[i:]
            result.append(new_perm)
    return result

def get_permutations_deque(nums: List[int]) -> List[List[int]]:
    """
    6. Deque-based Approach

    - Time Complexity: O(n! * n)
    - Space Complexity: O(n^2) - Using deque

    Real-world application:
    - Useful when you need to efficiently insert elements at both ends of a sequence during permutation generation.
    - Can be adapted for problems involving circular arrangements.
    """
    def permute(elements: Deque[int], current_perm: List[int], result: List[List[int]]):
        if not elements:
            result.append(current_perm)
            return

        for _ in range(len(elements)):
            element = elements.popleft()
            permute(elements, current_perm + [element], result)
            elements.append(element)  # Put the element back

    result: List[List[int]] = []
    permute(deque(nums), [], result)
    return result
def main():
    """
    Main function to demonstrate the permutation algorithms.
    """
    test_nums = [1, 2, 3]
    print(f"Input list: {test_nums}")

    print("\n1. Recursive Approach:")
    perms_recursive = get_permutations_recursive(test_nums)
    print(f"Number of permutations: {len(perms_recursive)}")
    print(f"Permutations: {perms_recursive}")

    print("\n2. itertools.permutations():")
    perms_itertools = get_permutations_itertools(test_nums)
    print(f"Number of permutations: {len(perms_itertools)}")
    print(f"Permutations: {perms_itertools}")

    print("\n3. Heap's Algorithm:")
    perms_heap = get_permutations_heap(test_nums)
    print(f"Number of permutations: {len(perms_heap)}")
    print(f"Permutations: {perms_heap}")

    print("\n4. Backtracking Approach:")
    perms_backtracking = get_permutations_backtracking(test_nums)
    print(f"Number of permutations: {len(perms_backtracking)}")
    print(f"Permutations: {perms_backtracking}")

    print("\n5. Insertion-based Approach:")
    perms_insert = get_permutations_insert(test_nums)
    print(f"Number of permutations: {len(perms_insert)}")
    print(f"Permutations: {perms_insert}")

    print("\n6. Deque-based Approach:")
    perms_deque = get_permutations_deque(test_nums)
    print(f"Number of permutations: {len(perms_deque)}")
    print(f"Permutations: {perms_deque}")
    # Verify the number of permutations
    expected_permutations = math.factorial(len(test_nums))
    print(f"\nExpected number of permutations: {expected_permutations}")

    # Verify that all methods produce the same result (optional, for testing)
    all_results = [
        perms_recursive,
        perms_itertools,
        perms_heap,
        perms_backtracking,
        perms_insert,
        perms_deque,
    ]
    for i in range(1, len(all_results)):
        assert sorted(all_results[0]) == sorted(all_results[i]), f"Results differ between methods 1 and {i+1}"
    print("\nAll methods produce the same permutations (verified).")
if __name__ == "__main__":
    main()

