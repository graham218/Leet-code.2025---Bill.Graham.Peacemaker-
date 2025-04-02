def rotate_image_approach1(matrix):
    """
    Approach 1: Using extra space for a new matrix.
    Creates a new matrix and copies elements from the original matrix in rotated order.

    Args:
        matrix: A list of lists representing the image.

    Returns:
        The rotated image (in-place modification of the input).
    """
    n = len(matrix)
    rotated = [[0] * n for _ in range(n)]  # Create a new matrix

    for i in range(n):
        for j in range(n):
            rotated[j][n - 1 - i] = matrix[i][j]

    # Copy the rotated matrix back to the original matrix
    for i in range(n):
        for j in range(n):
            matrix[i][j] = rotated[i][j]

    return matrix

def rotate_image_approach2(matrix):
    """
    Approach 2: In-place rotation by transposing and then reversing each row.
    Transpose the matrix (swap rows and columns) and then reverse each row.

    Args:
        matrix: A list of lists representing the image.

    Returns:
        The rotated image (in-place modification of the input).
    """
    n = len(matrix)

    # Transpose the matrix
    for i in range(n):
        for j in range(i + 1, n):
            matrix[i][j], matrix[j][i] = matrix[j][i], matrix[i][j]

    # Reverse each row
    for row in matrix:
        row.reverse()

    return matrix

def rotate_image_approach3(matrix):
    """
    Approach 3: In-place rotation using four-way swaps.
    Iterate through layers and swap elements in four-way cycles.

    Args:
        matrix: A list of lists representing the image.

    Returns:
        The rotated image (in-place modification of the input).
    """
    n = len(matrix)

    for i in range(n // 2):
        for j in range(i, n - i - 1):
            temp = matrix[i][j]
            matrix[i][j] = matrix[n - 1 - j][i]
            matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j]
            matrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 - i]
            matrix[j][n - 1 - i] = temp

    return matrix

def rotate_image_approach4(matrix):
    """
    Approach 4: Similar to approach 3, but more explicit variable names.
    Iterate through layers and swap elements in four-way cycles, with clearer variable names.

    Args:
        matrix: A list of lists representing the image.

    Returns:
        The rotated image (in-place modification of the input).
    """
    n = len(matrix)
    for layer in range(n // 2):
        first = layer
        last = n - 1 - layer
        for i in range(first, last):
            offset = i - first
            top = matrix[first][i]  # save top
            # left -> top
            matrix[first][i] = matrix[last - offset][first]
            # bottom -> left
            matrix[last - offset][first] = matrix[last][last - offset]
            # right -> bottom
            matrix[last][last - offset] = matrix[i][last]
            # top -> right
            matrix[i][last] = top
    return matrix

def rotate_image_approach5(matrix):
    """
    Approach 5: Using zip and reversed.
    Uses zip and reversed to create the rotated matrix.

    Args:
        matrix: A list of lists representing the image.

    Returns:
        The rotated image (in-place modification of the input).
    """
    n = len(matrix)
    rotated = list(zip(*matrix[::-1]))
    for i in range(n):
        for j in range(n):
            matrix[i][j] = rotated[i][j]
    return matrix

# Example usage and output
matrix1 = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
matrix2 = [[5, 1, 9, 11], [2, 4, 8, 10], [13, 3, 6, 7], [15, 14, 12, 16]]

print("Original Matrix 1:", matrix1)
print("Approach 1 (Extra Space):", rotate_image_approach1(matrix1.copy()))
print("Approach 2 (Transpose + Reverse):", rotate_image_approach2(matrix1.copy()))
print("Approach 3 (Four-way Swaps):", rotate_image_approach3(matrix1.copy()))
print("Approach 4 (Four-way Swaps, clearer vars):", rotate_image_approach4(matrix1.copy()))
print("Approach 5 (zip and reversed):", rotate_image_approach5(matrix1.copy()))

print("\nOriginal Matrix 2:", matrix2)
print("Approach 1 (Extra Space):", rotate_image_approach1(matrix2.copy()))
print("Approach 2 (Transpose + Reverse):", rotate_image_approach2(matrix2.copy()))
print("Approach 3 (Four-way Swaps):", rotate_image_approach3(matrix2.copy()))
print("Approach 4 (Four-way Swaps, clearer vars):", rotate_image_approach4(matrix2.copy()))
print("Approach 5 (zip and reversed):", rotate_image_approach5(matrix2.copy()))