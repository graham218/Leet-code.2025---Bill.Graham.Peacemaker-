# Advanced Real-World Implementations of Exponential Search
# These approaches apply exponential search in real-world use cases, such as search engines, finance, and AI.

from typing import List, Dict # Import List and Dict for type hinting
import bisect # Import bisect for binary search
from datetime import datetime # Import datetime for handling time data
import numpy as np # Import numpy for efficient calculations

# 1. Search for Earliest and Latest Stock Prices Before a Given Time
def search_stock_price(stock_data: List[Dict[str, float]], target_time: str) -> Dict[str, float]:
    """
    Searches for the stock price at the earliest time before a given target time using exponential search.

    Args:
        stock_data: A sorted list of dictionaries, where each dictionary contains stock "time" (string in "YYYY-MM-DD HH:MM:SS" format) and "price" (float).
        target_time: The target time to search before (string in "YYYY-MM-DD HH:MM:SS" format).

    Returns:
        A dictionary containing the stock data for the earliest time before the target time, or None if no such time exists.
    """
    timestamps = [datetime.strptime(stock["time"], "%Y-%m-%d %H:%M:%S") for stock in stock_data] # Convert time strings to datetime objects
    target_dt = datetime.strptime(target_time, "%Y-%m-%d %H:%M:%S") # Convert target time to a datetime object
    index = 1
    while index < len(timestamps) and timestamps[index] <= target_dt:
        index *= 2 # Exponentially increase index to find the relevant range
    pos = bisect.bisect_left(timestamps[:min(index, len(timestamps))], target_dt) # Perform binary search using bisect_left
    return {"earliest": stock_data[pos-1] if pos > 0 else None} # Return the stock data at the found position

# 2. Finding Closest GPS Location in a Route System
def search_nearest_location(locations: List[Dict[str, float]], target_lat: float, target_lon: float) -> Dict[str, float]:
    """
    Finds the nearest GPS location to a given target latitude and longitude using exponential search.

    Args:
        locations: A sorted list of dictionaries, where each dictionary contains "lat" (float) and "lon" (float) representing a location.
                 The list is sorted by distance from a reference point.
        target_lat: The target latitude (float).
        target_lon: The target longitude (float).

    Returns:
        The dictionary representing the nearest location.
    """
    distances = [(loc, np.sqrt((loc["lat"] - target_lat) ** 2 + (loc["lon"] - target_lon) ** 2)) for loc in locations] # Calculate distances
    distances.sort(key=lambda x: x[1]) # Sort by distance
    index = 1
    while index < len(distances) and distances[index][1] <= distances[0][1]:
        index *= 2 # Exponentially increase index
    pos = min(index, len(distances))
    return distances[pos - 1][0] # Return the location with the minimum distance

# 3. AI Model Prediction Search for Best Confidence Score
def search_best_confidence(predictions: List[Dict[str, float]], threshold: float) -> Dict[str, float]:
    """
    Finds the AI model prediction with the highest confidence score that is less than or equal to a given threshold.

    Args:
        predictions: A list of dictionaries, where each dictionary contains a "confidence" score (float).
        threshold: The confidence threshold (float).

    Returns:
        The dictionary representing the AI prediction with the highest confidence score below the threshold, or None if no such prediction exists.
    """
    scores = sorted([pred["confidence"] for pred in predictions]) # Extract and sort confidence scores
    index = 1
    while index < len(scores) and scores[index] <= threshold:
        index *= 2 # Exponentially increase index
    pos = bisect.bisect_left(scores[:min(index, len(scores))], threshold) # Binary search for the insertion point
    return {"best_prediction": predictions[pos - 1] if pos > 0 else None} # Return the prediction

