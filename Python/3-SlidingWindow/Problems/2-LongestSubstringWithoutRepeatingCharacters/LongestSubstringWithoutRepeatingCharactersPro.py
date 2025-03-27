'''
Advanced Sliding Window: Longest Substring Without Repeating Characters - Real-World Applications

Problem Statement:
Find the length of the longest substring without repeating characters using real-world scenarios.
'''

# 1. Network Packet Processing (O(n))
def longest_unique_packet_sequence(packets):
    """
    Finds the longest sequence of unique packets in a network stream.  This is useful for identifying
    anomalies or patterns of unique data within network traffic, which can be crucial for network optimization
    and security.

    Args:
        packets (list): A list of packet identifiers (e.g., packet IDs, source IPs).

    Returns:
        int: The length of the longest sequence of unique packets.
    """
    packet_set = set()  # Use a set to track unique packets in the current window.
    left = 0  # Initialize the left pointer of the sliding window.
    max_length = 0  # Initialize the maximum length of the unique sequence.
    for right in range(len(packets)):  # Iterate through the packets using the right pointer.
        while packets[right] in packet_set:  # If the current packet is already in the set (duplicate),
            packet_set.remove(packets[left])  # Remove the leftmost packet from the set.
            left += 1  # Shrink the window from the left.
        packet_set.add(packets[right])  # Add the current packet to the set.
        max_length = max(max_length, right - left + 1)  # Update max_length with the current window size.
    return max_length  # Return the maximum length of the unique packet sequence.

# 2. Unique User Session Tracking (O(n))
def longest_unique_user_session(logins):
    """
    Determines the longest unique user session, where a session is defined as a sequence of unique user logins.
    This can be used to track user activity patterns and identify unusual login sequences, which may be relevant
    for security or user behavior analysis.

    Args:
        logins (list): A list of user login IDs.

    Returns:
        int: The length of the longest unique user session.
    """
    user_index = {}  # Use a dictionary to store the last seen index of each user.
    left = 0  # Initialize the left pointer of the sliding window.
    max_length = 0  # Initialize the maximum length of the unique session.
    for right in range(len(logins)):  # Iterate through the login attempts.
        if logins[right] in user_index and user_index[logins[right]] >= left:
            # If the current user has logged in before within the current window:
            left = user_index[logins[right]] + 1  # Move the left pointer after the previous login.
        user_index[logins[right]] = right  # Update the last seen index for the current user.
        max_length = max(max_length, right - left + 1)  # Update max_length.
    return max_length  # Return the maximum length of the unique user session.

# 3. IoT Sensor Data Optimization (O(n))
def longest_unique_sensor_readings(readings):
    """
    Finds the longest sequence of unique sensor readings.  In IoT applications, this can be used to identify
    periods of stable, non-repeating data, which can be useful for calibrating models or detecting anomalies
    in sensor behavior.

    Args:
        readings (list): A list of sensor readings.

    Returns:
        int: The length of the longest sequence of unique sensor readings.
    """
    reading_map = {}  # Use a dictionary to store the last seen index of each reading.
    left = 0  # Initialize the left pointer of the sliding window.
    max_length = 0  # Initialize the maximum length.
    for right in range(len(readings)):  # Iterate through the sensor readings.
        if readings[right] in reading_map and reading_map[readings[right]] >= left:
            # If the current reading has appeared before in the current window:
            left = reading_map[readings[right]] + 1  # Move the left pointer.
        reading_map[readings[right]] = right  # Update the last seen index.
        max_length = max(max_length, right - left + 1)  # Update max_length.
    return max_length  # Return the maximum length.

# 4. Fraud Detection in Transactions (O(n))
def longest_unique_transaction_pattern(transactions):
    """
    Identifies the longest sequence of unique transactions.  This can be used to detect fraudulent activities
    by looking for repeated transaction patterns within a certain timeframe.  A long sequence of unique
    transactions might be considered less suspicious than a short sequence with many repetitions.

    Args:
        transactions (list): A list of transaction IDs or transaction fingerprints.

    Returns:
        int: The length of the longest sequence of unique transactions.
    """
    transaction_set = set()  # Use a set to track unique transactions in the current window.
    left = 0  # Initialize the left pointer.
    max_length = 0  # Initialize the maximum length.
    for right in range(len(transactions)):  # Iterate through the transactions.
        while transactions[right] in transaction_set:  # If the transaction is a duplicate:
            transaction_set.remove(transactions[left])  # Remove the leftmost transaction.
            left += 1  # Shrink the window.
        transaction_set.add(transactions[right])  # Add the current transaction to the set.
        max_length = max(max_length, right - left + 1)  # Update max_length.
    return max_length  # Return the maximum length.

# 5. Streaming Content Recommendation (O(n))
def longest_unique_content_stream(streamed_content):
    """
    Finds the longest sequence of unique content items in a streaming session.  This can be used to optimize
    content recommendations by ensuring that users are not shown the same content repeatedly within a short period,
    leading to a better user experience.

    Args:
        streamed_content (list): A list of content IDs or content titles.

    Returns:
        int: The length of the longest sequence of unique content items.
    """
    content_map = {}  # Use a dictionary to store the last seen index of each content item.
    left = 0  # Initialize the left pointer.
    max_length = 0  # Initialize the maximum length.
    for right in range(len(streamed_content)):  # Iterate through the streamed content.
        if streamed_content[right] in content_map and content_map[streamed_content[right]] >= left:
            # If the content has been seen before in the current window:
            left = content_map[streamed_content[right]] + 1  # Move the left pointer.
        content_map[streamed_content[right]] = right  # Update the last seen index.
        max_length = max(max_length, right - left + 1)  # Update max_length.
    return max_length  # Return the maximum length.

# 6. Cybersecurity Intrusion Detection (O(n))
def longest_unique_intrusion_pattern(log_patterns):
    """
    Identifies the longest sequence of unique log patterns in a system log.  This can be used to detect
    unusual or suspicious activity, as repeated log patterns might indicate an intrusion or an attack.

    Args:
        log_patterns (list): A list of log patterns or log entries.

    Returns:
        int: The length of the longest sequence of unique log patterns.
    """
    pattern_map = {}  # Use a dictionary to store the last seen index of each log pattern.
    left = 0  # Initialize the left pointer.
    max_length = 0  # Initialize the maximum length.
    for right in range(len(log_patterns)):  # Iterate through the log patterns.
        if log_patterns[right] in pattern_map and pattern_map[log_patterns[right]] >= left:
            # If the log pattern has been seen before in the current window:
            left = pattern_map[log_patterns[right]] + 1  # Move the left pointer.
        pattern_map[log_patterns[right]] = right  # Update the last seen index.
        max_length = max(max_length, right - left + 1)  # Update max_length.
    return max_length  # Return the maximum length.

# Test Cases
data = ["A", "B", "C", "A", "D", "E", "B", "F", "G", "H"]
print("Network Packet Processing:", longest_unique_packet_sequence(data))
print("Unique User Session Tracking:", longest_unique_user_session(data))
print("IoT Sensor Data Optimization:", longest_unique_sensor_readings(data))
print("Fraud Detection:", longest_unique_transaction_pattern(data))
print("Content Streaming:", longest_unique_content_stream(data))
print("Cybersecurity Intrusion Detection:", longest_unique_intrusion_pattern(data))
