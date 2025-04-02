import logging
import time
from concurrent.futures import ThreadPoolExecutor, as_completed
from typing import Callable, Dict, List, Tuple

# Configure logging for real-world application
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

def is_happy_number_v1(n: int) -> bool:
    """
    Approach 1: Using a set to detect cycles.

    -   Real-world application: Simple and easy to understand, suitable for small, non-performance-critical tasks.
    -   Error handling: Includes basic input validation and error logging.
    -   Optimization: Uses a set for efficient cycle detection.

    Args:
        n: The integer to check.

    Returns:
        True if n is a happy number, False otherwise.
    """
    if not isinstance(n, int) or n <= 0:
        logging.error(f"Invalid input: n must be a positive integer. Got {n}")
        return False  # Explicitly return False for invalid input

    seen = set()
    while n != 1 and n not in seen:
        seen.add(n)
        n = sum(int(digit) ** 2 for digit in str(n))
    return n == 1


def is_happy_number_v2(n: int) -> bool:
    """
    Approach 2: Floyd's Cycle Detection (Tortoise and Hare).

    -   Real-world application: More efficient than Approach 1 in terms of space complexity,
        suitable for larger numbers or memory-constrained environments.
    -   Error handling: Includes input validation and error logging.
    -   Optimization: Uses Floyd's algorithm, which has a lower memory footprint.
    """
    if not isinstance(n, int) or n <= 0:
        logging.error(f"Invalid input: n must be a positive integer. Got {n}")
        return False

    def get_next(num):
        return sum(int(digit) ** 2 for digit in str(num))

    slow = n
    fast = n
    while True:
        slow = get_next(slow)
        fast = get_next(get_next(fast))
        if fast == 1:
            return True
        if slow == fast:
            return False



def is_happy_number_v3(n: int) -> bool:
    """
    Approach 3: Using a hardcoded set of unhappy numbers.

    -   Real-world application: Fastest approach for single number checks, suitable for
        high-frequency checks or performance-critical applications.
    -   Error handling: Includes input validation and error logging.
    -   Optimization: Uses a precomputed set for O(1) lookup of unhappy numbers.
    """
    if not isinstance(n, int) or n <= 0:
        logging.error(f"Invalid input: n must be a positive integer. Got {n}")
        return False

    unhappy_numbers = {4, 16, 37, 58, 89, 145, 42, 20}
    while n != 1 and n not in unhappy_numbers:
        n = sum(int(digit) ** 2 for digit in str(n))
    return n == 1



def is_happy_number_v4(n: int) -> bool:
    """
    Approach 4: Recursive approach with a check for the base case of 4.

    -   Real-world application: Demonstrates recursion, but less practical for very large numbers
        due to potential stack overflow.  Good for educational purposes or small,
        well-defined input sets.
    -   Error handling: Includes input validation and error logging.
    -   Optimization: Checks for the base case of 4 to avoid infinite recursion.
    """
    if not isinstance(n, int) or n <= 0:
        logging.error(f"Invalid input: n must be a positive integer. Got {n}")
        return False

    def get_next(num):
        return sum(int(digit) ** 2 for digit in str(num))

    if n == 1:
        return True
    if n == 4:
        return False
    return is_happy_number_v4(get_next(n))



def is_happy_number_v5(n: int) -> bool:
    """
    Approach 5: Iterative, checking for 1 and the magic number 4.

    - Real-world application:  A balance of speed and simplicity.  Good for general-purpose
      use where you want something faster than the set approach, but don't want to
      hardcode the full unhappy number set.
    - Error handling: Includes input validation.
    - Optimization:  Avoids the overhead of a large set, checking only for the key number '4'.
    """
    if not isinstance(n, int) or n <= 0:
        logging.error(f"Invalid input: n must be a positive integer.  Got {n}")
        return False

    while n != 1 and n != 4:
        n = sum(int(digit) ** 2 for digit in str(n))
    return n == 1

def is_happy_number_v6(n: int) -> bool:
    """
    Approach 6: Using a lookup table for precomputed happy numbers.

    -   Real-world application: Best for scenarios where you need to check the happiness of many numbers
        within a specific range, and you can afford the memory to store the results.  This is
        a trade-off of memory for speed.
    -   Error handling: Includes input validation.
    -   Optimization:  Uses a precomputed lookup table (dictionary) for constant-time O(1) lookups.
    """
    if not isinstance(n, int) or n <= 0:
        logging.error(f"Invalid input: n must be a positive integer. Got {n}")
        return False

    # Precompute happy numbers up to a reasonable limit (e.g., 1000).  Adjust as needed.
    MAX_PRECOMPUTE = 1000
    happy_numbers = {i for i in range(1, MAX_PRECOMPUTE + 1) if is_happy_number_v5(i)}  # Use v5 for precomputation

    if n <= MAX_PRECOMPUTE:
        return n in happy_numbers
    else:
        # If n is larger than the precomputed range, fall back to a standard method (e.g., v5).
        return is_happy_number_v5(n)



def test_happy_number_function(func: Callable[[int], bool], func_name: str) -> None:
    """
    Test a happy number function with a set of test cases.

    Args:
        func: The happy number function to test.
        func_name: The name of the function.
    """
    test_cases: List[Tuple[int, bool]] = [
        (1, True),
        (7, True),
        (13, True),
        (10, True),
        (23, True),
        (28, True),
        (100, True),
        (1000, True),
        (4, False),
        (988, False),
        (0, False),  # Added test case for 0
        (-1, False), # Added test case for negative number
        (2147483647, True), # Max int
    ]

    logging.info(f"Testing {func_name}...")
    start_time = time.time()
    for n, expected in test_cases:
        result = func(n)
        if result == expected:
            logging.info(f"  Test case {n}: PASSED (Result: {result}, Expected: {expected})")
        else:
            logging.error(f"  Test case {n}: FAILED (Result: {result}, Expected: {expected})")
    end_time = time.time()
    logging.info(f"{func_name} tests completed in {end_time - start_time:.4f} seconds.")



def main() -> None:
    """
    Main function to demonstrate and test the different approaches.
    """
    approaches: Dict[str, Callable[[int], bool]] = {
        "Approach 1 (Set)": is_happy_number_v1,
        "Approach 2 (Tortoise/Hare)": is_happy_number_v2,
        "Approach 3 (Unhappy Set)": is_happy_number_v3,
        "Approach 4 (Recursion)": is_happy_number_v4,
        "Approach 5 (Iterative 1/4 Check)": is_happy_number_v5,
        "Approach 6 (Lookup Table)": is_happy_number_v6,
    }

    # Run tests for each approach
    for func_name, func in approaches.items():
        test_happy_number_function(func, func_name)

    # Example usage in a real-world scenario (e.g., processing a list of numbers)
    numbers_to_check = [1, 7, 22, 4, 988, 1000, 12345, 67890, 567892, 2, 3, -5, 0]
    print("\nChecking Happy Numbers in a batch:")
    with ThreadPoolExecutor() as executor:
        # Use a thread pool to parallelize the checks (real-world optimization)
        futures = {executor.submit(is_happy_number_v3, num): num for num in numbers_to_check}  # Using v3

        for future in as_completed(futures):
            num = futures[future]
            try:
                result = future.result()
                print(f"  Number {num}: {'Happy' if result else 'Unhappy'}")
            except Exception as e:
                logging.error(f"Error checking number {num}: {e}")
                print(f"  Number {num}: Error")  # Keep output consistent even on error


if __name__ == "__main__":
    main()
