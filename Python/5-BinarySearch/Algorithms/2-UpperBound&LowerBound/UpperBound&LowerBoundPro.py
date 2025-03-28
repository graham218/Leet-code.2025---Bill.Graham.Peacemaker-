# Advanced Real-World Implementations of Binary Search for Upper & Lower Bound
# This script demonstrates six practical applications of binary search in real-world scenarios.

from bisect import bisect_left, bisect_right # Import the bisect functions
from typing import List, Dict # Import List and Dict for type hinting
import numpy as np # Import numpy
from datetime import datetime # Import datetime for handling time data

# 1. Finding the Earliest and Latest Available Booking Time (Lower & Upper Bound on Time Slots)
def find_booking_slot(slots: List[str], target_time: str) -> Dict[str, str]:
    """
    Finds the earliest and latest available booking time slots relative to a target time, using binary search.

    Args:
        slots: A sorted list of booking time slots represented as strings in "HH:MM" format (e.g., ["09:00", "10:30", "12:00"]).
        target_time: The target time to compare against, also in "HH:MM" format.

    Returns:
        A dictionary containing the earliest and latest available slots:
        {
            "earliest_available": The first slot that is >= target_time, or "No slots available" if none exist.
            "latest_available": The last slot that is <= target_time, or "No earlier slot available" if none exist.
        }

    Example:
        slots = ["09:00", "10:30", "12:00", "14:00", "16:30"]
        target_time = "12:30"
        find_booking_slot(slots, target_time) == {'earliest_available': '14:00', 'latest_available': '12:00'}
    """
    slots_dt = [datetime.strptime(slot, "%H:%M") for slot in slots] # Convert time strings to datetime objects for comparison
    target_dt = datetime.strptime(target_time, "%H:%M") # Convert the target time string to a datetime object
    lower_idx = bisect_left(slots_dt, target_dt) # Find the index of the first slot >= target_time
    upper_idx = bisect_right(slots_dt, target_dt) # Find the index of the first slot > target_time
    return {
        "earliest_available": slots[lower_idx] if lower_idx < len(slots) else "No slots available", # Get the time slot string.
        "latest_available": slots[upper_idx - 1] if upper_idx > 0 else "No earlier slot available" # upper_idx - 1 gives the last slot <= target_time
    }

# 2. Searching for a Stock Price Before & After a Given Time
def search_stock_price(stock_data: List[Dict[str, float]], target_time: str) -> Dict[str, float]:
    """
    Searches for stock prices in a sorted list of stock data and finds the prices immediately before and after a given time.

    Args:
        stock_data: A sorted list of dictionaries, where each dictionary contains stock "time" (string in "YYYY-MM-DD HH:MM:SS" format) and "price" (float).
        target_time: The target time to search around (string in "YYYY-MM-DD HH:MM:SS" format).

    Returns:
        A dictionary containing the stock data for the times immediately before and after the target time:
        {
            "earliest": The stock data dictionary for the time just before target_time, or None if no such time exists.
            "latest": The stock data dictionary for the time just after target_time, or None if no such time exists.
        }

    Example:
        stock_data = [{"time": "2025-03-28 09:00:00", "price": 150.5},
                      {"time": "2025-03-28 12:00:00", "price": 153.2}]
        target_time = "2025-03-28 10:00:00"
        search_stock_price(stock_data, target_time) == {'earliest': {'time': '2025-03-28 09:00:00', 'price': 150.5}, 'latest': {'time': '2025-03-28 12:00:00', 'price': 153.2}}
    """
    timestamps = [datetime.strptime(stock["time"], "%Y-%m-%d %H:%M:%S") for stock in stock_data] # Extract and convert timestamps to datetime
    target_dt = datetime.strptime(target_time, "%Y-%m-%d %H:%M:%S") # Convert target time to datetime
    lower_idx = bisect_left(timestamps, target_dt) # Find the index of the first timestamp >= target_time
    upper_idx = bisect_right(timestamps, target_dt) # Find the index of the first timestamp > target_time
    return {
        "earliest": stock_data[lower_idx - 1] if lower_idx > 0 else None, # index - 1 is the price just before.
        "latest": stock_data[upper_idx] if upper_idx < len(stock_data) else None # index is the price just after
    }

