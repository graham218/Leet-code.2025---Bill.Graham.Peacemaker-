from typing import List

def plus_one_v1(digits: List[int]) -> List[int]:
    """
    Approach 1: Convert to integer, add one, convert back to list of digits.

    This is the most straightforward approach, but it may not be the most efficient
    for very large numbers due to the limitations of integer data types.

    Args:
        digits: A list of integers representing a non-negative number.

    Returns:
        A list of integers representing the number incremented by one.
    """
    # Convert the list of digits to a single integer.
    num = 0
    for digit in digits:
        num = num * 10 + digit

    # Add one to the integer.
    num += 1

    # Convert the integer back to a list of digits.
    result = []
    while num > 0:
        result.insert(0, num % 10)
        num //= 10
    return result if result else [1]  # Handle the case where the input is [0].

def plus_one_v2(digits: List[int]) -> List[int]:
    """
    Approach 2: Iterate from the rightmost digit, handling carry-over.

    This approach directly manipulates the list of digits, which is more efficient
    than converting to and from an integer.  It simulates the manual process of adding one.

    Args:
        digits: A list of integers representing a non-negative number.

    Returns:
        A list of integers representing the number incremented by one.
    """
    carry = 1
    for i in range(len(digits) - 1, -1, -1):
        digits[i] += carry
        carry = digits[i] // 10
        digits[i] %= 10
    if carry:
        digits.insert(0, carry)
    return digits

def plus_one_v3(digits: List[int]) -> List[int]:
    """
    Approach 3:  Iterate from the right, and return early if no carry.

    This is a slight optimization of Approach 2.  It avoids iterating through the entire
    list if the addition doesn't result in a carry-over.

    Args:
        digits: A list of integers representing a non-negative number.

    Returns:
        A list of integers representing the number incremented by one.
    """
    for i in range(len(digits) - 1, -1, -1):
        digits[i] += 1
        if digits[i] < 10:
            return digits
        digits[i] = 0
    return [1] + digits  # If we reach here, it means we had all 9s.

def plus_one_v4(digits: List[int]) -> List[int]:
    """
    Approach 4: Using recursion to handle the carry-over.

    This approach uses recursion to handle the carry-over.  While it's a different way
    to think about the problem, it's generally less efficient than the iterative approaches
    due to the overhead of function calls.  It can also lead to stack overflow for very
    large inputs (though that's unlikely with this problem).

    Args:
        digits: A list of integers representing a non-negative number.

    Returns:
        A list of integers representing the number incremented by one.
    """
    def recursive_add(digits, index):
        if index < 0:
            return [1] + digits
        digits[index] += 1
        if digits[index] < 10:
            return digits
        digits[index] = 0
        return recursive_add(digits, index - 1)

    return recursive_add(digits, len(digits) - 1)
def plus_one_v5(digits: List[int]) -> List[int]:
    """
    Approach 5:  Similar to v3, but uses a while loop.

    This approach is very similar to Approach 3, but uses a `while` loop instead of a `for` loop.
    It's essentially an iterative approach that stops as soon as a digit is less than 10
    after adding 1.

    Args:
        digits: A list of integers representing a non-negative number.

    Returns:
        A list of integers representing the number incremented by one.
    """
    i = len(digits) - 1
    while i >= 0:
        digits[i] += 1
        if digits[i] < 10:
            return digits
        digits[i] = 0
        i -= 1
    return [1] + digits

def main():
    """
    Main function to demonstrate the different approaches.
    """
    test_cases = [
        [1, 2, 3],
        [4, 3, 2, 1],
        [9],
        [9, 9],
        [9, 9, 9],
        [0],
        [5,9,9,9]
    ]
    approaches = {
        "Approach 1: Convert to integer": plus_one_v1,
        "Approach 2: Iterate from right": plus_one_v2,
        "Approach 3: Iterate and return early": plus_one_v3,
        "Approach 4: Recursion": plus_one_v4,
        "Approach 5: While Loop": plus_one_v5,
    }

    print("Testing Plus One with different approaches:")
    for test_case in test_cases:
        print(f"\nInput: {test_case}")
        for approach_name, approach_func in approaches.items():
            result = approach_func(test_case.copy())  # Pass a copy to avoid modifying the original
            print(f"  {approach_name}: {result}")

if __name__ == "__main__":
    main()
