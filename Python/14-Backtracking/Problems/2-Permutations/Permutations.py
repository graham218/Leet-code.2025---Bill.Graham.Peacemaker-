def get_permutations_1(nums):
    """
    Approach 1: Using Recursion and Swapping

    This approach uses recursion and swaps elements in the input list to generate permutations.
    It's a classic backtracking method.

    Args:
        nums: A list of integers.

    Returns:
        A list of lists, where each inner list is a permutation of the input list.
    """
    def permute(nums, l, r, result):
        """
        Recursive helper function to generate permutations.

        Args:
            nums: The list to permute.
            l: The left index of the current sublist to permute.
            r: The right index of the current sublist to permute.
            result: The list to store the generated permutations.
        """
        if l == r:
            # Base case: when left and right indices are the same, we have a complete permutation.
            result.append(nums[:])  # Append a *copy* of the current state of nums
        else:
            for i in range(l, r + 1):
                # Iterate through the remaining elements in the sublist.
                nums[l], nums[i] = nums[i], nums[l]  # Swap the current element with the element at the left index.
                permute(nums, l + 1, r, result)  # Recursively generate permutations for the remaining sublist.
                nums[l], nums[i] = nums[i], nums[l]  # Backtrack: swap the elements back to restore the original order.

    result = []
    permute(nums, 0, len(nums) - 1, result)
    return result

def get_permutations_2(nums):
    """
    Approach 2: Using Recursion and Inserting at All Positions

    This approach recursively builds permutations by inserting the next number
    into all possible positions of the previously generated permutations.

    Args:
        nums: A list of integers.

    Returns:
        A list of lists, where each inner list is a permutation of the input list.
    """
    if not nums:
        return [[]]  # Base case: empty list has one permutation: [[]]

    first = nums[0]  # Take the first element.
    rest = nums[1:]   # Get the remaining elements.
    perms_rest = get_permutations_2(rest) # Recursively get permutations of the rest of the list.
    result = []

    for perm in perms_rest:
        for i in range(len(perm) + 1):
            # Insert the 'first' element at every possible position in each permutation of the rest.
            new_perm = perm[:i] + [first] + perm[i:]
            result.append(new_perm)
    return result

def get_permutations_3(nums):
    """
    Approach 3: Iterative Approach

    This approach iteratively builds permutations.  It starts with the first element
    and then inserts subsequent elements into all possible positions of the
    existing permutations.

    Args:
        nums: A list of integers.

    Returns:
        A list of lists, where each inner list is a permutation of the input list.
    """
    result = [[nums[0]]]  # Start with the first element as the initial permutation.

    for i in range(1, len(nums)):
        num = nums[i]
        new_result = []
        for perm in result:
            for j in range(len(perm) + 1):
                # Insert the current number into all possible positions of each existing permutation.
                new_perm = perm[:j] + [num] + perm[j:]
                new_result.append(new_perm)
        result = new_result  # Update the result with the new permutations.
    return result

def get_permutations_4(nums):
    """
    Approach 4: Using collections.deque for Efficiency

    This approach is similar to approach 2 but uses collections.deque for
    more efficient insertion at arbitrary positions in the list.  Inserting into
    the middle of a standard Python list is O(n), while it's closer to O(1)
    for a deque.

    Args:
        nums: A list of integers.

    Returns:
        A list of lists, where each inner list is a permutation of the input list.
    """
    from collections import deque

    if not nums:
        return [[]]

    first = nums[0]
    rest = nums[1:]
    perms_rest = get_permutations_4(rest)
    result = []

    for perm in perms_rest:
        # Use deque for efficient insertion.
        perm_deque = deque(perm)
        for i in range(len(perm) + 1):
            perm_deque.insert(i, first)  # Insert at index i
            result.append(list(perm_deque)) # Convert back to list for final result.
            perm_deque.remove(first)      # Remove the inserted element (backtrack for deque)
    return result

def get_permutations_5(nums):
    """
    Approach 5: Using Backtracking with Visited Set

    This approach uses a visited set to keep track of which numbers have been
    included in the current permutation.  This avoids the swapping of elements
    seen in approach 1, and can be slightly more efficient in some cases.

    Args:
        nums: A list of integers.

    Returns:
        A list of lists, where each inner list is a permutation of the input list.
    """
    def permute(nums, current_perm, visited, result):
        if len(current_perm) == len(nums):
            result.append(current_perm[:])
            return

        for i in range(len(nums)):
            if i not in visited:
                visited.add(i)
                current_perm.append(nums[i])
                permute(nums, current_perm, visited, result)
                current_perm.pop()
                visited.remove(i)

    result = []
    permute(nums, [], set(), result)
    return result

if __name__ == "__main__":
    numbers = [1, 2, 3]

    print("Input list:", numbers)
    print("\nApproach 1: Recursion and Swapping")
    permutations_1 = get_permutations_1(numbers)
    print(permutations_1)

    print("\nApproach 2: Recursion and Inserting at All Positions")
    permutations_2 = get_permutations_2(numbers)
    print(permutations_2)

    print("\nApproach 3: Iterative Approach")
    permutations_3 = get_permutations_3(numbers)
    print(permutations_3)

    print("\nApproach 4: Using collections.deque")
    permutations_4 = get_permutations_4(numbers)
    print(permutations_4)

    print("\nApproach 5: Using Backtracking with Visited Set")
    permutations_5 = get_permutations_5(numbers)
    print(permutations_5)

    # Verify that all approaches produce the same result, regardless of order.
    # Convert each list of permutations to a set of tuples.  Sets ignore order,
    # and tuples are hashable (unlike lists), so we can compare them.
    set_of_permutations = set(tuple(perm) for perm in permutations_1)
    assert set(tuple(perm) for perm in permutations_2) == set_of_permutations
    assert set(tuple(perm) for perm in permutations_3) == set_of_permutations
    assert set(tuple(perm) for perm in permutations_4) == set_of_permutations
    assert set(tuple(perm) for perm in permutations_5) == set_of_permutations
    print("\nAll approaches produce the same set of permutations!")
