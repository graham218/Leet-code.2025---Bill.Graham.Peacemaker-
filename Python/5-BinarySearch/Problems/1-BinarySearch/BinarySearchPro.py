# Advanced Binary Search Implementations with Real-World Applications
# These approaches demonstrate how binary search can be applied in practical scenarios.

from typing import List, Dict # Import List and Dict for type hinting
import bisect # Import bisect for binary search
from datetime import datetime # Import datetime for handling time data

# 1. Searching for a Product Price in an E-commerce System
def search_product_price(products: List[Dict[str, float]], target_price: float) -> Dict[str, float]:
    """
    Searches for a product price closest to a target price in a sorted list of products.

    Args:
        products: A list of dictionaries, where each dictionary contains product information, including "price" (float).
        target_price: The target price to search for (float).

    Returns:
        A dictionary containing the product and price closest to the target price.
        If no product is found, returns "Not Found".
    """
    prices = sorted([product["price"] for product in products]) # Extract prices and sort them for binary search
    index = bisect.bisect_left(prices, target_price) # Find the insertion point for the target price
    if index < len(prices):
        return {"product_price": prices[index]} # Return price at index
    return {"product_price": "Not Found"} # Return "Not Found" if the target price is not found

# 2. Finding the Earliest Available Appointment Slot
def search_appointment_slot(slots: List[str], target_time: str) -> str:
    """
    Finds the earliest available appointment slot that is equal to or after a given target time.

    Args:
        slots: A sorted list of appointment time slots represented as strings in "HH:MM" format.
        target_time: The target time to search for (string in "HH:MM" format).

    Returns:
        The earliest available appointment slot (string) that is >= target_time.
        Returns "No Available Slots" if no such slot exists.
    """
    slot_times = [datetime.strptime(slot, "%H:%M") for slot in slots] # Convert time strings to datetime objects for comparison
    target_dt = datetime.strptime(target_time, "%H:%M") # Convert target time string to a datetime object
    index = bisect.bisect_left(slot_times, target_dt) # Find the insertion point
    if index < len(slots):
        return slots[index] # Return the slot at index
    return "No Available Slots" # Return "No Available Slots" if no suitable slot is found

# 3. Searching for the Best Stock Price before a Certain Time
def search_stock_price(stock_data: List[Dict[str, float]], target_time: str) -> Dict[str, float]:
    """
    Finds the stock price at the latest time that is less than a given target time.

    Args:
        stock_data: A sorted list of dictionaries, where each dictionary contains stock "time" (string in "YYYY-MM-DD HH:MM:SS" format) and "price" (float).
        target_time: The target time (string in "YYYY-MM-DD HH:MM:SS" format).

    Returns:
        A dictionary containing the stock data (time and price) for the latest time before the target time.
        Returns "No stock data available" if there is no data before the target time.
    """
    timestamps = [datetime.strptime(stock["time"], "%Y-%m-%d %H:%M:%S") for stock in stock_data] # Convert time strings to datetime objects
    target_dt = datetime.strptime(target_time, "%Y-%m-%d %H:%M:%S") # Convert target time to a datetime object
    index = bisect.bisect_left(timestamps, target_dt) # Find the insertion point
    if index > 0:
        return stock_data[index - 1] # Return the stock data at the index before the insertion point
    return {"message": "No stock data available"} # Return message if no data before target time

# 4. Searching for a Nearest Matching GPS Location
def search_nearest_location(locations: List[Dict[str, float]], target_lat: float) -> Dict[str, float]:
    """
    Finds the nearest GPS location to a given target latitude.

    Args:
        locations: A sorted list of dictionaries, where each dictionary contains "lat" (float) and "lon" (float)
                   representing a location.  The list is assumed to be sorted by latitude.
        target_lat: The target latitude (float).

    Returns:
        The dictionary representing the nearest GPS location.  Returns the first element if target_lat
        is smaller than all latitudes in the list.
    """
    latitudes = sorted([loc["lat"] for loc in locations]) # Extract latitudes.  Already sorted, but sorted() does not modify in place.
    index = bisect.bisect_left(latitudes, target_lat) # Find the insertion point for the target latitude
    if index > 0:
        return locations[index - 1] # Return location just before the insertion point
    return locations[0] # Return the first location if the target latitude is the smallest

# 5. Locating a Word in a Dictionary
def search_dictionary(dictionary: List[str], target_word: str) -> str:
    """
    Finds a word in a sorted list of dictionary words.

    Args:
        dictionary: A sorted list of strings representing words in a dictionary.
        target_word: The word to search for (string).

    Returns:
        The target word if found, otherwise "Word Not Found".
    """
    index = bisect.bisect_left(dictionary, target_word) # Find the insertion point
    if index < len(dictionary):
        return dictionary[index] # Return the word at the insertion point
    return "Word Not Found" # Return "Word Not Found" if target word is not in the dictionary

# 6. Searching for an Error in System Logs
def search_error_log(logs: List[Dict[str, str]], severity: str) -> Dict[str, str]:
    """
    Searches for the first error log entry with a specific severity level.

    Args:
        logs: A sorted list of dictionaries, where each dictionary represents a log entry and contains
              "timestamp" (string) and "severity" (string).  The list is sorted by severity.
        severity: The severity level to search for (string, e.g., "ERROR", "WARNING").

    Returns:
        The first log entry with the specified severity, or a message "No errors found" if
        no matching log entry exists.
    """
    severities = [log["severity"] for log in logs] # Extract the severities from the logs
    index = bisect.bisect_left(severities, severity) # Find the insertion point
    if index < len(logs):
        return logs[index] # Return the log at index
    return {"message": "No errors found"} # Return "No errors found" if no matching severity found

# Sample Data
ecommerce_products = [{"name": "Laptop", "price": 1000.0}, {"name": "Phone", "price": 500.0}]
available_slots = ["09:00", "10:30", "14:00", "16:00"]
stock_prices = [{"time": "2025-03-28 09:00:00", "price": 150.5}, {"time": "2025-03-28 12:00:00", "price": 153.2}]
gps_locations = [{"lat": 40.7128, "lon": -74.0060}, {"lat": 34.0522, "lon": -118.2437}]
dictionary_words = ["apple", "banana", "cherry", "date", "fig", "grape"]
error_logs = [{"timestamp": "2025-03-28 08:00:00", "severity": "INFO"}, {"timestamp": "2025-03-28 09:15:00", "severity": "ERROR"}]

# Running Tests
print("Product Price Search:", search_product_price(ecommerce_products, 750.0))
print("Appointment Slot Search:", search_appointment_slot(available_slots, "10:00"))
print("Stock Price Search:", search_stock_price(stock_prices, "2025-03-28 11:00:00"))
print("Nearest Location Search:", search_nearest_location(gps_locations, 37.7749))
print("Dictionary Word Search:", search_dictionary(dictionary_words, "cherry"))
print("Error Log Search:", search_error_log(error_logs, "ERROR"))
