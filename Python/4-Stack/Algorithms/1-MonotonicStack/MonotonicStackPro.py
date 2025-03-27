'''
Advanced Monotonic Stack Applications - Real-World Implementations

Problem Statement:
A monotonic stack is a data structure that maintains elements in either increasing or decreasing order.
It is commonly used to optimize problems in various domains such as finance, cybersecurity, and AI.
'''

from collections import deque

# 1. Stock Price Monitoring (Next Greater Element - Monotonic Decreasing Stack)
def stock_price_monitor(prices):
    """
    Monitors stock prices to find the next day when the price is higher than the current day.
    This can be used to identify potential buying opportunities or upward trends.

    Args:
        prices (list): A list of stock prices for consecutive days.

    Returns:
        list: A list where each element represents the next higher price for the corresponding day.
              If there is no higher price in the future, -1 is stored.
    """
    stack = []  # Stack to store indices of days, maintained in decreasing price order.
    result = [-1] * len(prices)  # Initialize result with -1, indicating no higher price found yet.

    for i in range(len(prices)):  # Iterate through each day's price.
        while stack and prices[stack[-1]] < prices[i]:
            # While the stack is not empty and the current day's price is higher than the price at the top of the stack:
            result[stack.pop()] = prices[i]  # The current day is the next higher price day for the day at the top of the stack.
        stack.append(i)  # Push the current day's index onto the stack.
    return result

# 2. Network Latency Detection (Next Smaller Element - Monotonic Increasing Stack)
def detect_latency_spikes(latencies):
    """
    Detects network latency spikes by finding the next time a latency is lower than the current time.
    This can help identify transient network issues or performance bottlenecks.

    Args:
        latencies (list): A list of network latencies at consecutive time intervals.

    Returns:
        list: A list where each element represents the next lower latency for the corresponding time interval.
              If there is no lower latency in the future, -1 is stored.
    """
    stack = []  # Stack to store indices of time intervals, maintained in increasing latency order.
    result = [-1] * len(latencies)  # Initialize result with -1.

    for i in range(len(latencies)):
        while stack and latencies[stack[-1]] > latencies[i]:
            # While the stack is not empty and the current latency is lower than the latency at the top of the stack:
            result[stack.pop()] = latencies[i]  # The current time interval is the next lower latency time for the interval at the top of the stack.
        stack.append(i)
    return result

# 3. Weather Pattern Analysis (Previous Greater Element - Reverse Monotonic Decreasing Stack)
def analyze_weather_patterns(temperatures):
    """
    Analyzes weather patterns to find the previous day with a higher temperature than the current day.
    This can help in identifying trends or unusual temperature fluctuations.

    Args:
        temperatures (list): A list of daily temperatures.

    Returns:
        list: A list where each element represents the previous higher temperature for the corresponding day.
              If there is no higher temperature in the past, -1 is stored.
    """
    stack = []  # Stack to store temperatures, maintained in decreasing order from bottom to top.
    result = [-1] * len(temperatures)  # Initialize result with -1.

    for i in range(len(temperatures)-1, -1, -1):  # Iterate in reverse to find previous elements.
        while stack and stack[-1] < temperatures[i]:
            # While the stack is not empty and the top of the stack is lower than the current temperature:
            stack.pop()  # Pop elements that are not the previous greater temperature.
        result[i] = stack[-1] if stack else -1  # The top of the stack is the previous greater temperature, or -1 if stack is empty.
        stack.append(temperatures[i])
    return result

# 4. AI Chatbot Response Time Optimization (Previous Smaller Element - Reverse Monotonic Increasing Stack)
def chatbot_response_time(messages):
    """
    Optimizes chatbot response times by finding the previous message that took less time to process.
    This can help in identifying messages that are processed faster and potentially optimizing the processing of similar messages.

    Args:
        messages (list): A list of response times for consecutive messages.

    Returns:
        list: A list where each element represents the previous smaller response time for the corresponding message.
              If there is no smaller response time in the past, -1 is stored.
    """
    stack = []  # Stack to store response times, maintained in increasing order from bottom to top.
    result = [-1] * len(messages)  # Initialize result with -1.

    for i in range(len(messages)-1, -1, -1):
        while stack and stack[-1] > messages[i]:
            stack.pop()
        result[i] = stack[-1] if stack else -1
        stack.append(messages[i])
    return result

# 5. Load Balancer Optimization (Load Peak Detection using Monotonic Stack)
def optimize_load_balancer(loads):
    """
    Optimizes load balancing by detecting load peaks and their corresponding widths.  This information can be used
    to distribute traffic more evenly and prevent server overload.  This function calculates the largest rectangular
    area under a histogram of loads, where the x-axis represents time and the y-axis represents load.

    Args:
        loads (list): A list of server loads at consecutive time intervals.

    Returns:
        int: The maximum rectangular area, representing the peak load and its duration.
    """
    stack = []  # Stack to store indices of loads, representing bars of the histogram.
    max_area = 0
    loads.append(0)  # Sentinel value to ensure all bars are processed.

    for i, load in enumerate(loads):
        while stack and loads[stack[-1]] > load:
            height = loads[stack.pop()]
            width = i if not stack else i - stack[-1] - 1
            max_area = max(max_area, height * width)
        stack.append(i)
    return max_area

# 6. Cybersecurity - Detecting Anomalous Traffic Bursts
# Uses a stack to track peaks of abnormal network traffic

def detect_anomalous_traffic(traffic):
    """
    Detects anomalous traffic bursts by identifying significant increases in network traffic.
    This can help in identifying potential DDoS attacks or other network anomalies.

    Args:
        traffic (list): A list of network traffic values at consecutive time intervals.

    Returns:
        list: A list of tuples, where each tuple represents an anomaly zone (start index, end index).
    """
    stack = deque()  # Use a deque for efficient left removal (though not strictly necessary for this logic).
    anomaly_zones = []

    for i, value in enumerate(traffic):
        while stack and traffic[stack[-1]] < value:
            stack.pop()
        if stack and value - traffic[stack[-1]] > 10:  # Threshold difference to define an anomaly.
            anomaly_zones.append((stack[-1], i))  # Store the start and end of the anomaly zone.
        stack.append(i)

    return anomaly_zones

# Test Cases
prices = [100, 80, 120, 130, 90, 150]
print("Stock Price Monitoring:", stock_price_monitor(prices))

latencies = [50, 40, 60, 70, 30, 80]
print("Network Latency Detection:", detect_latency_spikes(latencies))

temperatures = [30, 25, 40, 35, 45, 20]
print("Weather Pattern Analysis:", analyze_weather_patterns(temperatures))

messages = [5, 8, 3, 6, 10, 2]
print("Chatbot Response Time Optimization:", chatbot_response_time(messages))

loads = [2, 1, 5, 6, 2, 3]
print("Load Balancer Optimization:", optimize_load_balancer(loads))

traffic = [100, 120, 80, 130, 140, 90, 200]
print("Cybersecurity - Anomalous Traffic Detection:", detect_anomalous_traffic(traffic))
