"""
Combination Sum Problem:

Given a set of candidate numbers (candidates) and a target number (target),
find all unique combinations in candidates where the numbers sum to target.
The same number may be chosen from candidates an unlimited number of times.

For example:
    candidates = [2, 3, 6, 7], target = 7
    Output: [[7], [2, 2, 3]]

    candidates = [2, 3, 5], target = 8
    Output: [[2, 2, 2, 2], [2, 3, 3], [3, 5]]

    candidates = [2], target = 1
    Output: []
"""

def combinationSum_recursive(candidates, target):
    """
    1.  Recursive Approach (Basic Backtracking)

    This is the most straightforward backtracking solution.  It explores all possible
    combinations by recursively adding candidates to the current combination
    and checking if the sum equals the target.

    Time Complexity: O(N^(T/M)), where N is the number of candidates, T is the target,
                    and M is the minimum value in candidates.  This is a loose upper bound.
    Space Complexity: O(T/M) -  The maximum depth of the recursion.
    """
    result = []

    def backtrack(combination, remaining, start):
        if remaining == 0:
            result.append(list(combination))  # Append a *copy* to avoid modification issues
            return
        elif remaining < 0:
            return

        for i in range(start, len(candidates)):
            combination.append(candidates[i])
            backtrack(combination, remaining - candidates[i], i)  # Allow reuse of the same element
            combination.pop()  # Backtrack: remove the last element to try another path

    backtrack([], target, 0)
    return result


def combinationSum_optimized(candidates, target):
    """
    2. Optimized Recursive Approach with Sorting

    This approach improves the basic recursion by sorting the candidates first.
    This allows us to prune the search space earlier when the current sum exceeds
    the target, avoiding unnecessary recursive calls.

    Time Complexity: O(N*logN + N^(T/M)), where N is the number of candidates, T is the target,
                    and M is the minimum value in candidates. The N*logN comes from sorting.
    Space Complexity: O(T/M) - The maximum depth of the recursion.
    """
    result = []
    candidates.sort()  # Sort candidates to optimize

    def backtrack(combination, remaining, start):
        if remaining == 0:
            result.append(list(combination))
            return
        elif remaining < 0:
            return

        for i in range(start, len(candidates)):
            # Optimization: If current candidate is too large, skip it and the rest (since sorted)
            if candidates[i] > remaining:
                break
            combination.append(candidates[i])
            backtrack(combination, remaining - candidates[i], i)
            combination.pop()

    backtrack([], target, 0)
    return result



def combinationSum_iterative(candidates, target):
    """
    3. Iterative Approach using a Stack

    This approach uses a stack to simulate the recursive calls.  It can be
    more complex to understand but avoids the overhead of recursion.

    Time Complexity:  O(N^(T/M)), where N is the number of candidates, T is the target,
                    and M is the minimum value in candidates.
    Space Complexity: O(T/M),  The maximum size of the stack.
    """
    result = []
    stack = [(0, [], target)]  # (start index, current combination, remaining target)

    while stack:
        start, combination, remaining = stack.pop()
        if remaining == 0:
            result.append(list(combination))
            continue
        elif remaining < 0:
            continue

        for i in range(start, len(candidates)):
            stack.append((i, combination + [candidates[i]], remaining - candidates[i]))
    return result



def combinationSum_dp(candidates, target):
    """
    4. Dynamic Programming (DP) Approach (Less Common, Modified)

    While the classic Combination Sum problem doesn't lend itself perfectly to
    traditional DP due to the allowance of repeated numbers, we can adapt a DP-like
    approach to build up solutions.  This is less efficient than backtracking
    but demonstrates a different problem-solving technique.  This approach is
    modified to fit the problem.

    Time Complexity: O(T * N * (T/M)), where T is the target, N is the number of candidates, and M is the smallest candidate.
    Space Complexity: O(T * (T/M)),  where T is the target and M is the smallest candidate.
    """
    dp = [[] for _ in range(target + 1)]  # dp[i] stores combinations that sum to i
    dp[0] = [[]]  # Base case: sum of 0 is an empty combination

    for num in candidates:
        for i in range(num, target + 1):
            for comb in dp[i - num]:
                dp[i].append(comb + [num])
    return dp[target]



def combinationSum_generator(candidates, target):
    """
    5.  Generator-Based Approach (Elegant Backtracking)

    This approach uses a generator function to produce the combinations lazily.
    It's a more Pythonic way to implement backtracking, often considered more readable.

    Time Complexity: O(N^(T/M)), where N is the number of candidates, T is the target,
                    and M is the minimum value in candidates.
    Space Complexity: O(T/M) -  Due to the recursion depth.  The generator itself has minimal overhead.
    """
    def generate_combinations(combination, remaining, start):
        if remaining == 0:
            yield list(combination)
            return
        elif remaining < 0:
            return

        for i in range(start, len(candidates)):
            yield from generate_combinations(combination + [candidates[i]], remaining - candidates[i], i)

    return list(generate_combinations([], target, 0))  # Consume the generator and return a list


def combinationSum_memoized(candidates, target):
    """
    6. Memoized Recursive Approach (Top-Down DP)

    This approach uses memoization to store the results of subproblems, effectively
    turning the recursive solution into a top-down dynamic programming approach.
    This can improve performance in cases with overlapping subproblems, although
    in the standard Combination Sum problem, the overlap isn't always significant.

    Time Complexity: O(N^(T/M)), where N is the number of candidates, T is the target,
                    and M is the minimum value in candidates.  In the worst case, it's the same
                    as the basic recursive approach, but with memoization, it can be faster
                    for certain inputs due to avoiding redundant calculations.
    Space Complexity: O(T * (T/M)) -  The size of the memoization dictionary.
    """
    memo = {}  # Store results of subproblems: (remaining, start) -> list of combinations

    def backtrack(remaining, start):
        if (remaining, start) in memo:
            return memo[(remaining, start)]

        if remaining == 0:
            return [[]]  # Base case: one empty combination
        if remaining < 0:
            return []

        result = []
        for i in range(start, len(candidates)):
            sub_combinations = backtrack(remaining - candidates[i], i)
            for comb in sub_combinations:
                result.append([candidates[i]] + comb)  # Prepend current candidate
        memo[(remaining, start)] = result  # Store the result
        return result

    return backtrack(target, 0)



if __name__ == "__main__":
    candidates = [2, 3, 6, 7]
    target = 7

    print(f"Candidates: {candidates}, Target: {target}")
    print("\n1. Recursive Approach:")
    result1 = combinationSum_recursive(candidates, target)
    print(result1)

    print("\n2. Optimized Recursive Approach with Sorting:")
    result2 = combinationSum_optimized(candidates, target)
    print(result2)

    print("\n3. Iterative Approach using a Stack:")
    result3 = combinationSum_iterative(candidates, target)
    print(result3)

    print("\n4. Dynamic Programming Approach:")
    result4 = combinationSum_dp(candidates, target)
    print(result4)

    print("\n5. Generator-Based Approach:")
    result5 = combinationSum_generator(candidates, target)
    print(result5)

    print("\n6. Memoized Recursive Approach:")
    result6 = combinationSum_memoized(candidates, target)
    print(result6)
