import logging
from typing import List, Callable, Dict, Tuple
import time
from concurrent.futures import ThreadPoolExecutor, as_completed

# Configure logging for real-world application
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

def plus_one_v1(digits: List[int]) -> List[int]:
    """
    Approach 1: Convert to integer, add one, convert back to list of digits.

    -   Real-world application: Suitable for small to medium-sized numbers where performance is not critical.
    -   Error handling: Includes input validation and logging.
    -   Optimization: None (inherently inefficient for large numbers).
    -   Use case:  Quick script for non-performance-critical applications, or when interfacing with
        a system that represents numbers as integers.
    """
    if not isinstance(digits, list) or not all(isinstance(d, int) and 0 <= d <= 9 for d in digits):
        logging.error(f"Invalid input: digits must be a list of integers between 0 and 9. Got {digits}")
        return []  # Return empty list for invalid input

    if not digits:
        return [1]

    num = 0
    for digit in digits:
        num = num * 10 + digit
    num += 1
    result = []
    while num > 0:
        result.insert(0, num % 10)
        num //= 10
    return result if result else [1]



def plus_one_v2(digits: List[int]) -> List[int]:
    """
    Approach 2: Iterate from the rightmost digit, handling carry-over.

    -   Real-world application: More efficient than Approach 1, suitable for most general-purpose use cases.
    -   Error handling: Includes input validation and logging.
    -   Optimization: In-place modification of the list.
    -   Use case: General-purpose function for adding one to a number represented as a list of digits.
    """
    if not isinstance(digits, list) or not all(isinstance(d, int) and 0 <= d <= 9 for d in digits):
        logging.error(f"Invalid input: digits must be a list of integers between 0 and 9. Got {digits}")
        return []

    if not digits:
        return [1]

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
    Approach 3: Iterate from the right, and return early if no carry.

    -   Real-world application: Optimized for cases where carry-over is infrequent, common in many scenarios.
    -   Error handling: Includes input validation and logging.
    -   Optimization: Early return when no carry-over.
    -   Use case: High-performance applications where you expect the input number to not end in many 9s.
    """
    if not isinstance(digits, list) or not all(isinstance(d, int) and 0 <= d <= 9 for d in digits):
        logging.error(f"Invalid input: digits must be a list of integers between 0 and 9. Got {digits}")
        return []

    if not digits:
        return [1]

    for i in range(len(digits) - 1, -1, -1):
        digits[i] += 1
        if digits[i] < 10:
            return digits
        digits[i] = 0
    return [1] + digits  # Handle the case where the input is all 9s.




def plus_one_v4(digits: List[int]) -> List[int]:
    """
    Approach 4: Using recursion to handle the carry-over.

    -   Real-world application: Demonstrates recursion, but less practical for very large numbers
        due to potential stack overflow. Good for educational purposes and small inputs.
    -   Error handling: Includes input validation and logging.
    -   Optimization: Tail-call optimization *could* be applied by the Python interpreter, but it isn't.
    -   Use case:  Educational purposes, or in systems with limited memory where iterative approaches
        might use more stack space.
    """
    if not isinstance(digits, list) or not all(isinstance(d, int) and 0 <= d <= 9 for d in digits):
        logging.error(f"Invalid input: digits must be a list of integers between 0 and 9. Got {digits}")
        return []

    if not digits:
        return [1]

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
    Approach 5: Similar to v3, but uses a while loop.

    -   Real-world application:  Same as v3.
    -   Error handling: Includes input validation and logging.
    -   Optimization: Same as v3.
    -    Use case: Same as v3.
    """
    if not isinstance(digits, list) or not all(isinstance(d, int) and 0 <= d <= 9 for d in digits):
        logging.error(f"Invalid input: digits must be a list of integers between 0 and 9.  Got {digits}")
        return []

    if not digits:
        return [1]

    i = len(digits) - 1
    while i >= 0:
        digits[i] += 1
        if digits[i] < 10:
            return digits
        digits[i] = 0
        i -= 1
    return [1] + digits


