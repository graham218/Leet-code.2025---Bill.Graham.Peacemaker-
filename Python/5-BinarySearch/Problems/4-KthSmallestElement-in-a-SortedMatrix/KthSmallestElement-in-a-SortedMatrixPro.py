# Advanced Real-World Implementations for Finding Kth Smallest Element in a Sorted Matrix
# These solutions are tailored to real-world applications in finance, logistics, AI, healthcare, and cybersecurity.

from typing import List, Dict
import heapq
import bisect

def kth_smallest_stock_prices(stock_data: List[Dict[str, float]], k: int) -> Dict[str, float]:
    """
    Find the kth lowest stock price in a dataset (Finance).

    This function finds the k-th lowest stock price from a list of stock data.
    In a financial context, this can be used to identify undervalued stocks
    or to perform quantile analysis on a portfolio.  For example, finding the
    10th percentile of stock prices can help identify the lowest-performing
    stocks.

    Args:
        stock_data (List[Dict[str, float]]): A list of dictionaries, where each
            dictionary represents a stock and contains data like "price".
        k (int): The rank of the desired smallest price (e.g., 1 for the lowest).

    Returns:
        Dict[str, float]: The dictionary representing the stock with the k-th lowest price.
    """
    # Sort the stock data by price using a lambda function as the key.
    sorted_prices = sorted(stock_data, key=lambda x: x['price'])
    # Return the element at index k-1, which corresponds to the k-th smallest price.
    return sorted_prices[k - 1]



def kth_smallest_server_response(response_times: List[Dict[str, float]], k: int) -> Dict[str, float]:
    """
    Find the kth smallest server response time (Cloud Computing).

    This function finds the k-th smallest server response time.  In cloud computing,
    this can be used to analyze server performance and identify servers with
    unusually low response times, which might indicate problems or bottlenecks.
    For example, finding the 95th percentile response time can help in setting
    Service Level Agreements (SLAs).

    Args:
        response_times (List[Dict[str, float]]): A list of dictionaries, where each
            dictionary represents a server response and contains data like "response_time".
        k (int): The rank of the desired smallest response time.

    Returns:
        Dict[str, float]: The dictionary representing the server response with the k-th smallest time.
    """
    # Sort the response times using a lambda function.
    sorted_responses = sorted(response_times, key=lambda x: x['response_time'])
    # Return the k-th smallest response time.
    return sorted_responses[k - 1]



def kth_smallest_traffic_delay(traffic_data: List[Dict[str, float]], k: int) -> Dict[str, float]:
    """
    Find the kth smallest traffic delay time (Logistics).

    This function finds the k-th smallest traffic delay time.  In logistics, this
    can be used to analyze traffic patterns and identify routes or times with
    minimal delays.  For example, finding the median delay time can provide a
    typical delay value for route planning.

    Args:
        traffic_data (List[Dict[str, float]]): A list of dictionaries, where each
            dictionary represents traffic data and contains data like "delay".
        k (int): The rank of the desired smallest delay time.

    Returns:
        Dict[str, float]: The dictionary representing the traffic data with the k-th smallest delay.
    """
    # Sort the traffic delays.
    sorted_delays = sorted(traffic_data, key=lambda x: x['delay'])
    # Return the k-th smallest delay.
    return sorted_delays[k - 1]



def kth_smallest_disease_risk(patient_risk_scores: List[Dict[str, float]], k: int) -> Dict[str, float]:
    """
    Find the kth patient with the lowest risk score (Healthcare).

    This function finds the k-th patient with the lowest risk score.  In healthcare,
    this can be used to prioritize patients for treatment or further evaluation.
    For example, finding the patients in the lowest 10% risk group can help
    identify those who need immediate attention.

    Args:
        patient_risk_scores (List[Dict[str, float]]): A list of dictionaries, where each
            dictionary represents a patient and contains data like "risk_score".
        k (int): The rank of the desired smallest risk score.

    Returns:
        Dict[str, float]: The dictionary representing the patient with the k-th smallest risk score.
    """
    # Sort the patient risk scores.
    sorted_scores = sorted(patient_risk_scores, key=lambda x: x['risk_score'])
    # Return the k-th smallest risk score.
    return sorted_scores[k - 1]



def kth_smallest_intrusion_score(intrusion_logs: List[Dict[str, float]], k: int) -> Dict[str, float]:
    """
    Find the kth lowest intrusion detection score (Cybersecurity).

    This function finds the k-th lowest intrusion detection score.  In cybersecurity,
    this can be used to prioritize security alerts and identify the least severe
    intrusions.  For example, finding the 25th percentile of intrusion scores can
    help filter out the least critical alerts.

    Args:
        intrusion_logs (List[Dict[str, float]]): A list of dictionaries, where each
            dictionary represents an intrusion log and contains data like "intrusion_score".
        k (int): The rank of the desired smallest intrusion score.

    Returns:
        Dict[str, float]: The dictionary representing the intrusion log with the k-th smallest score.
    """
    # Sort the intrusion scores.
    sorted_intrusions = sorted(intrusion_logs, key=lambda x: x['intrusion_score'])
    # Return the k-th smallest intrusion score.
    return sorted_intrusions[k - 1]



def kth_smallest_sensor_reading(sensor_data: List[Dict[str, float]], k: int) -> Dict[str, float]:
    """
    Find the kth smallest sensor reading in IoT networks (AI & IoT).

    This function finds the k-th smallest sensor reading from IoT sensor data.
    This can be used to analyze sensor data and identify unusual or outlier
    readings. For example, finding the lowest 1% of sensor readings from a
    temperature sensor network can help detect malfunctioning sensors or
    unusually cold spots.

    Args:
        sensor_data (List[Dict[str, float]]): A list of dictionaries, where each
            dictionary represents sensor data and contains data like "reading".
        k (int): The rank of the desired smallest reading.

    Returns:
        Dict[str, float]: The dictionary representing the sensor data with the k-th smallest reading.
    """
    # Sort the sensor readings.
    sorted_readings = sorted(sensor_data, key=lambda x: x['reading'])
    # Return the k-th smallest reading.
    return sorted_readings[k - 1]


# Sample Data (Added for clarity and to make the code runnable)
stock_prices = [{'price': 150.3}, {'price': 120.5}, {'price': 180.0}, {'price': 160.2}]
server_responses = [{'response_time': 200.1}, {'response_time': 150.3}, {'response_time': 300.5}, {'response_time': 180.0}]
traffic_data = [{'delay': 5.0}, {'delay': 3.2}, {'delay': 6.7}, {'delay': 4.1}]
patient_risk_scores = [{'risk_score': 0.8}, {'risk_score': 0.6}, {'risk_score': 1.2}, {'risk_score': 0.9}]
intrusion_logs = [{'intrusion_score': 45.2}, {'intrusion_score': 30.1}, {'intrusion_score': 50.5}, {'intrusion_score': 40.0}]
sensor_readings = [{'reading': 22.5}, {'reading': 18.3}, {'reading': 25.0}, {'reading': 20.4}]

# Running Tests (Added to show usage)
k = 2
print("Stock Prices:", kth_smallest_stock_prices(stock_prices, k))
print("Server Response Times:", kth_smallest_server_response(server_responses, k))
print("Traffic Delays:", kth_smallest_traffic_delay(traffic_data, k))
print("Patient Risk Scores:", kth_smallest_disease_risk(patient_risk_scores, k))
print("Intrusion Scores:", kth_smallest_intrusion_score(intrusion_logs, k))
print("Sensor Readings:", kth_smallest_sensor_reading(sensor_readings, k))
