# Advanced Real-World Implementations of Binary Search

from bisect import bisect_left, bisect_right  # Import bisect_left and bisect_right for efficient searching in sorted sequences
from typing import List, Dict  # Import List and Dict for type hinting, improving code readability and maintainability
import numpy as np  # Import NumPy for efficient array operations, especially for large datasets

# 1. Binary Search in a Database (Simulated with a Dictionary)
def binary_search_database(records: Dict[int, str], target_id: int) -> str:
    """
    Simulates a binary search in a database (using a sorted dictionary).

    Args:
        records: A dictionary representing database records, where keys are sorted IDs (integers) and values are the corresponding data (strings).
        target_id: The ID to search for (integer).

    Returns:
        The data associated with the target_id if found, otherwise "Record not found".

    Example:
        records = {1001: "Alice", 1002: "Bob", 1003: "Charlie"}
        binary_search_database(records, 1002) == "Bob"
    """
    keys = sorted(records.keys())  # Sort the keys to simulate an indexed database (binary search requires sorted data)
    left, right = 0, len(keys) - 1  # Initialize left and right pointers for the binary search
    while left <= right:
        mid = left + (right - left) // 2  # Calculate the middle index to avoid potential overflow
        if keys[mid] == target_id:
            return records[keys[mid]]  # Target found: return the value (record) associated with the key
        elif keys[mid] < target_id:
            left = mid + 1  # If the middle key is less than the target, search the right half
        else:
            right = mid - 1  # If the middle key is greater than the target, search the left half
    return "Record not found"  # Target ID not found in the database

# 2. Searching for a Product in an E-commerce Price Range (Using Bisect)
def search_product_price_range(prices: List[int], target: int) -> int:
    """
    Searches for a product within a list of prices using binary search (bisect_left).

    Args:
        prices: A sorted list of product prices (integers).
        target: The target price to search for (integer).

    Returns:
        The index of the target price if found, otherwise -1.

    Example:
        prices = [10, 20, 30, 40, 50]
        search_product_price_range(prices, 30) == 2
    """
    index = bisect_left(prices, target)  # Use bisect_left to find the insertion point for the target
    if index < len(prices) and prices[index] == target:
        return index  # Target found at the insertion point
    return -1  # Target price not found

# 3. Binary Search in a Large Sorted NumPy Dataset (Optimized for Performance)
def binary_search_numpy(arr: np.ndarray, target: int) -> int:
    """
    Performs binary search in a large sorted NumPy array using np.searchsorted for optimized performance.

    Args:
        arr: A sorted NumPy array of integers.
        target: The target value to search for (integer).

    Returns:
        The index of the target value if found, otherwise -1.

    Example:
        arr = np.array([1, 3, 5, 7, 9, 11, 13, 15])
        binary_search_numpy(arr, 7) == 3
    """
    index = np.searchsorted(arr, target)  # Use np.searchsorted, which is optimized for NumPy arrays
    if index < len(arr) and arr[index] == target:
        return index  # Target found
    return -1  # Target not found

# 4. Searching Logs for a Specific Timestamp
from datetime import datetime  # Import the datetime module for handling timestamps

def search_log_timestamp(logs: List[Dict[str, str]], target_time: str) -> Dict[str, str]:
    """
    Searches for a specific timestamp within a list of log entries (dictionaries).

    Args:
        logs: A list of dictionaries, where each dictionary represents a log entry and contains a "timestamp" (string) and other data.
        target_time: The timestamp to search for (string in "YYYY-MM-DD HH:MM:SS" format).

    Returns:
        The log entry (dictionary) with the matching timestamp if found, otherwise a "Log entry not found" message.

    Example:
        logs = [{"timestamp": "2025-03-28 10:00:00", "message": "System started"},
                {"timestamp": "2025-03-28 10:05:00", "message": "User logged in"}]
        search_log_timestamp(logs, "2025-03-28 10:05:00") == {"timestamp": "2025-03-28 10:05:00", "message": "User logged in"}
    """
    timestamps = [datetime.strptime(log["timestamp"], "%Y-%m-%d %H:%M:%S") for log in logs] # Convert log timestamps to datetime objects for comparison
    target_dt = datetime.strptime(target_time, "%Y-%m-%d %H:%M:%S")  # Convert the target timestamp to a datetime object
    index = bisect_left(timestamps, target_dt)  # Use bisect_left to find the insertion point
    if index < len(logs) and timestamps[index] == target_dt:
        return logs[index]  # Return the log entry if the timestamp matches
    return {"message": "Log entry not found"}  # Target timestamp not found

