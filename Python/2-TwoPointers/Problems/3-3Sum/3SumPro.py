# Advanced 3Sum Problem - Real-World Applications
# Finding all unique triplets that sum to zero with six real-world applications.

from bisect import bisect_left  # Import bisect_left for efficient binary search in sorted data
from collections import defaultdict  # Import defaultdict for efficient counting in bucket counting approach
from itertools import combinations  # Import combinations for generating triplets in brute-force approach

# Approach 1: Financial Fraud Detection (Two Pointers)
# Detects fraudulent transactions where three amounts sum to a suspicious value.
def three_sum_fraud_detection(transactions, target):
    """
    Detects potentially fraudulent transactions by finding three amounts that sum to a suspicious target.

    This approach is useful in financial systems to identify patterns that might indicate fraud,
    such as money laundering or accounting irregularities.  It assumes the 'transactions' list
    represents transaction amounts.

    Args:
        transactions: A list of transaction amounts (integers or floats).
        target: The suspicious target sum (e.g., a known threshold for illegal activity).

    Returns:
        A list of unique triplets representing the three transaction amounts that sum to the target.
    """
    transactions.sort()  # Sort transactions to use the two-pointer approach
    result = []  # Initialize list to store results
    for i in range(len(transactions) - 2):
        if i > 0 and transactions[i] == transactions[i - 1]:
            continue  # Skip duplicate transactions
        left, right = i + 1, len(transactions) - 1  # Initialize left and right pointers
        while left < right:
            total = transactions[i] + transactions[left] + transactions[right]  # Calculate the sum
            if total == target:
                result.append([transactions[i], transactions[left], transactions[right]])  # Add triplet
                left += 1
                right -= 1
                while left < right and transactions[left] == transactions[left - 1]:
                    left += 1  # Skip duplicate transactions
                while left < right and transactions[right] == transactions[right + 1]:
                    right -= 1  # Skip duplicate transactions
            elif total < target:
                left += 1  # Adjust pointers based on the sum
            else:
                right -= 1
    return result  # Return the list of suspicious transaction triplets

# Approach 2: Climate Change Data Analysis (Hash Map)
# Identifies three temperature anomalies that sum to zero, indicating balance.
def three_sum_climate_data(temps, target=0):
    """
    Identifies three temperature anomalies that sum to zero, potentially indicating a balanced climate condition.

    This can be used in climate science to analyze temperature variations and identify periods
    where anomalies cancel each other out.  'temps' represents temperature deviations from a baseline.

    Args:
        temps: A list of temperature anomalies (integers or floats).
        target: The target sum, typically 0 for balanced anomalies.

    Returns:
        A list of unique triplets representing the three temperature anomalies that sum to the target.
    """
    temps.sort()  # Sort temperatures for efficiency
    result = set()  # Use a set to store unique triplets
    for i in range(len(temps) - 2):
        seen = {}  # Hash map to store seen temperatures
        for j in range(i + 1, len(temps)):
            complement = target - temps[i] - temps[j]  # Calculate complement
            if complement in seen:
                result.add((temps[i], complement, temps[j]))  # Add triplet to result
            seen[temps[j]] = j  # Store temperature and its index
    return list(map(list, result))  # Convert set to list

# Approach 3: Inventory Balancing in E-Commerce (Binary Search)
# Finds three product categories whose stocks balance out to a neutral point.
def three_sum_inventory(stock_levels, target=0):
    """
    Finds three product categories whose stock levels balance out to a neutral point.

    This is useful in inventory management to identify categories that offset each other,
    helping businesses maintain a balanced inventory. 'stock_levels' represents deviations
    from an ideal stock level.

    Args:
        stock_levels: A sorted list of stock levels (integers).
        target: The target sum, typically 0 for a balanced inventory.

    Returns:
        A list of unique triplets representing the three stock levels that sum to the target.
    """
    stock_levels.sort()  # Ensure stock levels are sorted
    result = set()  # Use a set for unique triplets
    for i in range(len(stock_levels) - 2):
        for j in range(i + 1, len(stock_levels) - 1):
            complement = target - stock_levels[i] - stock_levels[j]  # Calculate complement
            idx = bisect_left(stock_levels, complement, j + 1)  # Binary search for complement
            if idx < len(stock_levels) and stock_levels[idx] == complement:
                result.add((stock_levels[i], stock_levels[j], stock_levels[idx]))  # Add triplet
    return list(map(list, result))  # Convert set to list