# 3. Finding the First and Last Occurrence of a Log Entry with a Given Severity Level
def search_log_entries(logs: List[Dict[str, str]], severity: str) -> Dict[str, str]:
    """
    Finds the first and last log entries with a specific severity level.

    Args:
        logs: A sorted list of dictionaries, where each dictionary represents a log entry and contains "timestamp" (string) and "severity" (string).  The list is sorted by severity.
        severity: The severity level to search for (string, e.g., "INFO", "ERROR").

    Returns:
        A dictionary containing the first and last log entries with the specified severity:
        {
            "first_occurrence": The first log entry with the matching severity, or "Not Found" if none exist.
            "last_occurrence": The last log entry with the matching severity, or "Not Found" if none exist.
        }

    Example:
        logs = [{"timestamp": "2025-03-28 08:00:00", "severity": "INFO"},
                {"timestamp": "2025-03-28 09:15:00", "severity": "ERROR"},
                {"timestamp": "2025-03-28 10:00:00", "severity": "ERROR"}]
        search_log_entries(logs, "ERROR") == {'first_occurrence': {'timestamp': '2025-03-28 09:15:00', 'severity': 'ERROR'}, 'last_occurrence': {'timestamp': '2025-03-28 10:00:00', 'severity': 'ERROR'}}
    """
    severities = [log["severity"] for log in logs] # Extract the severity levels from the log entries
    lower_idx = bisect_left(severities, severity) # Find the first occurrence of the severity
    upper_idx = bisect_right(severities, severity) # Find the position after the last occurrence
    return {
        "first_occurrence": logs[lower_idx] if lower_idx < len(logs) else "Not Found", #  logs[lower_idx] is the first occurrence
        "last_occurrence": logs[upper_idx - 1] if upper_idx > 0 else "Not Found" # logs[upper_idx - 1] is the last occurrence
    }

# 4. Identifying the First and Last Matching Customer Order in a Sorted List
def find_customer_orders(orders: List[Dict[str, str]], customer_id: str) -> Dict[str, str]:
    """
    Finds the first and last order for a given customer ID in a sorted list of orders.

    Args:
        orders: A sorted list of dictionaries, where each dictionary represents an order and contains "customer_id" (string) and "order_id" (string).
               The list is sorted by customer_id.
        customer_id: The customer ID to search for.

    Returns:
        A dictionary containing the first and last order for the customer:
        {
            "first_order": The first order dictionary for the given customer, or "No orders found" if none exist.
            "last_order": The last order dictionary for the given customer, or "No orders found" if none exist.
        }

    Example:
        orders = [{"customer_id": "A123", "order_id": "1001"},
                  {"customer_id": "A123", "order_id": "1002"},
                  {"customer_id": "B456", "order_id": "2001"}]
        find_customer_orders(orders, "A123") == {'first_order': {'customer_id': 'A123', 'order_id': '1001'}, 'last_order': {'customer_id': 'A123', 'order_id': '1002'}}
    """
    customer_ids = [order["customer_id"] for order in orders] # Extract customer IDs
    lower_idx = bisect_left(customer_ids, customer_id) # Find the first order for this customer
    upper_idx = bisect_right(customer_ids, customer_id) # Find the position after the last order
    return {
        "first_order": orders[lower_idx] if lower_idx < len(orders) else "No orders found", # First order
        "last_order": orders[upper_idx - 1] if upper_idx > 0 else "No orders found" # Last order
    }