# 5. Finding Nearest Location in GPS Coordinates List (Binary Search on Latitude)
def search_nearest_location(locations: List[Dict[str, float]], target_lat: float) -> Dict[str, float]:
    """
    Finds the nearest location to a given latitude using binary search on a list of locations.

    Args:
        locations: A list of dictionaries, where each dictionary represents a location and contains "latitude" and "longitude" (floats).
        target_lat: The target latitude (float).

    Returns:
        The location (dictionary) nearest to the target latitude.

    Example:
        locations = [{"latitude": -1.283, "longitude": 36.8219},
                     {"latitude": -1.292, "longitude": 36.8228}]
        search_nearest_location(locations, -1.290) == {'latitude': -1.292, 'longitude': 36.8228}
    """
    locations.sort(key=lambda x: x["latitude"])  # Sort the locations list based on latitude using a lambda function
    latitudes = [loc["latitude"] for loc in locations]  # Extract the latitudes into a separate list
    index = bisect_left(latitudes, target_lat)  # Find the insertion point for the target latitude
    if index == len(locations):
        return locations[-1]  # If the target is greater than all latitudes, return the last location
    elif index == 0 or abs(latitudes[index] - target_lat) < abs(latitudes[index - 1] - target_lat):
        return locations[index] # If the target is closest to the first location or the closest to the element at the insertion point
    return locations[index - 1] # Otherwise return the location before the insertion point

# 6. AI Model Predictions Search (Binary Search on Prediction Scores)
def search_ai_prediction(predictions: List[Dict[str, float]], threshold: float) -> Dict[str, float]:
    """
    Searches for the AI model prediction with the score closest to a given threshold using binary search.

    Args:
        predictions: A list of dictionaries, where each dictionary represents an AI prediction and contains "score" (float) and other data.
        threshold: The target score threshold (float).

    Returns:
        The AI prediction (dictionary) with the score closest to the threshold.

        Example:
        predictions = [{"score": 0.75, "label": "Positive"}, {"score": 0.85, "label": "Highly Positive"}]
        search_ai_prediction(predictions, 0.80) == {'score': 0.75, 'label': 'Positive'}
    """
    predictions.sort(key=lambda x: x["score"])  # Sort the predictions by their scores
    scores = [pred["score"] for pred in predictions]  # Extract the scores into a separate list
    index = bisect_right(scores, threshold) - 1 # Find the insertion point for the threshold using bisect_right and adjust the index
    if index >= 0:
        return predictions[index]  # Return the prediction with the score closest to the threshold
    return {"message": "No suitable prediction found"}  # If no prediction is found

# Sample Data for Testing
db_records = {1001: "Alice", 1002: "Bob", 1003: "Charlie"}
product_prices = [10, 20, 30, 40, 50]
numpy_array = np.array([1, 3, 5, 7, 9, 11, 13, 15])
logs = [{"timestamp": "2025-03-28 10:00:00", "message": "System started"},
        {"timestamp": "2025-03-28 10:05:00", "message": "User logged in"}]
locations = [{"latitude": -1.283, "longitude": 36.8219},
             {"latitude": -1.292, "longitude": 36.8228}]
predictions = [{"score": 0.75, "label": "Positive"}, {"score": 0.85, "label": "Highly Positive"}]

# Run Tests
print("Database Search:", binary_search_database(db_records, 1002))
print("Product Price Search:", search_product_price_range(product_prices, 30))
print("NumPy Binary Search:", binary_search_numpy(numpy_array, 7))
print("Log Search:", search_log_timestamp(logs, "2025-03-28 10:05:00"))
print("Nearest Location:", search_nearest_location(locations, -1.290))
print("AI Prediction Search:", search_ai_prediction(predictions, 0.80))