def plus_one_v6(digits: List[int]) -> List[int]:
    """
    Approach 6: Optimized for very large numbers using string conversion and back.

    -   Real-world application: Handles extremely large numbers that exceed Python's integer limits.
    -   Error handling: Includes input validation and logging.
    -   Optimization: Uses string conversion to handle arbitrarily large numbers.
    -   Use case: Systems that deal with very large numbers, such as financial calculations,
        cryptography, or scientific computing.
    """
    if not isinstance(digits, list) or not all(isinstance(d, int) and 0 <= d <= 9 for d in digits):
        logging.error(f"Invalid input: digits must be a list of integers between 0 and 9. Got {digits}")
        return []

    if not digits:
        return [1]

    num_str = "".join(map(str, digits))
    try:
        large_num = int(num_str) + 1
        result = [int(digit) for digit in str(large_num)]
        return result
    except OverflowError:
        logging.error("Number too large to handle.")
        return []  # Handle overflow, though Python ints should handle very large numbers.



def test_plus_one_function(func: Callable[[List[int]], List[int]], func_name: str) -> None:
    """
    Test a plus one function with a set of test cases.

    Args:
        func: The plus one function to test.
        func_name: The name of the function.
    """
    test_cases: List[Tuple[List[int], List[int]]] = [
        ([1, 2, 3], [1, 2, 4]),
        ([4, 3, 2, 1], [4, 3, 2, 2]),
        ([9], [1, 0]),
        ([9, 9], [1, 0, 0]),
        ([9, 9, 9], [1, 0, 0, 0]),
        ([0], [1]),
        ([5, 9, 9, 9], [6, 0, 0, 0]),
        ([], [1]),  # Test case for empty list
        ([1, 2, 10], []), # Test case with invalid input
        ([1, 2, -1], []), # Test case with negative input
        ([1, 2, 3.5], []), # Test case with float
        ("abc", []), # Test case with string
    ]

    logging.info(f"Testing {func_name}...")
    start_time = time.time()
    for digits, expected in test_cases:
        result = func(digits)
        if result == expected:
            logging.info(f"  Test case {digits}: PASSED (Result: {result}, Expected: {expected})")
        else:
            logging.error(f"  Test case {digits}: FAILED (Result: {result}, Expected: {expected})")
    end_time = time.time()
    logging.info(f"{func_name} tests completed in {end_time - start_time:.4f} seconds.")



def main() -> None:
    """
    Main function to demonstrate and test the different approaches.
    """
    approaches: Dict[str, Callable[[List[int]], List[int]]] = {
        "Approach 1: Convert to integer": plus_one_v1,
        "Approach 2: Iterate from right": plus_one_v2,
        "Approach 3: Iterate and return early": plus_one_v3,
        "Approach 4: Recursion": plus_one_v4,
        "Approach 5: While Loop": plus_one_v5,
        "Approach 6: Handle Very Large Numbers": plus_one_v6,
    }

    # Run tests for each approach
    for func_name, func in approaches.items():
        test_plus_one_function(func, func_name)

    # Example usage in a real-world scenario (e.g., processing a list of numbers)
    numbers_to_increment = [[1, 2, 3], [9, 9, 9], [1234567890123456789], [5, 6, 7], [999999999999999999999999999999]]  # Added a very large number
    print("\nIncrementing numbers in a batch:")
    with ThreadPoolExecutor() as executor:
        futures = {executor.submit(plus_one_v6, num): num for num in numbers_to_increment} # Using v6 for large number handling
        for future in as_completed(futures):
            num = futures[future]
            try:
                result = future.result()
                print(f"  Incrementing {num}: Result = {result}")
            except Exception as e:
                logging.error(f"Error incrementing {num}: {e}")
                print(f"  Incrementing {num}: Error")



if __name__ == "__main__":
    main()
