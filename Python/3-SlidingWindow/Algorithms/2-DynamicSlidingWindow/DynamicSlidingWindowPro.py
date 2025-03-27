'''
Advanced Dynamic Sliding Window - Real-World Implementations

Problem Statement:
Implement real-world use cases using the dynamic sliding window technique with six different approaches.
'''

# 1. Adaptive Rate Limiting (API Throttling) - (O(n))
def rate_limiter(request_timestamps, limit, window_size):
    """
    Implements adaptive rate limiting using a dynamic sliding window.  It checks if the number of requests
    within a given time window exceeds a defined limit.

    Args:
        request_timestamps (list): A list of timestamps for incoming API requests (assumed to be sorted).
        limit (int): The maximum number of requests allowed within the window.
        window_size (int): The time window size (in seconds, or any consistent time unit).

    Returns:
        bool: True if the requests are within the limit, False otherwise.
    """
    left = 0  # Initialize the left pointer of the sliding window.
    for right in range(len(request_timestamps)):  # Iterate through the request timestamps using the right pointer.
        # Shrink the window from the left until all requests in the window are within the time window.
        while request_timestamps[right] - request_timestamps[left] >= window_size:
            left += 1  # Move the left pointer to the right, effectively shrinking the window.
        # Check if the number of requests in the current window exceeds the limit.
        if right - left + 1 > limit:
            return False  # Rate limit exceeded: return False.
    return True  # All requests are within the limit: return True.

# 2. Video Buffering Optimization - (O(n))
def min_buffer_window(frames, min_quality):
    """
    Determines the minimum number of video frames needed in a buffer to ensure a minimum quality level
    during playback.  This helps optimize buffering time and reduce playback interruptions.

    Args:
        frames (list): A list representing the quality of each video frame.  Higher values mean higher quality.
        min_quality (int): The minimum acceptable quality level.

    Returns:
        int: The minimum number of frames needed in the buffer, or 0 if the required quality cannot be met.
    """
    left = 0  # Initialize the left pointer of the sliding window.
    current_quality = 0  # Initialize the sum of the quality of frames in the current window.
    min_len = float('inf')  # Initialize min_len to infinity.

    for right in range(len(frames)):  # Iterate through the frames using the right pointer.
        current_quality += frames[right]  # Add the quality of the current frame to the window.
        # Shrink the window from the left while the current quality is sufficient.
        while current_quality >= min_quality:
            min_len = min(min_len, right - left + 1)  # Update min_len if the current window is smaller.
            current_quality -= frames[left]  # Subtract the quality of the frame leaving the window.
            left += 1  # Move the left pointer to shrink the window.

    return min_len if min_len != float('inf') else 0  # Return the minimum window length, or 0 if no such window exists.

# 3. Anomaly Detection in Financial Transactions - (O(n log n))
from bisect import bisect_left

def detect_anomalous_transactions(transactions, threshold):
    """
    Detects anomalous financial transactions using a dynamic sliding window and prefix sums with binary search.
    An anomaly is defined as a transaction that, when added to the sum of preceding transactions
    within a window, exceeds a given threshold.  This implementation is not a standard sliding window,
    and it's not very efficient, but it uses the dynamic window concept.  A standard sliding window
    would be more efficient here.

    Args:
        transactions (list): A list of transaction amounts.
        threshold (int): The threshold for detecting anomalous transactions.

    Returns:
        list: A list of anomalous transaction amounts.
    """
    prefix_sums = [0] * (len(transactions) + 1)  # Create an array to store prefix sums.
    for i in range(1, len(transactions) + 1):
        prefix_sums[i] = prefix_sums[i - 1] + transactions[i - 1]  # Calculate prefix sums.

    anomalies = []  # Initialize a list to store anomalous transactions.
    for i in range(len(transactions)):
        target_sum = prefix_sums[i] + threshold  # Calculate the target sum (previous transactions + threshold).
        # Use binary search to find if there's a prefix sum that exceeds the target.
        bound = bisect_left(prefix_sums, target_sum)
        if bound <= len(transactions):
            anomalies.append(transactions[i])  # If found, the current transaction is considered anomalous.
    return anomalies

