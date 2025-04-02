"""
The "Gas Station" problem:

Imagine you have a circular route with n gas stations. At each gas station i, you can get gas[i] amount of gas.
You have a car with an unlimited gas tank, and it costs cost[i] amount of gas to travel from station i to its next station (i+1).
You begin the journey with an empty tank at one of the gas stations.

Given two integer arrays gas and cost, return the starting gas station's index if you can travel around the circuit once in the clockwise direction; otherwise, return -1.
If there exists a solution, it is guaranteed to be unique.

Constraints:
    n == gas.length == cost.length
    1 <= n <= 10^4
    0 <= gas[i], cost[i] <= 10^4

Example 1:
    Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
    Output: 3
    Explanation:
    Start at the gas station with index 3 (starting fuel = 0).
    - Travel to station 4. Your tank = 0 + 4 - 1 = 3
    - Travel to station 0. Your tank = 3 + 5 - 2 = 6
    - Travel to station 1. Your tank = 6 + 1 - 3 = 4
    - Travel to station 2. Your tank = 4 + 2 - 4 = 2
    - Travel to station 3. Your tank = 2 + 3 - 5 = 0
    You can complete the circuit rotationally, so return 3.

Example 2:
    Input: gas = [2,3,4], cost = [3,4,3]
    Output: -1
    Explanation:
    You can't start at any gas station to complete the circuit.

"""
from typing import List

def can_complete_circuit_brute_force(gas: List[int], cost: List[int]) -> int:
    """
    Approach 1: Brute Force
    - Try every station as a starting point.
    - Simulate the journey and check if it's possible to complete the circuit.
    - This is the most straightforward but least efficient approach.

    Time Complexity: O(n^2), where n is the number of gas stations.
    Space Complexity: O(1)
    """
    n = len(gas)
    for start_station in range(n):
        current_gas = 0
        possible = True
        for i in range(n):
            # Calculate the current station index in the circular route.
            current_station = (start_station + i) % n
            current_gas += gas[current_station] - cost[current_station]
            if current_gas < 0:
                possible = False
                break
        if possible:
            print(f"Brute Force: Starting station = {start_station}")
            return start_station
    print("Brute Force: No solution")
    return -1


def can_complete_circuit_optimized(gas: List[int], cost: List[int]) -> int:
    """
    Approach 2: Optimized Single Pass
    - If the total gas is less than the total cost, there is no solution.
    - Start from station 0, and keep track of the current gas and the starting station.
    - If the current gas becomes negative, change the starting station to the next station.
    - This approach is based on the observation that if we cannot reach station j from station i,
      then we cannot reach station j from any station between i and j.

    Time Complexity: O(n), where n is the number of gas stations.
    Space Complexity: O(1)
    """
    n = len(gas)
    total_gas = sum(gas)
    total_cost = sum(cost)

    if total_gas < total_cost:
        print("Optimized Single Pass: No solution")
        return -1

    start_station = 0
    current_gas = 0
    for i in range(n):
        current_gas += gas[i] - cost[i]
        if current_gas < 0:
            start_station = i + 1
            current_gas = 0

    print(f"Optimized Single Pass: Starting station = {start_station}")
    return start_station