# 5. Locating Nearest Sensor Data Before and After a Given Value
def find_nearest_sensor_reading(sensor_data: List[float], target_value: float) -> Dict[str, float]:
    """
    Finds the sensor data values immediately before and after a given target value in a sorted list of sensor readings.

    Args:
        sensor_data: A sorted list of sensor data values (floats).
        target_value: The target value (float).

    Returns:
        A dictionary containing the closest sensor readings:
        {
            "closest_lower": The sensor reading just below the target_value, or None if no such reading exists.
            "closest_upper": The sensor reading just above the target_value, or None if no such reading exists.
        }
    Example:
        sensor_readings = [0.1, 1.5, 2.3, 3.8, 5.0, 6.7]
        target_value = 4.0
        find_nearest_sensor_reading(sensor_readings, 4.0) == {'closest_lower': 3.8, 'closest_upper': 5.0}
    """
    lower_idx = bisect_left(sensor_data, target_value) #  Find the insertion point
    upper_idx = bisect_right(sensor_data, target_value)
    return {
        "closest_lower": sensor_data[lower_idx - 1] if lower_idx > 0 else None, # The value before the insertion point
        "closest_upper": sensor_data[upper_idx] if upper_idx < len(sensor_data) else None # The value at the insertion point
    }

# 6. AI Model Predictions: Finding the Closest Confidence Score Before & After a Given Threshold
def find_prediction_threshold(predictions: List[Dict[str, float]], threshold: float) -> Dict[str, float]:
    """
    Finds the AI model prediction confidence scores closest to and on either side of a given threshold.

    Args:
        predictions: A list of dictionaries, where each dictionary represents an AI prediction and contains a "confidence" score (float).
        threshold: The confidence threshold (float).

    Returns:
        A dictionary containing the confidence scores:
        {
            "lower_bound_prediction": The confidence score just below the threshold, or None if no such score exists.
            "upper_bound_prediction": The confidence score just above the threshold, or None if no such score exists.
        }
    Example:
        predictions = [{"confidence": 0.65}, {"confidence": 0.75}, {"confidence": 0.85}]
        threshold = 0.70
        find_prediction_threshold(predictions, 0.70) == {'lower_bound_prediction': 0.65, 'upper_bound_prediction': 0.75}
    """
    scores = [pred["confidence"] for pred in predictions] # Extract confidence scores.
    scores.sort() # Sort the scores
    lower_idx = bisect_left(scores, threshold) # Find insertion point
    upper_idx = bisect_right(scores, threshold)
    return {
        "lower_bound_prediction": scores[lower_idx - 1] if lower_idx > 0 else None, # The score before insertion point
        "upper_bound_prediction": scores[upper_idx] if upper_idx < len(scores) else None # The score at the insertion point
    }

# Sample Data for Testing
booking_slots = ["09:00", "10:30", "12:00", "14:00", "16:30"]
stock_prices = [{"time": "2025-03-28 09:00:00", "price": 150.5},
                {"time": "2025-03-28 12:00:00", "price": 153.2}]
log_entries = [{"timestamp": "2025-03-28 08:00:00", "severity": "INFO"},
               {"timestamp": "2025-03-28 09:15:00", "severity": "ERROR"}]
customer_orders = [{"customer_id": "A123", "order_id": "1001"},
                   {"customer_id": "A123", "order_id": "1002"}]
sensor_readings = [0.1, 1.5, 2.3, 3.8, 5.0, 6.7]
predictions = [{"confidence": 0.65}, {"confidence": 0.75}, {"confidence": 0.85}]

# Run Tests
print("Booking Slot:", find_booking_slot(booking_slots, "12:30"))
print("Stock Price:", search_stock_price(stock_prices, "2025-03-28 10:00:00"))
print("Log Entries:", search_log_entries(log_entries, "ERROR"))
print("Customer Orders:", find_customer_orders(customer_orders, "A123"))
print("Nearest Sensor Reading:", find_nearest_sensor_reading(sensor_readings, 4.0))
print("AI Prediction Threshold:", find_prediction_threshold(predictions, 0.70))
