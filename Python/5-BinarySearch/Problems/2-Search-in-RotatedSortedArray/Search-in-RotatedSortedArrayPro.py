# Advanced Real-World Implementations for Searching in a Rotated Sorted Array
# These solutions demonstrate how binary search can be used in different industries.

from typing import List, Dict
import bisect  # Import the bisect module for binary search


def search_rotated_product_prices(products: List[Dict[str, float]], target_price: float) -> Dict[str, float]:
    """
    Search for a product price in a rotated price list (E-commerce).

    This function simulates searching for a product's price in an e-commerce database.
    It assumes the prices are sorted, but the list might have been rotated (though the example data isn't rotated).
    It uses binary search (bisect.bisect_left) to efficiently find the target price.

    Args:
        products (List[Dict[str, float]]): A list of dictionaries, where each dictionary
            represents a product and contains its name and price.
        target_price (float): The price to search for.

    Returns:
        Dict[str, float]: A dictionary containing the found product price.  If the price
        is found, it returns the price. If not found, it returns "Not Found".
    """
    # Extract prices from the product list and sort them.  bisect requires a sorted list.
    prices = sorted([product["price"] for product in products])
    # Use bisect_left to find the insertion point for the target price.
    index = bisect.bisect_left(prices, target_price)
    # Check if the index is within the bounds of the prices list.
    # If it is, return the price at that index.  Otherwise, return "Not Found".
    return {"product_price": prices[index] if index < len(prices) else "Not Found"}



def search_rotated_flight_times(flight_times: List[str], target_time: str) -> str:
    """
    Find the next available flight in a rotated sorted schedule (Aviation).

    This function simulates searching for a flight time in an aviation schedule.
    It assumes the flight times are sorted, and uses binary search.

    Args:
        flight_times (List[str]): A list of flight times (strings) in 24-hour format.
        target_time (str): The time to search for.

    Returns:
        str: The next available flight time, or "No available flights" if none found.
    """
    # Use bisect_left to find the insertion point for the target time.
    index = bisect.bisect_left(flight_times, target_time)
    # Check if the index is within the bounds of the flight_times list.
    # If it is, return the flight time at that index. Otherwise, return "No available flights".
    return flight_times[index] if index < len(flight_times) else "No available flights"



def search_rotated_sensor_readings(readings: List[Dict[str, float]], target_value: float) -> Dict[str, float]:
    """
    Find a specific sensor reading from a rotated sorted dataset (IoT & Smart Devices).

    This function simulates searching for a sensor reading in data from an IoT device.
    It assumes the sensor readings are sorted, and uses binary search.

    Args:
        readings (List[Dict[str, float]]): A list of dictionaries, where each dictionary
            represents a sensor reading and contains a timestamp and value.
        target_value (float): The sensor value to search for.

    Returns:
        Dict[str, float]: The sensor reading (dictionary) that is closest to the target_value.
    """
    # Extract the sensor values and sort them.
    values = sorted([reading["value"] for reading in readings])
    # Use bisect_left to find the insertion point for the target value.
    index = bisect.bisect_left(values, target_value)
    # Return the reading *before* the insertion point.  If index is 0, return the first.
    return readings[index - 1] if index > 0 else readings[0]



def search_rotated_stock_prices(stock_data: List[Dict[str, float]], target_price: float) -> Dict[str, float]:
    """
    Find the closest stock price from a rotated sorted market data list (Finance).

    This function simulates searching for a stock price in financial market data.
    It assumes the stock prices are sorted, and uses binary search.

    Args:
        stock_data (List[Dict[str, float]]): A list of dictionaries, where each dictionary
            represents stock data and contains a time and price.
        target_price (float): The stock price to search for.

    Returns:
        Dict[str, float]: The stock data (dictionary) with the closest price to the target.
    """
    # Extract the stock prices and sort them.
    prices = sorted([stock["price"] for stock in stock_data])
    # Use bisect_left to find the insertion point for the target price.
    index = bisect.bisect_left(prices, target_price)
    # Return the stock data *before* the insertion point. If index is 0, return the first.
    return stock_data[index - 1] if index > 0 else stock_data[0]



def search_rotated_medical_records(records: List[Dict[str, str]], target_patient: str) -> Dict[str, str]:
    """
    Find a patient record in a rotated sorted dataset (Healthcare).

    This function simulates searching for a patient record in a healthcare database.
    It assumes the patient names are sorted, and uses binary search.

    Args:
        records (List[Dict[str, str]]): A list of dictionaries, where each dictionary
            represents a medical record.
        target_patient (str): The name of the patient to search for.

    Returns:
        Dict[str, str]: The patient's medical record (dictionary), or a message if not found.
    """
    # Extract the patient names and sort them.
    patients = sorted([record["name"] for record in records])
    # Use bisect_left to find the insertion point for the target patient name.
    index = bisect.bisect_left(patients, target_patient)
    # Return the record at the found index, or a "Patient not found" message.
    return records[index] if index < len(records) else {"message": "Patient not found"}



def search_rotated_log_entries(logs: List[Dict[str, str]], target_severity: str) -> Dict[str, str]:
    """
    Find the most recent log entry matching a severity level (Cybersecurity & IT).

    This function simulates searching for a log entry in a system log.
    It assumes the log entries are sorted by severity, and uses binary search.

    Args:
        logs (List[Dict[str, str]]): A list of dictionaries, where each dictionary
            represents a log entry.
        target_severity (str): The severity level to search for.

    Returns:
        Dict[str, str]: The log entry (dictionary) with the matching severity, or a message if not found.
    """
    # Extract the severities from the log entries and sort them.
    severities = sorted([log["severity"] for log in logs])
    # Use bisect_left to find the insertion point for the target severity.
    index = bisect.bisect_left(severities, target_severity)
    # Return the log entry at the found index, or a "No matching log found" message.
    return logs[index] if index < len(logs) else {"message": "No matching log found"}



# Sample Data (Added for clarity and to make the code runnable)
ecommerce_products = [{"name": "Laptop", "price": 1200.0}, {"name": "Tablet", "price": 600.0}]
flight_schedule = ["06:00", "09:30", "14:00", "20:15"]
sensor_data = [{"timestamp": "2025-03-28 10:00:00", "value": 35.5}, {"timestamp": "2025-03-28 11:00:00", "value": 37.2}]
stock_market = [{"time": "2025-03-28 09:00:00", "price": 250.5}, {"time": "2025-03-28 12:00:00", "price": 255.2}]
medical_data = [{"name": "John Doe", "age": 45}, {"name": "Jane Smith", "age": 52}]
log_entries = [{"timestamp": "2025-03-28 08:00:00", "severity": "INFO"}, {"timestamp": "2025-03-28 09:15:00", "severity": "ERROR"}]

# Running Tests (Added to show usage)
print("Product Price Search:", search_rotated_product_prices(ecommerce_products, 750.0))
print("Flight Schedule Search:", search_rotated_flight_times(flight_schedule, "10:00"))
print("Sensor Readings Search:", search_rotated_sensor_readings(sensor_data, 36.0))
print("Stock Prices Search:", search_rotated_stock_prices(stock_market, 253.0))
print("Medical Records Search:", search_rotated_medical_records(medical_data, "Jane Smith"))
print("Log Entries Search:", search_rotated_log_entries(log_entries, "ERROR"))
