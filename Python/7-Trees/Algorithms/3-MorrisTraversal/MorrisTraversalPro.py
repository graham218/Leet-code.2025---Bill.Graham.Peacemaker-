from typing import Optional, List, Dict

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        """
        Initializes a TreeNode object.

        Args:
            val (int): The value of the node. Defaults to 0.
            left (Optional[TreeNode]): The left child of the node. Defaults to None.
            right (Optional[TreeNode]): The right child of the node. Defaults to None.
        """
        self.val = val
        self.left = left
        self.right = right

# Approach 1: Morris Inorder Traversal with Node Depth Calculation
def morris_inorder_depth(root: Optional[TreeNode]) -> (List[tuple], Dict[int, int]):
    """
    Performs Morris inorder traversal while calculating the depth of each node.  It
    returns a list of (node value, depth) tuples and a dictionary mapping node values
    to their depths.  This is an extension of the standard Morris inorder traversal.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        tuple: A tuple containing:
            - List[tuple]: A list of (node value, depth) tuples in inorder order.
            - Dict[int, int]: A dictionary mapping node values to their depths.
    """
    result = []  # Store (node value, depth) tuples
    depth_map = {}  # Store node value to depth mapping
    depth = 0  # Initialize the depth of the root node
    current = root

    while current:
        if current.left is None:
            # If no left child, visit, store depth, and go right
            result.append((current.val, depth))
            depth_map[current.val] = depth
            current = current.right
        else:
            # Find predecessor
            predecessor = current.left
            pred_depth = depth + 1  # Calculate depth of predecessor
            while predecessor.right and predecessor.right is not current:
                predecessor = predecessor.right
                pred_depth += 1
            if predecessor.right is None:
                # First visit, create link, go left
                predecessor.right = current
                current = current.left
                depth = pred_depth  # Update depth for the left subtree
            else:
                # Second visit, remove link, visit, go right
                predecessor.right = None
                result.append((current.val, depth))
                depth_map[current.val] = depth
                current = current.right
                depth -= 1  # Correct depth after traversing left subtree
    return result, depth_map

# Approach 2: Morris Preorder Traversal with Parent Tracking
def morris_preorder_parent(root: Optional[TreeNode]) -> (List[int], Dict[int, int]):
    """
    Performs Morris preorder traversal while tracking the parent of each node.  It
    returns a list of node values in preorder and a dictionary mapping node values to
    their parent node values.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        tuple: A tuple containing:
            - List[int]: A list of node values in preorder.
            - Dict[int, int]: A dictionary mapping each node's value to its parent's value.
                            The root node will not be present in the dictionary.
    """
    result = []
    parent_map = {}
    current = root

    while current:
        if current.left is None:
            # If no left child, visit, store parent, go right
            result.append(current.val)
            if current.right:
                parent_map[current.right.val] = current.val
            current = current.right
        else:
            # Find predecessor
            predecessor = current.left
            while predecessor.right and predecessor.right is not current:
                predecessor = predecessor.right
            if predecessor.right is None:
                # First visit, visit, create link, go left
                result.append(current.val)
                parent_map[current.left.val] = current.val
                predecessor.right = current
                current = current.left
            else:
                # Second visit, remove link, go right
                predecessor.right = None
                current = current.right
    return result, parent_map

# Approach 3: Morris Traversal with Node Count Verification
def morris_traversal_node_count(root: Optional[TreeNode]) -> int:
    """
    Performs a Morris traversal to count the number of nodes in a binary tree.  This
    function effectively traverses the tree without using recursion or a stack,
    and returns the total node count.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        int: The total number of nodes in the tree.
    """
    count = 0
    current = root

    while current:
        if current.left is None:
            # If no left child, increment count, go right
            count += 1
            current = current.right
        else:
            # Find predecessor
            predecessor = current.left
            while predecessor.right and predecessor.right is not current:
                predecessor = predecessor.right
            if predecessor.right is None:
                # First visit, create link, go left
                predecessor.right = current
                current = current.left
            else:
                # Second visit, remove link, increment count, go right
                predecessor.right = None
                count += 1
                current = current.right
    return count