# Approach 4: AI Sentiment Analysis in Social Media (Machine Learning Optimization)
# Groups words into three sentiment categories that balance to a neutral score.
def three_sum_sentiment_analysis(scores, target=0):
    """
    Groups words into three sentiment categories that balance to a neutral sentiment score.

    This can be used in natural language processing to analyze the overall sentiment of a text
    by identifying combinations of words with opposing sentiments. 'scores' represents
    sentiment scores for words or phrases.

    Args:
        scores: A sorted list of sentiment scores (integers or floats).
        target: The target sentiment sum, typically 0 for neutral.

    Returns:
        A list of unique triplets representing the three sentiment scores that sum to the target.
    """
    scores.sort()  # Sort sentiment scores
    result = set()  # Use a set for unique triplets
    for i in range(len(scores) - 2):
        left, right = i + 1, len(scores) - 1  # Initialize two pointers
        while left < right:
            total = scores[i] + scores[left] + scores[right]  # Calculate total sentiment
            if total == target:
                result.add((scores[i], scores[left], scores[right]))  # Add triplet
                left += 1
                right -= 1
            elif total < target:
                left += 1  # Adjust pointers
            else:
                right -= 1
    return list(map(list, result))  # Convert set to list

# Approach 5: Cryptocurrency Portfolio Rebalancing (Bucket Counting)
# Finds three assets whose values sum to a target portfolio balance.
def three_sum_crypto(crypto_values, target):
    """
    Finds three cryptocurrency assets whose values sum to a target portfolio balance.

    This can be used in portfolio management to find combinations of assets that achieve a desired
    balance or risk level. 'crypto_values' represents the values of different cryptocurrencies
    in a portfolio.

    Args:
        crypto_values: A list of cryptocurrency values (integers or floats).
        target: The target portfolio balance.

    Returns:
        A list of unique triplets representing the three cryptocurrency values that sum to the target.
    """
    count = defaultdict(int)  # Use defaultdict to count occurrences
    for value in crypto_values:
        count[value] += 1  # Count value occurrences
    result = set()  # Use a set for unique triplets
    unique_values = sorted(count.keys())  # Get sorted unique values
    for i, x in enumerate(unique_values):
        for j in range(i, len(unique_values)):
            y = unique_values[j]
            z = target - (x + y)  # Calculate complement
            if z in count and (z > y or (z == y and count[y] > 1) or (x == y == z and count[x] > 2)):
                result.add(tuple(sorted([x, y, z])))  # Add triplet
    return list(map(list, result))  # Convert set to list

# Approach 6: Logistics Optimization (Graph Theory-Based Planning)
# Identifies three optimal delivery routes whose combined cost meets budget constraints.
def three_sum_logistics(routes, budget):
    """
    Identifies three optimal delivery routes whose combined cost meets budget constraints.

    This can be used in logistics and transportation planning to find cost-effective route combinations.
    'routes' represents the costs or distances of different delivery routes.

    Args:
        routes: A sorted list of route costs or distances (integers or floats).
        budget: The target budget or cost constraint.

    Returns:
        A list of unique triplets representing the three route costs that sum to the budget.
    """
    routes.sort()  # Sort routes
    result = []  # Initialize result list
    for i in range(len(routes) - 2):
        if i > 0 and routes[i] == routes[i - 1]:
            continue  # Skip duplicate routes
        left, right = i + 1, len(routes) - 1  # Initialize pointers
        while left < right:
            total = routes[i] + routes[left] + routes[right]  # Calculate total cost
            if total == budget:
                result.append([routes[i], routes[left], routes[right]])  # Add triplet
                left += 1
                right -= 1
            elif total < budget:
                left += 1  # Adjust pointers
            else:
                right -= 1
    return result  # Return result

# Test Cases
transactions = [10, 20, -10, -20, 5, 15, -5, 0]
temps = [-3, 1, 4, -1, 2, -4, 3, 0]
stock_levels = [50, -20, 30, -10, 40, -30, 20]
sentiment_scores = [-1, -2, 3, 4, -3, -4, 2, 1]
crypto_values = [100, -50, -20, 70, 30, -10, 60]
routes = [300, 150, 50, 200, 100, 250, 400]

target = 0
budget = 500

print("Financial Fraud Detection:", three_sum_fraud_detection(transactions, target))
print("Climate Change Data Analysis:", three_sum_climate_data(temps, target))
print("Inventory Balancing:", three_sum_inventory(stock_levels, target))
print("AI Sentiment Analysis:", three_sum_sentiment_analysis(sentiment_scores, target))
print("Cryptocurrency Portfolio Rebalancing:", three_sum_crypto(crypto_values, target))
print("Logistics Optimization:", three_sum_logistics(routes, budget))