# 4. Smart Home Energy Consumption Control - (O(n))
def min_energy_window(consumption, max_usage):
    """
    Determines the minimum time window during which energy consumption exceeds a maximum usage limit
    in a smart home system.  This helps identify periods of high energy consumption.

    Args:
        consumption (list): A list of energy consumption values per time unit.
        max_usage (int): The maximum allowed energy usage.

    Returns:
        int: The minimum time window length, or 0 if the usage never exceeds the limit.
    """
    left = 0  # Initialize the left pointer of the sliding window.
    current_usage = 0  # Initialize the current energy usage within the window.
    min_len = float('inf')  # Initialize min_len to infinity.
    for right in range(len(consumption)):  # Iterate through the consumption data.
        current_usage += consumption[right]  # Add the current consumption to the window.
        # Shrink the window from the left while the usage exceeds the limit.
        while current_usage >= max_usage:
            min_len = min(min_len, right - left + 1)  # Update min_len.
            current_usage -= consumption[left]  # Subtract the consumption leaving the window.
            left += 1  # Move the left pointer.
    return min_len if min_len != float('inf') else 0  # Return the minimum window length, or 0.

# 5. Dynamic Spam Detection in Emails - (O(n))
def spam_detection(email_scores, spam_threshold):
    """
    Detects spam emails using a dynamic sliding window.  It finds the largest window where the number of emails
    with a spam score above a threshold exceeds the threshold itself.

    Args:
        email_scores (list): A list of spam scores for each email.
        spam_threshold (int): The threshold above which an email is considered spam, and also the max allowed spam emails.

    Returns:
        int: The length of the largest window with more than spam_threshold spam emails.
    """
    left = 0  # Initialize the left pointer.
    current_spam_count = 0  # Initialize the count of spam emails in the current window.
    max_spam_window = 0  # Initialize the maximum spam window length.
    for right in range(len(email_scores)):  # Iterate through the email scores.
        if email_scores[right] >= spam_threshold:  # If the current email is spam:
            current_spam_count += 1  # Increment the spam count.
        # Shrink the window from the left to maintain the spam threshold.
        while current_spam_count > spam_threshold:
            if email_scores[left] >= spam_threshold:  # If the email leaving the window is spam:
                current_spam_count -= 1  # Decrement the spam count.
            left += 1  # Move the left pointer.
        max_spam_window = max(max_spam_window, right - left + 1)  # Update the maximum spam window length.
    return max_spam_window

# 6. AI Model Data Preprocessing - (O(n))
def preprocess_sensor_data(sensor_readings, noise_threshold):
    """
    Preprocesses sensor data to find the largest valid window where the cumulative noise level
    (absolute value of readings) is below a given threshold.  This helps identify clean data segments
    for training AI models.

    Args:
        sensor_readings (list): A list of sensor readings (can be positive or negative).
        noise_threshold (int): The maximum allowed cumulative noise level.

    Returns:
        int: The length of the largest valid data window.
    """
    left = 0  # Initialize the left pointer.
    current_noise_level = 0  # Initialize the current noise level.
    valid_window = 0  # Initialize the length of the largest valid window.
    for right in range(len(sensor_readings)):  # Iterate through the sensor readings.
        current_noise_level += abs(sensor_readings[right])  # Add the noise level of the current reading.
        # Shrink the window from the left if the noise level exceeds the threshold.
        while current_noise_level > noise_threshold:
            current_noise_level -= abs(sensor_readings[left])  # Subtract the noise level of the reading leaving.
            left += 1  # Move the left pointer.
        valid_window = max(valid_window, right - left + 1)  # Update the length of the valid window.
    return valid_window

# Test Cases
requests = [1, 3, 5, 7, 10, 15]
frames = [4, 2, 1, 5, 3, 8]
transactions = [200, 500, 1000, 400, 900]
consumption = [100, 50, 120, 60, 80, 90]
email_scores = [3, 8, 2, 7, 10, 15, 20]
sensor_readings = [-2, 4, -3, 8, -1, 6]

print("API Rate Limiting:", rate_limiter(requests, 3, 10))
print("Min Buffer Window:", min_buffer_window(frames, 10))
print("Anomalous Transactions:", detect_anomalous_transactions(transactions, 1000))
print("Min Energy Window:", min_energy_window(consumption, 200))
print("Spam Detection Window:", spam_detection(email_scores, 10))
print("Valid Sensor Data Window:", preprocess_sensor_data(sensor_readings, 5))
