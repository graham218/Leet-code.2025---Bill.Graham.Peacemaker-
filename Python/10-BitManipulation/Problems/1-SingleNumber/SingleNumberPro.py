def single_number_approach1(nums):
    """
    Approach 1: Using a dictionary (hash map).

    Real-world application:
    - Identifying unique elements in data streams: In real-time data processing, you might need to find unique IDs or events
      from a stream of data where duplicates occur.  This method can be used to track counts efficiently.
    - Detecting anomalies:  If you have a log of user actions and most actions occur in pairs (e.g., login/logout),
      a single, unpaired action could indicate an anomaly.

    Time Complexity: O(n) - Iterates through the list once.  Dictionary operations (insert, lookup) are on average O(1).
    Space Complexity: O(n) - In the worst case, the dictionary stores all n elements (if they are all unique).
    """
    counts = {}
    for num in nums:
        counts[num] = counts.get(num, 0) + 1  # Increment count for each number
    for num, count in counts.items():
        if count == 1:
            return num  # Return the number with count 1


def single_number_approach2(nums):
    """
    Approach 2: Using sets.

    Real-world application:
    - Finding unique items in a collection:  If you have a list of products, files, or database entries, you can use this
      to quickly identify the one that doesn't have a duplicate.
    - Data cleaning:  Removing duplicate entries from a dataset is a common data cleaning task.  This approach can help
      identify the unique entries.

    Time Complexity: O(n) - Iterates through the list once.  Set operations (add, remove) are on average O(1).
    Space Complexity: O(n) - In the worst case, the set stores n-1 elements.
    """
    unique_set = set()
    for num in nums:
        if num in unique_set:
            unique_set.remove(num)  # Remove if duplicate found
        else:
            unique_set.add(num)  # Add if first occurrence
    return unique_set.pop()  # The last remaining element is the single number


def single_number_approach3(nums):
    """
    Approach 3: Using the XOR (^) operator.

    Real-world application:
    - Error detection in data transmission: XOR is used in simple parity checks to detect single-bit errors. While this
      function doesn't directly detect errors, the XOR property is fundamental in such applications.
    - Cryptographic algorithms: XOR is a basic building block in many symmetric encryption algorithms.

    Time Complexity: O(n) - Iterates through the list once.  XOR is a constant-time operation.
    Space Complexity: O(1) - No extra space is used.
    """
    result = 0
    for num in nums:
        result ^= num  # XORing a number with itself cancels it out (a ^ a = 0)
    return result  # The final result is the single number


def single_number_approach4(nums):
    """
    Approach 4: Using math (sum of set - sum of nums)

    Real-world application:
    - Verifying data integrity: If you have a set of numbers and their expected sum (without duplicates), you can use this
      approach to check if any number is missing or duplicated.
    - Database operations: Finding discrepancies between aggregated data and raw data.

    Time Complexity: O(n) - summing n numbers and a set of n/2 numbers
    Space Complexity: O(n) - set of n/2 numbers
    """
    return 2 * sum(set(nums)) - sum(nums)


def single_number_approach5(nums):
    """
    Approach 5: Using collections.Counter

    Real-world application:
    - Frequency analysis: similar to app1, but Counter is optimized for counting.
    - fast retrieval of element frequencies.
    - Text processing: Counting word occurrences.
    - Survey analysis: Counting responses

    Time Complexity: O(n)
    Space Complexity: O(n)
    """
    from collections import Counter
    counts = Counter(nums)
    for num, count in counts.items():
        if count == 1:
            return num


def single_number_approach6(nums):
    """
    Approach 6: Using reduce and XOR

    Real-world application:
     -  Efficiently combining states:  In distributed computing or parallel processing, you might use reduce with XOR
        to combine intermediate results where duplicates cancel out, leading to a final unique state.
     -  Compact data representation:  XOR can be used to create compact representations of data where order doesn't matter
        and duplicates are redundant.

    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    from functools import reduce
    import operator
    return reduce(operator.xor, nums)


def main():
    """
    Main function to demonstrate all approaches with various test cases.
    """
    test_cases = [
        [2, 2, 1],
        [4, 1, 2, 1, 2],
        [1],
        [5, 2, 2, 5, 6, 7, 7],
        [1, 2, 3, 4, 5, 1, 2, 3, 4],
        [10, 20, 10, 20, 30],
        [0, 0, 100],
        [-1, -1, -2],
        [-2, 0, -2, 1, 1],
    ]

    print("Finding the single number using different approaches:")
    print("-" * 80)
    for i, nums in enumerate(test_cases):
        print(f"\nTest Case {i + 1}: {nums}")
        print("-" * 80)
        print(f"Approach 1: Using a dictionary (hash map): {single_number_approach1(nums)}")
        print(f"Approach 2: Using sets: {single_number_approach2(nums)}")
        print(f"Approach 3: Using the XOR (^) operator: {single_number_approach3(nums)}")
        print(f"Approach 4: Using math (sum of set - sum of nums): {single_number_approach4(nums)}")
        print(f"Approach 5: Using collections.Counter: {single_number_approach5(nums)}")
        print(f"Approach 6: Using reduce and XOR: {single_number_approach6(nums)}")
        print("-" * 80)


if __name__ == "__main__":
    main()
