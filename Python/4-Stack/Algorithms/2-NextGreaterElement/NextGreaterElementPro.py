'''
Advanced Next Greater Element - Real-World Implementations

Problem Statement:
The Next Greater Element (NGE) for an element in an array is the first greater element found to its right.
If no greater element exists, return -1.
This concept is widely used in real-world applications such as stock price analysis, CPU scheduling, and AI prediction models.
'''

from collections import deque # Import deque, although it is not used.

# 1. Stock Market Prediction (Next Greater Closing Price)
def stock_market_prediction(prices):
    """
    Predicts the next greater closing price for each day, which can help in identifying upward trends.

    Args:
        prices: A list of stock closing prices for each day.

    Returns:
        A list where each element represents the next greater closing price for the corresponding day,
        or -1 if no greater price occurs in the future.
    """
    stack = []  # Initialize an empty stack to store stock prices (or indices).
    result = [-1] * len(prices)  # Initialize the result array with -1.
    for i in range(len(prices) - 1, -1, -1):  # Iterate through the prices from the last day to the first.
        while stack and stack[-1] <= prices[i]:  # While the stack is not empty and the top price is less than or equal to the current price...
            stack.pop()  # ...pop the top price (it's not the next greater).
        result[i] = stack[-1] if stack else -1  # The next greater price is at the top of the stack (if any).
        stack.append(prices[i])  # Push the current day's price onto the stack.
    return result  # Return the array of next greater prices.

# 2. CPU Scheduling Optimization (Next Higher CPU Load)
def cpu_scheduling(loads):
    """
    Optimizes CPU scheduling by finding the next higher CPU load for each time slot.
    This can help in proactive resource allocation and preventing overload.

    Args:
        loads: A list of CPU loads at different time slots.

    Returns:
        A list where each element represents the next higher CPU load for the corresponding time slot,
        or -1 if no higher load occurs later.
    """
    stack = []  # Initialize an empty stack to store CPU loads.
    result = [-1] * len(loads)  # Initialize the result array with -1.
    for i in range(len(loads) - 1, -1, -1):  # Iterate through the loads from the last time slot to the first.
        while stack and stack[-1] <= loads[i]:  # While the stack is not empty and the top load is less than or equal to the current load...
            stack.pop()  # ...pop the top load.
        result[i] = stack[-1] if stack else -1  # The next greater load is at the top of the stack (if any).
        stack.append(loads[i])  # Push the current load onto the stack.
    return result  # Return the array of next greater loads.

# 3. AI Model Performance Analysis (Detect Next Peak Accuracy)
def ai_performance(accuracies):
    """
    Analyzes AI model performance by detecting the next peak accuracy.
    This helps in identifying when the model is improving and when it starts to decline.

    Args:
        accuracies: A list of AI model accuracies at different training epochs or iterations.

    Returns:
        A list where each element represents the next peak accuracy,
        or -1 if no higher accuracy is achieved later.
    """
    stack = []  # Initialize an empty stack to store model accuracies.
    result = [-1] * len(accuracies)  # Initialize the result array with -1.
    for i in range(len(accuracies) - 1, -1, -1):  # Iterate through the accuracies from the last epoch to the first.
        while stack and stack[-1] <= accuracies[i]:  # While the stack is not empty and the top accuracy is less than or equal to the current accuracy...
            stack.pop()  # ...pop the top accuracy.
        result[i] = stack[-1] if stack else -1  # The next greater accuracy is at the top of the stack (if any).
        stack.append(accuracies[i])  # Push the current accuracy onto the stack.
    return result  # Return the array of next greater accuracies.

# 4. Weather Forecasting (Next Warmer Day)
def weather_forecasting(temperatures):
    """
    Predicts the next warmer day for each day, which is useful for planning and agriculture.

    Args:
        temperatures: A list of daily temperatures.

    Returns:
        A list where each element represents the temperature of the next warmer day,
        or -1 if no warmer day occurs in the future.
    """
    stack = []  # Initialize an empty stack to store temperatures.
    result = [-1] * len(temperatures)  # Initialize the result array with -1.
    for i in range(len(temperatures) - 1, -1, -1):  # Iterate through the temperatures from the last day to the first.
        while stack and stack[-1] <= temperatures[i]:  # While the stack is not empty and the top temperature is less than or equal to the current temperature...
            stack.pop()  # ...pop the top temperature.
        result[i] = stack[-1] if stack else -1  # The next greater temperature is at the top of the stack (if any).
        stack.append(temperatures[i])  # Push the current day's temperature onto the stack.
    return result  # Return the array of next greater temperatures.

# 5. E-Commerce Price Tracking (Next Price Drop Detection)
def ecommerce_price_tracking(prices):
    """
    Detects the next price drop for each day.  Note that this is the *opposite* of NGE.

    Args:
        prices: A list of prices of a product over time.

    Returns:
        A list where each element represents the price at the next time the price drops,
        or -1 if no price drop occurs in the future.
    """
    stack = []  # Initialize an empty stack to store prices.
    result = [-1] * len(prices)  # Initialize the result array with -1.
    for i in range(len(prices) - 1, -1, -1):  # Iterate through the prices from the last day to the first.
        while stack and stack[-1] >= prices[i]:  # While the stack is not empty and the top price is greater than or equal to the current price...
            stack.pop()  # ...pop the top price.
        result[i] = stack[-1] if stack else -1  # The next *lower* price is at the top of the stack (if any).
        stack.append(prices[i])  # Push the current price onto the stack.
    return result  # Return the result array.

# 6. Cybersecurity Anomaly Detection (Next Higher Traffic Spike)
def cybersecurity_traffic_spikes(traffic):
    """
    Detects the next higher traffic spike in network traffic data, which can indicate potential security threats.

    Args:
        traffic: A list of network traffic volumes at different times.

    Returns:
        A list where each element represents the next higher traffic volume,
        or -1 if no higher volume occurs later.
    """
    stack = []  # Initialize an empty stack to store traffic volumes.
    result = [-1] * len(traffic)  # Initialize the result array with -1.
    for i in range(len(traffic) - 1, -1, -1):  # Iterate through the traffic volumes from the last time to the first.
        while stack and stack[-1] <= traffic[i]:  # While the stack is not empty and the top volume is less than or equal to the current volume...
            stack.pop()  # ...pop the top volume.
        result[i] = stack[-1] if stack else -1  # The next greater volume is at the top of the stack (if any).
        stack.append(traffic[i])  # Push the current traffic volume onto the stack.
    return result  # Return the result array.
# Test Cases
prices = [100, 80, 120, 130, 90, 150]
print("Stock Market Prediction:", stock_market_prediction(prices))

loads = [40, 50, 45, 60, 30, 70]
print("CPU Scheduling Optimization:", cpu_scheduling(loads))

accuracies = [0.85, 0.87, 0.80, 0.90, 0.88]
print("AI Model Performance:", ai_performance(accuracies))

temperatures = [30, 25, 40, 35, 45, 20]
print("Weather Forecasting:", weather_forecasting(temperatures))

price_drops = [500, 450, 480, 400, 420, 390]
print("E-Commerce Price Tracking:", ecommerce_price_tracking(price_drops))

traffic_spikes = [200, 250, 220, 270, 230, 300]
print("Cybersecurity Traffic Spike Detection:", cybersecurity_traffic_spikes(traffic_spikes))
