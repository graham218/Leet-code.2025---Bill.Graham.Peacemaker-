# Advanced Two Sum II Implementations
# Real-World Applications of Two Sum II (Sorted Array)

from bisect import bisect_left  # Import bisect_left for efficient binary search
from collections import defaultdict # Import defaultdict, although it's not used

# Approach 1: Financial Transactions (Two Pointers)
# Used to find matching transactions that sum up to a specific amount
def two_sum_finance(transactions, target):
    """
    Finds two transactions whose sum equals the target amount using the two-pointer approach.

    This is useful in financial systems for reconciliation, fraud detection, or finding
    transactions that, when combined, reach a specific financial goal.  The input
    'transactions' is assumed to be sorted (or sorted amounts).

    Args:
        transactions: A sorted list of transaction amounts (integers or floats).
        target: The target transaction amount.

    Returns:
        A list containing the 1-based indices of the two transactions.
        Returns an empty list if no such pair exists.
    """
    left, right = 0, len(transactions) - 1  # Initialize left and right pointers
    while left < right:
        current_sum = transactions[left] + transactions[right]  # Calculate the sum of the two transactions
        if current_sum == target:
            return [left + 1, right + 1]  # Return 1-based indices if the sum matches the target
        elif current_sum < target:
            left += 1  # Move left pointer to increase the sum
        else:
            right -= 1  # Move right pointer to decrease the sum
    return []  # Return empty list if no matching transactions are found

# Approach 2: E-Commerce Discounts (Binary Search)
# Used in discount calculations where items must sum to a specific amount
def two_sum_discounts(prices, target):
    """
    Finds two item prices that sum up to a target discount value using binary search.

    This can be used in e-commerce to find which two items, when purchased together,
    qualify for a specific discount or promotional offer. The input 'prices' is
    assumed to be sorted.  Uses bisect_left for efficiency.

    Args:
        prices: A sorted list of item prices (integers or floats).
        target: The target discount value.

    Returns:
        A list containing the 1-based indices of the two items.
        Returns an empty list if no such pair exists.
    """
    for i in range(len(prices)):
        complement = target - prices[i]  # Calculate the complement needed to reach the target
        index = bisect_left(prices, complement, i + 1) # Use binary search to find the complement's index
        if index < len(prices) and prices[index] == complement:
            return [i + 1, index + 1]  # Return indices if complement is found
    return []  # Return empty list if no matching items are found

# Approach 3: Cloud Storage Optimization (Hash Map)
# Used in cloud storage deduplication by finding complementary file sizes
def two_sum_cloud_storage(sizes, target):
    """
    Finds two file sizes that sum up to a target value, often used in cloud storage
    optimization for deduplication.

    Cloud storage systems can use this to identify pairs of files that, when combined,
    reach a specific size, potentially indicating redundant data that can be optimized.
    This approach uses a hash map for efficient lookup. The input 'sizes' does not
    need to be sorted.

    Args:
        sizes: A list of file sizes (integers or floats).
        target: The target combined file size.

    Returns:
        A list containing the 1-based indices of the two files.
        Returns an empty list if no such pair exists.
    """
    size_map = {}  # Initialize a hash map to store file sizes and their indices
    for i, size in enumerate(sizes):
        complement = target - size  # Calculate the complement size
        if complement in size_map:
            return [size_map[complement] + 1, i + 1]  # Return indices if complement is found
        size_map[size] = i  # Store the size and its index
    return []  # Return empty list if no matching files are found

