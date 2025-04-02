"""
The Gas Station Problem:

You are given a circular array of gas stations.  Each gas station has a certain amount of gas,
and there is a cost to travel to the next gas station.  You start with an empty tank.
Find a starting gas station such that you can complete a full circle.

More formally:

-   `gas`: A list of integers representing the amount of gas at each gas station.
-   `cost`: A list of integers representing the cost to travel from gas station i to i+1.

You need to find the starting index (gas station) from which you can complete a circular route,
visiting all the gas stations exactly once.  If no such starting point exists, return -1.

Assumptions:

-   There is only one unique solution if one exists.
-   All gas and cost values are non-negative.
-   The input lists `gas` and `cost` have the same length.

Example:
gas  = [1, 2, 3, 4, 5]
cost = [3, 4, 5, 1, 2]
Starting at index 3, you can complete the circle:
- Start at 3 (gas = 4).
- Travel to 4 (cost = 1, remaining gas = 4 - 1 = 3).
- Travel to 0 (cost = 2, remaining gas = 3 + 5 - 2 = 6).
- Travel to 1 (cost = 3, remaining gas = 6 + 1 - 3 = 4).
- Travel to 2 (cost = 2, remaining gas = 4 + 2 - 4 = 2).
- Travel to 3 (cost = 5, remaining gas = 2 + 3 - 5 = 0).
So, index 3 is a valid starting point.

"""
from typing import List

def can_complete_circuit_brute_force(gas: List[int], cost: List[int]) -> int:
    """
    Approach 1: Brute Force

    -   Try every gas station as a starting point.
    -   Simulate the journey, keeping track of the remaining gas.
    -   If the journey completes, return the starting index.
    -   If no journey completes, return -1.

    Time Complexity: O(n^2), where n is the number of gas stations.
    Space Complexity: O(1)
    """
    n = len(gas)
    for start_index in range(n):
        remaining_gas = 0
        current_index = start_index
        stations_visited = 0

        while stations_visited < n:
            remaining_gas += gas[current_index] - cost[current_index]
            if remaining_gas < 0:
                break  # Cannot complete from this starting point
            current_index = (current_index + 1) % n  # Move to the next station (circular)
            stations_visited += 1

        if stations_visited == n and remaining_gas >= 0:
            return start_index  # Journey completed successfully
    return -1  # No valid starting point found
def can_complete_circuit_optimized(gas: List[int], cost: List[int]) -> int:
    """
    Approach 2: Optimized Single Pass

    -   Calculate the total gas and total cost. If total gas is less than total cost,
        no solution exists.
    -   Iterate through the gas stations, keeping track of the remaining gas.
    -   If the remaining gas becomes negative, reset the starting point to the next station
        and reset the remaining gas.
    -   The final starting point is the solution.

    Time Complexity: O(n), where n is the number of gas stations.
    Space Complexity: O(1)
    """
    n = len(gas)
    total_gas = sum(gas)
    total_cost = sum(cost)

    if total_gas < total_cost:
        return -1  # Cannot complete the circuit

    start_index = 0
    remaining_gas = 0
    for i in range(n):
        remaining_gas += gas[i] - cost[i]
        if remaining_gas < 0:
            start_index = i + 1  # Reset start index
            remaining_gas = 0  # Reset remaining gas

    return start_index

def can_complete_circuit_kadane(gas: List[int], cost: List[int]) -> int:
    """
    Approach 3: Kadane's Algorithm Variation

    -   Similar to the optimized approach, but focuses on finding the minimum prefix sum.
    -   If the total gas is less than the total cost, return -1.
    -   Iterate through the stations, tracking the current gas and the minimum gas.
    -   The starting station is the one after the station where the minimum gas occurs.

    Time Complexity: O(n), where n is the number of gas stations.
    Space Complexity: O(1)
    """
    n = len(gas)
    total_gas = sum(gas)
    total_cost = sum(cost)

    if total_gas < total_cost:
        return -1

    start_index = 0
    current_gas = 0
    min_gas = float('inf')
    min_index = -1

    for i in range(n):
        current_gas += gas[i] - cost[i]
        if current_gas < min_gas:
            min_gas = current_gas
            min_index = i

    if min_index == -1:
        return 0
    else:
        return (min_index + 1) % n
def can_complete_circuit_two_passes(gas: List[int], cost: List[int]) -> int:
    """
    Approach 4: Two-Pass Approach

    -   First pass: Calculate the net gas at each station (gas[i] - cost[i]).
    -   Second pass: Iterate through the stations, keeping track of the cumulative gas.
    -   If the cumulative gas becomes negative, add it to a deficit and reset cumulative gas.
    -   The starting station is the index where the cumulative gas was last reset.

    Time Complexity: O(n), where n is the number of gas stations.
    Space Complexity: O(1)
    """
    n = len(gas)
    net_gas = [gas[i] - cost[i] for i in range(n)]

    total_net_gas = sum(net_gas)
    if total_net_gas < 0:
        return -1

    start_index = 0
    cumulative_gas = 0
    for i in range(n):
        cumulative_gas += net_gas[i]
        if cumulative_gas < 0:
            start_index = i + 1
            cumulative_gas = 0

    return start_index
import collections
def can_complete_circuit_deque(gas: List[int], cost: List[int]) -> int:
    """
    Approach 5: Using Deque (Circular Simulation)

    -   Simulate the circular route using a deque.
    -   For each starting position, rotate the deque and track the remaining gas.
    -   If a starting position allows a complete circle, return its index.

    Time Complexity: O(n^2) in the worst case, but can be faster in some cases due to early stopping.
    Space Complexity: O(n)
    """
    n = len(gas)
    if sum(gas) < sum(cost):
        return -1

    for start_index in range(n):
        q = collections.deque(range(n))
        q.rotate(-start_index)  # Rotate to start at start_index
        remaining_gas = 0
        possible = True

        for _ in range(n):
            current_station = q.popleft()
            remaining_gas += gas[current_station] - cost[current_station]
            if remaining_gas < 0:
                possible = False
                break
        if possible:
            return start_index
    return -1
def main():
    """
    Main function to test the gas station problem solutions.
    """
    gas = [1, 2, 3, 4, 5]
    cost = [3, 4, 5, 1, 2]

    print("Gas Stations: ", gas)
    print("Costs:         ", cost)
    print("-" * 40)

    # Brute Force Approach
    result1 = can_complete_circuit_brute_force(gas, cost)
    print("Brute Force Approach:")
    print("Starting station:", result1)
    print("-" * 40)

    # Optimized Single Pass Approach
    result2 = can_complete_circuit_optimized(gas, cost)
    print("Optimized Single Pass Approach:")
    print("Starting station:", result2)
    print("-" * 40)

    # Kadane's Algorithm Variation
    result3 = can_complete_circuit_kadane(gas, cost)
    print("Kadane's Algorithm Variation:")
    print("Starting station:", result3)
    print("-" * 40)

    # Two-Pass Approach
    result4 = can_complete_circuit_two_passes(gas, cost)
    print("Two-Pass Approach:")
    print("Starting station:", result4)
    print("-" * 40)

    # Deque Approach
    result5 = can_complete_circuit_deque(gas, cost)
    print("Deque Approach:")
    print("Starting station:", result5)
    print("-" * 40)
if __name__ == "__main__":
    main()