# 4. Searching in Large Log Files for Errors
def search_error_logs(logs: List[Dict[str, str]], severity: str) -> Dict[str, str]:
    """
    Searches for the first log entry with a specific severity level (e.g., "ERROR") in a sorted list of log entries.

    Args:
        logs: A sorted list of dictionaries, where each dictionary represents a log entry and contains "timestamp" (string) and "severity" (string).
        severity: The severity level to search for (string, e.g., "ERROR").

    Returns:
        The first log entry with the specified severity, or "Not Found" if no such entry exists.
    """
    severities = [log["severity"] for log in logs] # Extract severities
    index = 1
    while index < len(severities) and severities[index] <= severity:
        index *= 2 # Exponentially increase index
    pos = bisect.bisect_left(severities[:min(index, len(severities))], severity) # Binary search
    return {"first_error": logs[pos] if pos < len(logs) else "Not Found"} # Return the log entry

# 5. Locating Data in a Distributed Database
def search_distributed_db(records: List[Dict[str, str]], target_key: str) -> Dict[str, str]:
    """
    Searches for a record with a specific key in a simulated distributed database (list of dictionaries).

    Args:
        records: A sorted list of dictionaries, where each dictionary represents a database record and contains "key" (string) and "value" (string).
        target_key: The key to search for (string).

    Returns:
        The database record with the matching key, or a "Record not found" message if no such record exists.
    """
    keys = sorted([record["key"] for record in records]) # Extract and sort keys
    index = 1
    while index < len(keys) and keys[index] <= target_key:
        index *= 2 # Exponentially increase index
    pos = bisect.bisect_left(keys[:min(index, len(keys))], target_key) # Binary search
    return records[pos] if pos < len(records) else {"message": "Record not found"} # Return the record

# 6. Searching in Streaming Video Metadata for a Specific Timestamp
def search_video_frame(frames: List[Dict[str, str]], target_timestamp: str) -> Dict[str, str]:
    """
    Searches for a specific video frame in a sorted list of video frame metadata using exponential search.

    Args:
        frames: A sorted list of dictionaries, where each dictionary represents a video frame and contains "timestamp" (string in "HH:MM:SS" format) and other frame data.
        target_timestamp: The timestamp to search for (string in "HH:MM:SS" format).

    Returns:
        The video frame data for the frame with the matching timestamp, or a "Frame not found" message if no such frame exists.
    """
    timestamps = [datetime.strptime(frame["timestamp"], "%H:%M:%S") for frame in frames] # Convert timestamp strings to datetime objects
    target_dt = datetime.strptime(target_timestamp, "%H:%M:%S") # Convert target timestamp to datetime
    index = 1
    while index < len(timestamps) and timestamps[index] <= target_dt:
        index *= 2 # Exponentially increase index
    pos = bisect.bisect_left(timestamps[:min(index, len(timestamps))], target_dt) # Binary search
    return frames[pos] if pos < len(frames) else {"message": "Frame not found"} # Return the frame data

# Sample Data for Testing
stock_data = [{"time": "2025-03-28 09:00:00", "price": 150.5},
              {"time": "2025-03-28 12:00:00", "price": 153.2}]
locations = [{"lat": 40.7128, "lon": -74.0060}, {"lat": 34.0522, "lon": -118.2437}]
predictions = [{"confidence": 0.65}, {"confidence": 0.75}, {"confidence": 0.85}]
log_entries = [{"timestamp": "2025-03-28 08:00:00", "severity": "INFO"},
               {"timestamp": "2025-03-28 09:15:00", "severity": "ERROR"}]
db_records = [{"key": "A123", "value": "Customer Data"},
              {"key": "B456", "value": "Order Data"}]
video_frames = [{"timestamp": "00:01:00", "frame": "Scene 1"},
                {"timestamp": "00:02:30", "frame": "Scene 2"}]

# Running Tests
print("Stock Price:", search_stock_price(stock_data, "2025-03-28 10:00:00"))
print("Nearest Location:", search_nearest_location(locations, 37.7749, -122.4194))
print("Best AI Prediction:", search_best_confidence(predictions, 0.70))
print("Error Log Search:", search_error_logs(log_entries, "ERROR"))
print("Database Record Search:", search_distributed_db(db_records, "A123"))
print("Video Frame Search:", search_video_frame(video_frames, "00:02:00"))
