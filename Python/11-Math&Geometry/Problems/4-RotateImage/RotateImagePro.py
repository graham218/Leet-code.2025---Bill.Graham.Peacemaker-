import numpy as np
from collections import deque

def rotate_image_inplace(matrix):
    """
    Approach 1: Rotate Image In-Place (Transpose + Reverse Rows)
    """
    n = len(matrix)
    # Transpose the matrix
    for i in range(n):
        for j in range(i, n):
            matrix[i][j], matrix[j][i] = matrix[j][i], matrix[i][j]
    # Reverse each row
    for row in matrix:
        row.reverse()
    return matrix


def rotate_image_copy(matrix):
    """
    Approach 2: Rotate Image Using a New Matrix (Extra Space)
    """
    n = len(matrix)
    rotated = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            rotated[j][n - 1 - i] = matrix[i][j]
    return rotated


def rotate_image_numpy(matrix):
    """
    Approach 3: Rotate Image Using NumPy
    """
    return np.rot90(matrix, k=-1).tolist()


def rotate_image_deque(matrix):
    """
    Approach 4: Rotate Image Using Deque (for row shifting)
    """
    n = len(matrix)
    rotated = [deque() for _ in range(n)]
    for i in range(n):
        for j in range(n):
            rotated[j].appendleft(matrix[i][j])
    return [list(row) for row in rotated]


def rotate_image_zip(matrix):
    """
    Approach 5: Rotate Image Using Zip
    """
    return [list(row) for row in zip(*matrix[::-1])]


def rotate_image_reverse_transpose(matrix):
    """
    Approach 6: Rotate Image by Reversing and Transposing
    """
    matrix.reverse()
    return [list(row) for row in zip(*matrix)]


# Sample Test Cases
matrix = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
]

print("Original Matrix:")
print(np.array(matrix))

print("\nRotated In-Place:")
print(np.array(rotate_image_inplace([row[:] for row in matrix])))

print("\nRotated Using Copy:")
print(np.array(rotate_image_copy(matrix)))

print("\nRotated Using NumPy:")
print(np.array(rotate_image_numpy(matrix)))

print("\nRotated Using Deque:")
print(np.array(rotate_image_deque(matrix)))

print("\nRotated Using Zip:")
print(np.array(rotate_image_zip(matrix)))

print("\nRotated Using Reverse & Transpose:")
print(np.array(rotate_image_reverse_transpose(matrix)))
