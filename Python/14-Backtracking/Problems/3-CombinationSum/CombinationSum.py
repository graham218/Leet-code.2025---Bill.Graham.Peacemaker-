from typing import List

def combinationSum_1(candidates: List[int], target: int) -> List[List[int]]:
    """
    Approach 1: Classic Backtracking

    -   Base Case: If target is 0, we found a valid combination.
    -   Base Case: If target is negative, or we've run out of candidates, backtrack.
    -   Recursive Step:
        -   Include the current candidate: Add it to the path, reduce the target, and recurse.
        -   Exclude the current candidate: Skip it and recurse with the next candidate.
    """
    result = []

    def backtrack(combination, remaining_target, start_index):
        if remaining_target == 0:
            result.append(list(combination))  # Append a *copy* to avoid modification issues
            return
        if remaining_target < 0 or start_index >= len(candidates):
            return

        # Include the current candidate
        combination.append(candidates[start_index])
        backtrack(combination, remaining_target - candidates[start_index], start_index)  # Allow reuse
        combination.pop()  # Backtrack: Remove the candidate

        # Exclude the current candidate
        backtrack(combination, remaining_target, start_index + 1)

    backtrack([], target, 0)
    return result

def combinationSum_2(candidates: List[int], target: int) -> List[List[int]]:
    """
    Approach 2: Backtracking with Optimized Looping

    -   Similar to Approach 1, but uses a for loop in the backtrack function.
    -   This can make the logic slightly more compact.
    """
    result = []

    def backtrack(combination, remaining_target, start_index):
        if remaining_target == 0:
            result.append(list(combination))
            return
        if remaining_target < 0:
            return

        for i in range(start_index, len(candidates)):
            combination.append(candidates[i])
            backtrack(combination, remaining_target - candidates[i], i)
            combination.pop()

    backtrack([], target, 0)
    return result
def combinationSum_3(candidates: List[int], target: int) -> List[List[int]]:
    """
    Approach 3: Backtracking with Early Pruning

    -   Sort the candidates array.
    -   If a candidate is larger than the remaining target, we can skip it
        and all subsequent candidates.
    """
    result = []
    candidates.sort()  # Important for pruning

    def backtrack(combination, remaining_target, start_index):
        if remaining_target == 0:
            result.append(list(combination))
            return
        if remaining_target < 0:
            return

        for i in range(start_index, len(candidates)):
            if candidates[i] > remaining_target:  # Pruning step
                break
            combination.append(candidates[i])
            backtrack(combination, remaining_target - candidates[i], i)
            combination.pop()

    backtrack([], target, 0)
    return result

def combinationSum_4(candidates: List[int], target: int) -> List[List[int]]:
    """
     Approach 4: Using a Helper Function for Backtracking

    - Separates the backtracking logic into a helper function.
    - This approach aims to improve code organization and readability
    """
    result = []

    def _backtrack(combination, remaining_target, start_index):
        if remaining_target == 0:
            result.append(list(combination))
            return
        if remaining_target < 0:
            return

        for i in range(start_index, len(candidates)):
            combination.append(candidates[i])
            _backtrack(combination, remaining_target - candidates[i], i)
            combination.pop()

    def backtrack(candidates, target):
        _backtrack([], target, 0)
        return result
    return backtrack(candidates, target)

def combinationSum_5(candidates: List[int], target: int) -> List[List[int]]:
    """
    Approach 5: Backtracking with Explicit State Variables

    - Makes the state variables (combination, remaining_target) very clear
      in each recursive call.
    """
    result = []

    def backtrack(candidates, target, combination, remaining_target, start_index):
        if remaining_target == 0:
            result.append(list(combination))
            return
        if remaining_target < 0:
            return

        for i in range(start_index, len(candidates)):
            new_combination = combination + [candidates[i]] # Create new combination.
            backtrack(candidates, target, new_combination, remaining_target - candidates[i], i)

    backtrack(candidates, target, [], target, 0)
    return result

def combinationSum_6(candidates: List[int], target: int) -> List[List[int]]:
    """
    Approach 6:  Backtracking with generator (Yield)

     - Uses a generator for backtracking
    """
    def backtrack(candidates, target, combination, start_index):
        if target == 0:
            yield list(combination)
            return
        if target < 0:
            return

        for i in range(start_index, len(candidates)):
            yield from backtrack(candidates, target - candidates[i], combination + [candidates[i]], i)

    return list(backtrack(candidates, target, [], 0))
if __name__ == "__main__":
    candidates = [2, 3, 6, 7]
    target = 7

    print("Candidates:", candidates)
    print("Target:", target)

    print("\nApproach 1: Classic Backtracking")
    result1 = combinationSum_1(candidates, target)
    print("Result:", result1)

    print("\nApproach 2: Backtracking with Optimized Looping")
    result2 = combinationSum_2(candidates, target)
    print("Result:", result2)

    print("\nApproach 3: Backtracking with Early Pruning")
    result3 = combinationSum_3(candidates, target)
    print("Result:", result3)

    print("\nApproach 4: Using a Helper Function for Backtracking")
    result4 = combinationSum_4(candidates, target)
    print("Result:", result4)

    print("\nApproach 5: Backtracking with Explicit State Variables")
    result5 = combinationSum_5(candidates, target)
    print("Result:", result5)

    print("\nApproach 6: Backtracking with Generator (Yield)")
    result6 = combinationSum_6(candidates, target)
    print("Result:", result6)