def can_complete_circuit_kadane(gas: List[int], cost: List[int]) -> int:
    """
    Approach 3: Kadane's Algorithm Variation
    - Similar to the optimized single pass, but uses a variation of Kadane's algorithm.
    - Kadane's algorithm is typically used to find the maximum subarray sum.
    - Here, we adapt it to find the starting point with the maximum "gas surplus".

    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    n = len(gas)
    total_gas = 0
    current_gas = 0
    start_station = 0

    for i in range(n):
        total_gas += gas[i] - cost[i]
        current_gas += gas[i] - cost[i]
        if current_gas < 0:
            current_gas = 0
            start_station = i + 1

    if total_gas < 0:
        print("Kadane Variation: No solution")
        return -1
    print(f"Kadane Variation: Starting station = {start_station}")
    return start_station
def can_complete_circuit_deque(gas: List[int], cost: List[int]) -> int:
    """
    Approach 4: Using Deque (Double-Ended Queue)
    - Extend the gas and cost arrays to simulate the circular route.
    - Use a deque to maintain a window of possible starting points.
    - If a starting point is not feasible, remove it from the deque.

    Time Complexity: O(n)
    Space Complexity: O(n)
    """
    from collections import deque

    n = len(gas)
    extended_gas = gas + gas
    extended_cost = cost + cost
    q = deque(range(n))  # Initialize deque with possible starting stations

    for i in range(2 * n):
        while q and sum(extended_gas[q[0]:i+1]) < sum(extended_cost[q[0]:i+1]):
            q.popleft()  # Remove infeasible starting stations
        if not q:
            print("Deque Approach: No solution")
            return -1
        if i >= n and q[0] < n:
            print(f"Deque Approach: Starting station = {q[0]}")
            return q[0]
    print("Deque Approach: No solution")
    return -1

def can_complete_circuit_dynamic_programming(gas: List[int], cost: List[int]) -> int:
    """
    Approach 5: Dynamic Programming (Less Efficient, but Demonstrates DP)
    - Create a DP table where dp[i] stores the remaining gas at station i, starting from station 0.
    - Iterate through all possible starting stations and use the DP table to check for completion.
    - While DP can be used, it's not the most efficient approach for this problem.

    Time Complexity: O(n^2)
    Space Complexity: O(n)
    """
    n = len(gas)
    for start_station in range(n):
        dp = [0] * n
        dp[0] = gas[start_station] - cost[start_station]
        possible = True
        for i in range(1, n):
            current_station = (start_station + i) % n
            prev_station = (start_station + i - 1) % n
            dp[i] = dp[i - 1] + gas[current_station] - cost[current_station]
            if dp[i] < 0:
                possible = False
                break
        if possible and dp[-1] >= 0: # Check if the tank has >=0 gas at the end
            print(f"Dynamic Programming: Starting station = {start_station}")
            return start_station
    print("Dynamic Programming: No solution")
    return -1

def can_complete_circuit_greedy(gas: List[int], cost: List[int]) -> int:
    """
    Approach 6: Greedy Approach (Most Efficient)
    - This is the most efficient and intuitive solution.
    - The core idea is that if the total gas is greater than or equal to the total cost,
      there must be a solution.
    - We maintain a running `tank` and a `start` index.  If the `tank` goes negative,
      we reset the `start` to the next station.

    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    n = len(gas)
    tank = 0
    total_gas = 0
    total_cost = 0
    start = 0

    for i in range(n):
        tank += gas[i] - cost[i]
        total_gas += gas[i]
        total_cost += cost[i]
        if tank < 0:
            start = i + 1
            tank = 0

    if total_gas < total_cost:
        print("Greedy Approach: No solution")
        return -1  # Not possible to complete the circuit
    else:
        print(f"Greedy Approach: Starting station = {start}")
        return start

if __name__ == "__main__":
    gas = [1, 2, 3, 4, 5]
    cost = [3, 4, 5, 1, 2]
    #gas = [2, 3, 4]
    #cost = [3, 4, 3]

    print("Gas and Cost:", gas, cost)
    print("-" * 30)
    print("Brute Force Result:", can_complete_circuit_brute_force(gas, cost))
    print("-" * 30)
    print("Optimized Single Pass Result:", can_complete_circuit_optimized(gas, cost))
    print("-" * 30)
    print("Kadane Variation Result:", can_complete_circuit_kadane(gas, cost))
    print("-" * 30)
    print("Deque Approach Result:", can_complete_circuit_deque(gas, cost))
    print("-" * 30)
    print("Dynamic Programming Result:", can_complete_circuit_dynamic_programming(gas, cost))
    print("-" * 30)
    print("Greedy Approach Result:", can_complete_circuit_greedy(gas, cost))
    print("-" * 30)
