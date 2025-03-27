'''
Advanced Sliding Window - Real-World Implementations

Problem Statement:
Given an array of integers and a window size `k`, implement six different real-world use cases using the sliding window technique.
'''

# 1. Stock Price Analysis - Maximum Stock Price in K Days (Deque - O(n))
from collections import deque

def max_stock_price(prices, k):
    """
    Finds the maximum stock price within a sliding window of k days.  Uses a deque
    to efficiently track the maximum price within the current window.

    Args:
        prices (list): A list of stock prices for each day.
        k (int): The size of the sliding window.

    Returns:
        list: A list of the maximum stock prices for each sliding window.
    """
    q = deque()  # Initialize a deque to store indices of stock prices.
    result = []  # Initialize a list to store the maximum stock prices.

    for i in range(len(prices)):
        # Maintain a decreasing order of prices in the deque.
        # If the current price is greater than the price at the back of the deque,
        # pop the back element until the deque is empty or the order is restored.
        while q and prices[q[-1]] < prices[i]:
            q.pop()
        q.append(i)  # Append the index of the current price to the deque.

        # If the front of the deque is out of the current window, remove it.
        if q[0] == i - k:
            q.popleft()

        # If the window has reached size k, append the maximum price (at the front of deque) to the result.
        if i >= k - 1:
            result.append(prices[q[0]])
    return result

# 2. Network Traffic Monitoring - Max Data Transfer in Sliding Interval
def max_network_traffic(data, k):
    """
    Calculates the maximum network traffic within a sliding window of size k.

    Args:
        data (list): A list of data transfer amounts per unit of time.
        k (int): The size of the sliding window.

    Returns:
        int: The maximum data transfer amount within any window of size k.
    """
    max_traffic = 0  # Initialize the maximum traffic.
    current_sum = sum(data[:k])  # Calculate the sum of the first k data points.
    max_traffic = current_sum  # Initialize max_traffic with the sum of the first window.

    for i in range(k, len(data)):
        # Slide the window: subtract the data leaving the window and add the data entering.
        current_sum += data[i] - data[i - k]
        max_traffic = max(max_traffic, current_sum)  # Update max_traffic if necessary.
    return max_traffic

# 3. Fraud Detection - Moving Average for Transaction Amounts
def moving_avg_fraud_detection(transactions, k):
    """
    Calculates the moving average of transaction amounts over a sliding window of size k.
    This can be used to detect unusual spikes or drops in transaction values, which
    might indicate fraudulent activity.

    Args:
        transactions (list): A list of transaction amounts.
        k (int): The size of the sliding window.

    Returns:
        list: A list of moving averages for each window.
    """
    avg_values = []  # Initialize a list to store the moving averages.
    current_sum = sum(transactions[:k])  # Calculate the sum of the first k transactions.
    avg_values.append(current_sum / k)  # Calculate and append the first moving average.

    for i in range(k, len(transactions)):
        # Slide the window: subtract the transaction leaving and add the transaction entering.
        current_sum += transactions[i] - transactions[i - k]
        avg_values.append(current_sum / k)  # Calculate and append the moving average.
    return avg_values

# 4. IoT Sensor Data Processing - Highest Temperature in Time Window
def highest_temperature(temperatures, k):
    """
    Finds the highest temperature within a sliding window of k time units.

    Args:
        temperatures (list): A list of temperature readings.
        k (int): The size of the sliding window.

    Returns:
        int: The highest temperature within any window of size k.
    """
    max_temp = float('-inf')  # Initialize max_temp to negative infinity.
    current_sum = sum(temperatures[:k])  # Calculate the sum of the first k temperatures.
    max_temp = current_sum # Initialize max_temp
    for i in range(k, len(temperatures)):
        # Slide the window: subtract the temperature leaving and add the temperature entering.
        current_sum += temperatures[i] - temperatures[i - k]
        max_temp = max(max_temp, current_sum)  # Update max_temp.
    return max_temp

# 5. User Engagement Analysis - Longest Session with High Activity
def longest_active_session(logins, k):
    """
    Finds the longest session (window of size k) with the highest number of active users.
    Assumes active users are those with login counts greater than 10.

    Args:
        logins (list): A list of login counts for each user.
        k (int): The size of the sliding window.

    Returns:
        int: The maximum number of active users in any window of size k.
    """
    active_count = sum(1 for x in logins[:k] if x > 10)  # Count active users in the first window.
    max_active = active_count  # Initialize max_active.

    for i in range(k, len(logins)):
        # Slide the window: adjust active_count based on users entering and leaving.
        if logins[i] > 10:
            active_count += 1
        if logins[i - k] > 10:
            active_count -= 1
        max_active = max(max_active, active_count)  # Update max_active.
    return max_active

# 6. Cybersecurity Threat Detection - Suspicious IP Requests in Sliding Window
def detect_suspicious_ips(requests, threshold, k):
    """
    Detects the number of suspicious IP requests (above a threshold) within a sliding window.

    Args:
        requests (list): A list of request counts for each IP address.
        threshold (int): The threshold for suspicious activity.
        k (int): The size of the sliding window.

    Returns:
        list: A list of suspicious request counts for each window.
    """
    suspicious_counts = []  # Initialize list to store counts of suspicious requests.
    current_count = sum(1 for x in requests[:k] if x > threshold)  # Count suspicious requests in first window
    suspicious_counts.append(current_count)  # Append the count for the first window.

    for i in range(k, len(requests)):
        # Slide the window: adjust suspicious_count based on requests entering and leaving.
        if requests[i] > threshold:
            current_count += 1
        if requests[i - k] > threshold:
            current_count -= 1
        suspicious_counts.append(current_count)  # Append the count for the current window.
    return suspicious_counts

# Test Cases
data_stream = [10, 20, 15, 30, 25, 10, 35, 40]
stock_prices = [100, 105, 102, 110, 108, 115, 120, 125]
transactions = [500, 300, 700, 400, 600, 800, 900, 1000]
temperatures = [20, 25, 30, 35, 28, 32, 40, 42]
logins = [5, 15, 8, 12, 20, 25, 30, 35]
requests = [50, 100, 200, 150, 250, 300, 400, 500]

k = 3
threshold = 200

print("Max Stock Prices in K Days:", max_stock_price(stock_prices, k))
print("Max Network Traffic:", max_network_traffic(data_stream, k))
print("Moving Average for Fraud Detection:", moving_avg_fraud_detection(transactions, k))
print("Highest Temperature in Time Window:", highest_temperature(temperatures, k))
print("Longest Active User Session:", longest_active_session(logins, k))
print("Suspicious IP Requests:", detect_suspicious_ips(requests, threshold, k))