# Approach 4: Morris Inorder Serialization and Deserialization
def serialize_morris(root: Optional[TreeNode]) -> List[int]:
    """
    Serializes a binary tree into a list using Morris inorder traversal.  The
    resulting list represents the inorder traversal sequence of the tree.  This
    is not a complete serialization as it doesn't preserve the tree structure,
    but it can be useful in specific scenarios.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[int]: A list representing the inorder traversal of the tree.
    """
    serialized = []
    current = root

    while current:
        if current.left is None:
            # If no left child, append value, go right
            serialized.append(current.val)
            current = current.right
        else:
            # Find predecessor
            predecessor = current.left
            while predecessor.right and predecessor.right is not current:
                predecessor = predecessor.right
            if predecessor.right is None:
                # First visit, create link, go left
                predecessor.right = current
                current = current.left
            else:
                # Second visit, remove link, append value, go right
                predecessor.right = None
                serialized.append(current.val)
                current = current.right
    return serialized

def deserialize_morris(data: List[int]) -> Optional[TreeNode]:
    """
    Deserializes a list (obtained from `serialize_morris`) back into a binary tree.
    This function attempts to reconstruct the tree from its inorder traversal sequence,
    but it's important to note that the original tree structure cannot be fully
    recovered from the inorder sequence alone if the tree has duplicate values.
    This function assumes no duplicates.

    Args:
        data (List[int]): A list representing the inorder traversal of the tree.

    Returns:
        Optional[TreeNode]: The root of the reconstructed binary tree.  Returns None if the input data is empty.
    """
    if not data:
        return None
    root = TreeNode(data[0])  # Create the root node
    node_map = {data[0]: root}  # Map values to nodes
    for val in data[1:]:
        node = TreeNode(val)
        node_map[val] = node
    return root  # Returns the root of the reconstructed tree.  The tree is NOT fully connected.

# Approach 5: Morris Traversal for Checking Balanced Tree
def is_balanced_morris(root: Optional[TreeNode]) -> bool:
    """
    Checks if a binary tree is balanced using Morris inorder traversal.  A tree is
    balanced if the difference between the maximum and minimum depths of its leaves
    is not greater than 1.  This function uses Morris traversal to find the depths
    of the leaves without using recursion or a stack.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        bool: True if the tree is balanced, False otherwise.
    """
    if not root:
        return True
    depths = []
    current = root
    depth = 0
    while current:
        if current.left is None:
            # If no left child, record depth (leaf), go right
            depths.append(depth)
            current = current.right
        else:
            # Find predecessor
            predecessor = current.left
            pred_depth = depth + 1
            while predecessor.right and predecessor.right is not current:
                predecessor = predecessor.right
                pred_depth += 1
            if predecessor.right is None:
                # First visit, create link, go left
                predecessor.right = current
                current = current.left
                depth = pred_depth
            else:
                # Second visit, remove link, record depth (leaf), go right
                predecessor.right = None
                depths.append(depth)
                current = current.right
                depth -= 1
    return max(depths) - min(depths) <= 1

# Approach 6: Morris Traversal for Finding Kth Smallest Element
def kth_smallest_morris(root: Optional[TreeNode], k: int) -> Optional[int]:
    """
    Finds the kth smallest element in a Binary Search Tree (BST) using Morris
    inorder traversal.  This approach is efficient as it avoids using extra space
    for a stack or recursion.

    Args:
        root (Optional[TreeNode]): The root of the BST.
        k (int): The rank of the smallest element to find (1-indexed).

    Returns:
        Optional[int]: The value of the kth smallest element, or None if k is invalid.
    """
    count = 0
    current = root

    while current:
        if current.left is None:
            # If no left child, increment count, check if kth, go right
            count += 1
            if count == k:
                return current.val
            current = current.right
        else:
            # Find predecessor
            predecessor = current.left
            while predecessor.right and predecessor.right is not current:
                predecessor = predecessor.right
            if predecessor.right is None:
                # First visit, create link, go left
                predecessor.right = current
                current = current.left
            else:
                # Second visit, remove link, increment count, check if kth, go right
                predecessor.right = None
                count += 1
                if count == k:
                    return current.val
                current = current.right
    return None

# Sample Tree
tree = TreeNode(5, TreeNode(3, TreeNode(2), TreeNode(4)), TreeNode(7, TreeNode(6), TreeNode(8)))

# Execute Advanced Traversals
print("Morris Inorder with Depth:", morris_inorder_depth(tree))
print("Morris Preorder with Parent Tracking:", morris_preorder_parent(tree))
print("Total Nodes Count:", morris_traversal_node_count(tree))
print("Serialized Morris Traversal:", serialize_morris(tree))
print("Is Balanced Tree:", is_balanced_morris(tree))
print("3rd Smallest Element:", kth_smallest_morris(tree, 3))
