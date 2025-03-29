from typing import Optional, List

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

# Approach 1: Morris Inorder Traversal
def morris_inorder(root: Optional[TreeNode]) -> List[int]:
    """
    Performs an inorder traversal of a binary tree using the Morris traversal algorithm.
    Morris traversal is a space-optimized approach that avoids using a stack or recursion.  It
    works by temporarily modifying the tree structure during traversal.

    The key idea is to create a temporary link (a "Morris link") from the rightmost
    node of the left subtree to the current node. This allows us to traverse back to
    the current node after visiting the left subtree, without using a stack.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[int]: A list containing the node values in inorder traversal order.
    """
    result = []  # Initialize an empty list to store the inorder traversal result
    current = root  # Start from the root of the tree

    while current:
        if current.left is None:
            # If the current node has no left child, visit the node, and move to the right child.
            result.append(current.val)
            current = current.right
        else:
            # Find the predecessor (the rightmost node in the left subtree).
            predecessor = current.left
            while predecessor.right and predecessor.right is not current:
                predecessor = predecessor.right

            if predecessor.right is None:
                # If the predecessor's right child is None, it means we haven't visited
                # the left subtree yet.  Create the Morris link.
                predecessor.right = current  # Create the temporary link
                current = current.left      # Move to the left child to traverse it
            else:
                # If the predecessor's right child is current, it means we've finished
                # traversing the left subtree.  Remove the Morris link and visit the current node.
                predecessor.right = None    # Remove the temporary link
                result.append(current.val)  # Visit the current node (inorder)
                current = current.right      # Move to the right child
    return result  # Return the list of node values in inorder order

# Approach 2: Morris Preorder Traversal
def morris_preorder(root: Optional[TreeNode]) -> List[int]:
    """
    Performs a preorder traversal of a binary tree using the Morris traversal algorithm.
    Similar to inorder traversal, this method avoids using a stack or recursion by
    temporarily modifying the tree structure.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[int]: A list containing the node values in preorder traversal order.
    """
    result = []  # Initialize an empty list to store the preorder traversal result
    current = root  # Start from the root

    while current:
        if current.left is None:
            # If the current node has no left child, visit it and move to the right.
            result.append(current.val)
            current = current.right
        else:
            # Find the predecessor (rightmost node in the left subtree)
            predecessor = current.left
            while predecessor.right and predecessor.right is not current:
                predecessor = predecessor.right

            if predecessor.right is None:
                # If predecessor's right is None, it's the first time visiting.
                # Visit the current node (preorder) and create the Morris link.
                result.append(current.val)
                predecessor.right = current
                current = current.left
            else:
                # If predecessor's right is current, we've visited the left.
                # Remove the link and move to the right.
                predecessor.right = None
                current = current.right
    return result

# Approach 3: Morris Postorder Traversal (Reverse Morris Inorder)
def morris_postorder(root: Optional[TreeNode]) -> List[int]:
    """
    Performs a postorder traversal of a binary tree using a modified Morris traversal.
    Postorder is more complex with Morris traversal than inorder or preorder.  This
    implementation uses a dummy node and a helper function to reverse the links.
    The idea is to visit the nodes in a reverse inorder fashion, and then reverse
    the collected nodes.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[int]: A list containing the node values in postorder traversal order.
    """
    result = []
    dummy = TreeNode(0)  # Create a dummy node to handle the root
    dummy.left = root
    current = dummy

    while current:
        if current.left is None:
            current = current.right
        else:
            predecessor = current.left
            while predecessor.right and predecessor.right is not current:
                predecessor = predecessor.right
            if predecessor.right is None:
                predecessor.right = current
                current = current.left
            else:
                predecessor.right = None
                collect_reverse(current.left, predecessor, result)  # Collect nodes in reverse
                current = current.right
    return result

# Helper function to collect nodes in reverse order
def collect_reverse(start: TreeNode, end: TreeNode, result: List[int]):
    """
    Helper function to collect the values of nodes in a reversed order,
    starting from 'start' and ending at 'end'.  This is used in the
    Morris postorder traversal to get the postorder sequence.

    Args:
        start (TreeNode): The starting node for collecting values.
        end (TreeNode): The ending node for collecting values.
        result (List[int]): The list to store the collected node values.
    """
    reverse = []
    while start != end:
        reverse.append(start.val)
        start = start.right
    reverse.append(end.val)
    result.extend(reverse[::-1])  # Reverse the collected values and add to result

# Approach 4: Morris Level Order Traversal (Simulated Using Morris Links)
def morris_level_order(root: Optional[TreeNode]) -> List[List[int]]:
    """
    Performs a level order traversal of a binary tree, but it's not a true Morris
    traversal.  Morris traversal, in its standard form, is designed for inorder,
    preorder, and postorder.  This function uses a standard iterative level order
    traversal (using a queue) and does not utilize the link manipulation that
    is characteristic of Morris traversal.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[List[int]]: A list of lists, where each inner list represents a level
                         in the tree.
    """
    if not root:
        return []
    result = []
    queue = [root]  # Use a queue for standard level order traversal
    while queue:
        level = []
        next_queue = []
        for node in queue:
            level.append(node.val)
            if node.left:
                next_queue.append(node.left)
            if node.right:
                next_queue.append(node.right)
        result.append(level)
        queue = next_queue
    return result

# Approach 5: Morris Spiral Order Traversal (Zigzag Using Morris)
def morris_spiral_order(root: Optional[TreeNode]) -> List[List[int]]:
    """
    Performs a spiral order (or zigzag) traversal of a binary tree.  This is also
    not a true Morris traversal in the standard sense.  It uses a standard
    iterative level order traversal (with a queue) and then reverses the order of
    nodes at alternate levels to achieve the spiral pattern.  It does not use the
    threaded link manipulation of Morris traversal.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        List[List[int]]: A list of lists, where each inner list represents a level
                         in the tree, with the order of nodes reversed at alternate levels.
    """
    if not root:
        return []
    result = []
    queue = [root]
    left_to_right = True  # Flag to indicate traversal direction
    while queue:
        level = []
        next_queue = []
        for node in queue:
            level.append(node.val)
            if node.left:
                next_queue.append(node.left)
            if node.right:
                next_queue.append(node.right)
        if not left_to_right:
            level.reverse()  # Reverse the level if going right-to-left
        result.append(level)
        queue = next_queue
        left_to_right = not left_to_right  # Toggle direction for the next level
    return result

# Sample Tree
tree = TreeNode(1, TreeNode(2, TreeNode(4), TreeNode(5)), TreeNode(3, TreeNode(6), TreeNode(7)))

# Execute Traversals
print("Morris Inorder:", morris_inorder(tree))
print("Morris Preorder:", morris_preorder(tree))
print("Morris Postorder:", morris_postorder(tree))
print("Morris Level Order:", morris_level_order(tree))
print("Morris Spiral Order:", morris_spiral_order(tree))
