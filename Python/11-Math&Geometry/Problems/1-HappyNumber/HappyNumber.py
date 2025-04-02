def is_happy_number_v1(n: int) -> bool:
    """
    Approach 1: Using a set to detect cycles.

    A happy number is defined by the following process:
    Starting with any positive integer, replace the number by the sum of the squares of its digits,
    and repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle
    which does not include 1. Those numbers for which this process ends in 1 are happy numbers.

    This version uses a set to keep track of seen numbers. If a number repeats,
    we know it's in a cycle and not a happy number.

    Args:
        n: The integer to check.

    Returns:
        True if n is a happy number, False otherwise.
    """
    seen = set()
    while n != 1 and n not in seen:
        seen.add(n)
        n = sum(int(digit) ** 2 for digit in str(n))
    return n == 1

def is_happy_number_v2(n: int) -> bool:
    """
    Approach 2: Floyd's Cycle Detection (Tortoise and Hare).

    This approach uses two pointers, 'slow' and 'fast'.  The 'slow' pointer moves one step
    at a time, while the 'fast' pointer moves two steps at a time.  If there's a cycle,
    the two pointers will eventually meet. If there is no cycle, the fast pointer will eventually reach 1.

    Args:
        n: The integer to check.

    Returns:
        True if n is a happy number, False otherwise.
    """
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

    All unhappy numbers eventually fall into the same cycle: 4, 16, 37, 58, 89, 145, 42, 20.
    We can pre-calculate this cycle and check if the number ever reaches any of these values.
    This is the most efficient approach in terms of speed.

    Args:
        n: The integer to check.

    Returns:
        True if n is a happy number, False otherwise.
    """
    unhappy_numbers = {4, 16, 37, 58, 89, 145, 42, 20} # changed to set
    while n != 1 and n not in unhappy_numbers:
        n = sum(int(digit) ** 2 for digit in str(n))
    return n == 1

def is_happy_number_v4(n: int) -> bool:
    """
    Approach 4: Recursive approach with a check for the base case of 4.

    This approach uses recursion.  The base case is when the number reaches 1 (happy) or 4 (unhappy).
    It's similar to approach 1 but implemented recursively.

    Args:
        n: The integer to check.

    Returns:
        True if n is a happy number, False otherwise.
    """
    def get_next(num):
        return sum(int(digit) ** 2 for digit in str(num))

    if n == 1:
        return True
    if n == 4:  # Base case for unhappy numbers
        return False
    return is_happy_number_v4(get_next(n)) # Recursive call

def is_happy_number_v5(n: int) -> bool:
    """
    Approach 5: Iterative, checking for 1 and the magic number 4.

    A slight variation on the previous approaches, this one explicitly checks for the
    number 4, which is the start of the unhappy number cycle.  This avoids using a full set
    of unhappy numbers, making it slightly more efficient than the set approach.

    Args:
        n: The integer to check.

    Returns:
        True if n is a happy number, False otherwise.
    """
    while n != 1 and n != 4:
        n = sum(int(digit) ** 2 for digit in str(n))
    return n == 1

def main():
    """
    Main function to demonstrate the different approaches.
    """
    test_numbers = [1, 7, 13, 10, 23, 28, 100, 1000, 4, 988] # Added more test cases
    approaches = {
        "Approach 1 (Set)": is_happy_number_v1,
        "Approach 2 (Tortoise/Hare)": is_happy_number_v2,
        "Approach 3 (Unhappy Set)": is_happy_number_v3,
        "Approach 4 (Recursion)": is_happy_number_v4,
        "Approach 5 (Iterative 1/4 Check)": is_happy_number_v5,
    }

    print("Checking Happy Numbers with different approaches:")
    for num in test_numbers:
        print(f"\nNumber: {num}")
        for approach_name, approach_func in approaches.items():
            result = approach_func(num)
            print(f"  {approach_name}: {result}")

if __name__ == "__main__":
    main()
