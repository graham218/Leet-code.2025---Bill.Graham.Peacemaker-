"""
Problem: Product of Array Except Self
Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].

You must write an algorithm that runs in O(n) time and without using division.

Approaches:
1. Prefix and Suffix Multiplication
2. Left and Right Pass Multiplication
3. Logarithmic Summation (Alternative Approach)
4. Using a Single Pass with Accumulative Products
5. Optimized Space Complexity Approach
"""

def product_except_self_prefix_suffix(nums):
    """
    Approach 1: Prefix and Suffix Multiplication
    Compute prefix and suffix products separately and multiply them.
    Time Complexity: O(n)
    Space Complexity: O(n)
    """
    n = len(nums)
    prefix = [1] * n
    suffix = [1] * n

    for i in range(1, n):
        prefix[i] = prefix[i - 1] * nums[i - 1]

    for i in range(n - 2, -1, -1):
        suffix[i] = suffix[i + 1] * nums[i + 1]

    return [prefix[i] * suffix[i] for i in range(n)]

def product_except_self_two_pass(nums):
    """
    Approach 2: Left and Right Pass Multiplication
    Using a single array to store the result, first filling with left product and then multiplying with right product.
    Time Complexity: O(n)
    Space Complexity: O(1) (output array excluded)
    """
    n = len(nums)
    result = [1] * n
    left_product = 1
    for i in range(n):
        result[i] = left_product
        left_product *= nums[i]

    right_product = 1
    for i in range(n - 1, -1, -1):
        result[i] *= right_product
        right_product *= nums[i]

    return result

def product_except_self_logarithmic(nums):
    """
    Approach 3: Logarithmic Summation
    Using logarithms to transform multiplication into addition.
    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    from math import log, exp
    total_log = sum(log(abs(num)) for num in nums if num != 0)

    return [round(exp(total_log - log(abs(num)))) if num != 0 else 0 for num in nums]

def product_except_self_accumulative(nums):
    """
    Approach 4: Using a Single Pass with Accumulative Products
    Maintain a rolling product from both left and right in a single pass.
    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    n = len(nums)
    result = [1] * n
    left = right = 1
    for i in range(n):
        result[i] *= left
        result[n - 1 - i] *= right
        left *= nums[i]
        right *= nums[n - 1 - i]

    return result

def product_except_self_optimized(nums):
    """
    Approach 5: Optimized Space Complexity Approach
    Modify the input array to store results, minimizing extra space usage.
    Time Complexity: O(n)
    Space Complexity: O(1) (excluding output array)
    """
    n = len(nums)
    output = [1] * n
    left = 1
    for i in range(n):
        output[i] = left
        left *= nums[i]

    right = 1
    for i in range(n - 1, -1, -1):
        output[i] *= right
        right *= nums[i]

    return output

# Example Usage
nums = [1, 2, 3, 4]
print("Prefix-Suffix:", product_except_self_prefix_suffix(nums))
print("Two-Pass Multiplication:", product_except_self_two_pass(nums))
print("Logarithmic Approach:", product_except_self_logarithmic(nums))
print("Accumulative Pass:", product_except_self_accumulative(nums))
print("Optimized Space Approach:", product_except_self_optimized(nums))