# Approach 4: Logistics & Route Planning (Graph Optimization)
# Used to determine two best routes that sum to the target distance
def two_sum_routes(distances, target):
    """
    Finds two routes whose distances sum up to a target distance in logistics
    and route planning.

    This can help in optimizing delivery routes, finding optimal connections,
    or planning travel itineraries. The input 'distances' is assumed to be sorted.

    Args:
        distances: A sorted list of route distances (integers or floats).
        target: The target total distance.

    Returns:
        A list containing the 1-based indices of the two routes.
        Returns an empty list if no such pair exists.
    """
    left, right = 0, len(distances) - 1  # Initialize left and right pointers
    while left < right:
        current_distance = distances[left] + distances[right]  # Calculate the sum of the distances
        if current_distance == target:
            return [left + 1, right + 1]  # Return indices if the sum matches
        elif current_distance < target:
            left += 1  # Move left pointer to increase the sum
        else:
            right -= 1  # Move right pointer to decrease the sum
    return []  # Return empty list if no matching routes are found

# Approach 5: AI Chatbot Response Matching (Modified Approach)
# Used in AI/NLP systems to find phrase lengths that match the target
def two_sum_chatbot(phrases, target):
    """
    Finds two phrases whose lengths sum up to a target length in AI chatbot
    response matching.

    This can be used to find combinations of phrases that fit a specific
    character limit or to analyze the structure of chatbot responses.  This
    approach calculates the lengths of the phrases and then uses the
    two-pointer technique. The input 'phrases' does not need to be sorted, but
    the lengths are effectively sorted by the logic.

    Args:
        phrases: A list of phrases (strings).
        target: The target combined length.

    Returns:
        A list containing the 1-based indices of the two phrases.
        Returns an empty list if no such pair exists.
    """
    lengths = [len(phrase) for phrase in phrases]  # Calculate the length of each phrase
    left, right = 0, len(lengths) - 1  # Initialize left and right pointers
    while left < right:
        current_sum = lengths[left] + lengths[right]  # Calculate the sum of the lengths
        if current_sum == target:
            return [left + 1, right + 1]  # Return indices if the sum matches
        elif current_sum < target:
            left += 1  # Move left pointer to increase the sum
        else:
            right -= 1  # Move right pointer to decrease the sum
    return []  # Return empty list if no matching phrases are found

# Approach 6: Cryptocurrency Arbitrage (Real-Time Data Processing)
# Used to find two cryptocurrency values that sum to an arbitrage target
def two_sum_crypto(prices, target):
    """
    Finds two cryptocurrency prices that sum to a target arbitrage value.

    This can be used in real-time trading systems to identify potential
    arbitrage opportunities where the combined price of two cryptocurrencies
    meets a specific target for profit.  This approach uses a set for efficient
    lookup. The input 'prices' does not need to be sorted, and this approach
    assumes that the prices are unique.

    Args:
        prices: A list of cryptocurrency prices (integers or floats).
        target: The target arbitrage value.

    Returns:
        A list containing the 1-based indices of the two prices.
        Returns an empty list if no such pair exists.  If there are duplicate
        prices, the function may not return the expected indices.
    """
    seen = set()  # Initialize a set to store seen prices
    for price in prices:
        complement = target - price  # Calculate the complement price
        if complement in seen:
            return [prices.index(complement) + 1, prices.index(price) + 1]  # Return indices
        seen.add(price)  # Add the current price to the set
    return []  # Return empty list if no arbitrage opportunity is found

# Test Cases
transactions = [10, 20, 35, 50, 75, 100]
prices = [5, 25, 40, 60, 80, 95]
distances = [3, 10, 25, 45, 60, 75]
sizes = [1, 5, 10, 15, 20, 25]
phrases = ["hello", "world", "ai", "bot", "matching"]
crypto_prices = [200, 450, 700, 1200, 1500]

target = 100

print("Financial Transactions:", two_sum_finance(transactions, target))
print("E-Commerce Discounts:", two_sum_discounts(prices, target))
print("Cloud Storage Optimization:", two_sum_cloud_storage(sizes, target))
print("Logistics & Route Planning:", two_sum_routes(distances, target))
print("AI Chatbot Response Matching:", two_sum_chatbot(phrases, 6))
print("Cryptocurrency Arbitrage:", two_sum_crypto(crypto_prices, 1700))
