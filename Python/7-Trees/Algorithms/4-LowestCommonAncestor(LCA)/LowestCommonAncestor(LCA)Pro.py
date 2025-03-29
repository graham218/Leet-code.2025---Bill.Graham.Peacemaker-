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

# Approach 1: Recursive DFS Approach
def lca_recursive(root: Optional[TreeNode], p: TreeNode, q: TreeNode) -> Optional[TreeNode]:
    """
    Finds the Lowest Common Ancestor (LCA) of two nodes 'p' and 'q' in a binary tree
    using a recursive depth-first search (DFS) approach.

    The LCA of two nodes 'p' and 'q' is the deepest node in the tree that is an ancestor of both 'p' and 'q'.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.
        p (TreeNode): The first node to find the LCA with.
        q (TreeNode): The second node to find the LCA with.

    Returns:
        Optional[TreeNode]: The LCA of nodes 'p' and 'q'.  Returns None if either p or q is not in the tree.
    """
    if not root or root == p or root == q:
        return root  # Base case: If the root is None, or if the root is either p or q, it is the LCA
    left = lca_recursive(root.left, p, q)  # Recursively find LCA in the left subtree
    right = lca_recursive(root.right, p, q)  # Recursively find LCA in the right subtree
    # If p and q are in different subtrees, the current root is the LCA
    return root if left and right else left or right # If one subtree returns a node, and the other returns None, the node returned is the LCA.

# Approach 2: Iterative BFS with Parent Mapping
def lca_bfs(root: Optional[TreeNode], p: TreeNode, q: TreeNode) -> Optional[TreeNode]:
    """
    Finds the Lowest Common Ancestor (LCA) of two nodes 'p' and 'q' in a binary tree
    using an iterative breadth-first search (BFS) approach.  This method first builds a
    dictionary mapping each node to its parent.  Then, it finds the ancestors of 'p'
    and checks which ancestor is also an ancestor of 'q'.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.
        p (TreeNode): The first node.
        q (TreeNode): The second node.

    Returns:
        Optional[TreeNode]: The LCA of nodes 'p' and 'q'.  Returns None if either p or q is not in the tree.
    """
    parent = {root: None}  # Dictionary to store the parent of each node; the parent of root is None
    queue = [root]  # Queue for BFS traversal
    # Perform BFS to populate the parent dictionary.  We stop when both p and q are in the parent map.
    while p not in parent or q not in parent:
        node = queue.pop(0)  # Dequeue a node
        if node.left:
            parent[node.left] = node  # Map left child to its parent
            queue.append(node.left)  # Enqueue left child
        if node.right:
            parent[node.right] = node  # Map right child to its parent
            queue.append(node.right)  # Enqueue right child
    ancestors = set()  # Set to store the ancestors of node p
    # Collect all ancestors of p, including p itself.
    while p:
        ancestors.add(p)
        p = parent[p]  # Move to the parent of p
    # Find the first ancestor of q that is also an ancestor of p.
    while q not in ancestors:
        q = parent[q]  # Move to the parent of q
    return q  # q is now the LCA

# Approach 3: Path Tracking with Stacks
def lca_path_tracking(root: Optional[TreeNode], p: TreeNode, q: TreeNode) -> Optional[TreeNode]:
    """
    Finds the Lowest Common Ancestor (LCA) of two nodes 'p' and 'q' in a binary tree
    by tracking the paths from the root to each node.  It uses a helper function
    `find_path` to get the path to each target node.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.
        p (TreeNode): The first node.
        q (TreeNode): The second node.

    Returns:
        Optional[TreeNode]: The LCA of nodes 'p' and 'q'. Returns None if either p or q is not in the tree.
    """
    def find_path(node: Optional[TreeNode], target: TreeNode, path: List[TreeNode]) -> bool:
        """
        Recursively finds the path from the given node to the target node.

        Args:
            node (Optional[TreeNode]): The current node in the traversal.
            target (TreeNode): The target node to find the path to.
            path (List[TreeNode]): The list representing the path being built.

        Returns:
            bool: True if a path to the target is found, False otherwise.
        """
        if not node:
            return False  # Base case: If the node is None, there's no path.
        path.append(node)  # Add the current node to the path
        if node == target:
            return True  # Base case: If the current node is the target, we found the path.
        # Recursively search for the path in the left and right subtrees.
        if find_path(node.left, target, path) or find_path(node.right, target, path):
            return True  # If the path is found in either subtree, return True.
        path.pop()  # If the target is not found in the current subtree, remove the node from the path.
        return False  # Path not found in this node.

    path_p, path_q = [], []  # Lists to store the paths from the root to p and q, respectively.
    find_path(root, p, path_p)  # Find the path from the root to p.
    find_path(root, q, path_q)  # Find the path from the root to q.
    lca = None
    # Iterate through the paths to find the last common node.
    for a, b in zip(path_p, path_q):
        if a == b:
            lca = a  # Update lca as long as the nodes on the paths are the same
        else:
            break  # Stop when the paths diverge.
    return lca  # Return the last common node, which is the LCA.

# Approach 4: Depth and Parent Mapping with Iteration
def lca_depth_adjustment(root: Optional[TreeNode], p: TreeNode, q: TreeNode) -> Optional[TreeNode]:
    """
    Finds the Lowest Common Ancestor (LCA) of two nodes 'p' and 'q' in a binary tree
    by first calculating the depth of each node and mapping each node to its parent.
    Then, it brings the deeper node to the same level as the shallower node and
    iterates upwards until the two nodes meet.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.
        p (TreeNode): The first node.
        q (TreeNode): The second node.

    Returns:
        Optional[TreeNode]: The LCA of nodes 'p' and 'q'. Returns None if either p or q is not in the tree.
    """
    depth = {}  # Dictionary to store the depth of each node
    parent = {}  # Dictionary to store the parent of each node
    stack = [(root, None, 0)]  # Stack for iterative DFS, storing (node, parent, depth)
    # Perform iterative DFS to populate the depth and parent dictionaries.
    while stack:
        node, par, d = stack.pop()
        if node:
            depth[node] = d  # Store the depth of the current node
            parent[node] = par  # Store the parent of the current node
            stack.append((node.right, node, d + 1))  # Push the right child onto the stack
            stack.append((node.left, node, d + 1))  # Push the left child onto the stack

    # Bring the deeper node to the same depth as the shallower node.
    while depth[p] > depth[q]:
        p = parent[p]  # Move p upwards
    while depth[q] > depth[p]:
        q = parent[q]  # Move q upwards

    # Now p and q are at the same depth.  Iterate upwards until they meet.
    while p != q:
        p, q = parent[p], parent[q]  # Move both p and q upwards
    return p  # When p == q, p (or q) is the LCA

# Approach 5: Binary Lifting for LCA (Optimized for Large Trees)
def preprocess_lca(root: Optional[TreeNode]) -> (Dict[TreeNode, Optional[TreeNode]], Dict[TreeNode, int], Dict[TreeNode, List[Optional[TreeNode]]]):
    """
    Preprocesses the binary tree to efficiently find LCA queries later.  It computes:
    - parent: A dictionary mapping each node to its parent.
    - depth:  A dictionary mapping each node to its depth.
    - ancestors: A dictionary mapping each node to its 2^i-th ancestors for i in range(20).
                 ancestors[node][i] stores the 2^i-th ancestor of node.

    This preprocessing step is used to optimize LCA queries for large trees.  The 2^i-th
    ancestor information allows us to jump up the tree quickly.

    Args:
        root (Optional[TreeNode]): The root of the binary tree.

    Returns:
        tuple: A tuple containing the parent dictionary, the depth dictionary, and the ancestor dictionary.
    """
    parent = {}  # Dictionary to store the parent of each node
    depth = {}  # Dictionary to store the depth of each node
    ancestors = {}  # Dictionary to store the 2^i-th ancestors of each node
    stack = [(root, None, 0)]  # Stack for iterative DFS, storing (node, parent, depth)

    # Perform iterative DFS to populate parent, depth, and initial ancestor (2^0th ancestor) information.
    while stack:
        node, par, d = stack.pop()
        if node:
            parent[node] = par  # Store the parent
            depth[node] = d  # Store the depth
            ancestors[node] = [None] * 20  # Initialize the ancestor list for each node.  We store ancestors at 2^0, 2^1, ..., 2^19 levels.
            ancestors[node][0] = par  # The 2^0th ancestor is simply the parent.

            # Calculate the 2^i-th ancestors for i > 0 using dynamic programming:
            # The 2^i-th ancestor of a node is the 2^(i-1)-th ancestor of its 2^(i-1)-th ancestor.
            for i in range(1, 20):
                if ancestors[node][i - 1]:
                    ancestors[node][i] = parent[ancestors[node][i - 1]] if ancestors[node][i - 1] else None
            stack.append((node.right, node, d + 1))  # Push right child
            stack.append((node.left, node, d + 1))  # Push left child
    return parent, depth, ancestors

def lca_binary_lifting(p: TreeNode, q: TreeNode, parent: Dict[TreeNode, Optional[TreeNode]],
                       depth: Dict[TreeNode, int], ancestors: Dict[TreeNode, List[Optional[TreeNode]]]) -> Optional[TreeNode]:
    """
    Finds the Lowest Common Ancestor (LCA) of two nodes 'p' and 'q' using the precomputed
    ancestor information from `preprocess_lca` (binary lifting).

    Args:
        p (TreeNode): The first node.
        q (TreeNode): The second node.
        parent (Dict[TreeNode, Optional[TreeNode]]): Precomputed parent mapping.
        depth (Dict[TreeNode, int]): Precomputed depth mapping.
        ancestors (Dict[TreeNode, List[Optional[TreeNode]]]): Precomputed ancestor table.

    Returns:
        Optional[TreeNode]: The LCA of nodes 'p' and 'q'.
    """
    if depth[p] < depth[q]:
        p, q = q, p  # Ensure p is the deeper node
    diff = depth[p] - depth[q]  # Calculate the difference in depths
    # Bring p to the same level as q by jumping upwards using the precomputed ancestor table.
    for i in range(20):
        if diff & (1 << i):  # Check if the i-th bit of 'diff' is set (1 << i is 2^i)
            p = ancestors[p][i]  # Move p up by 2^i levels
    if p == q:
        return p  # If p and q are now the same node, it's the LCA
    # Move p and q upwards in parallel, comparing their 2^i-th ancestors.
    for i in range(19, -1, -1):  # Iterate from the highest ancestor level down to 0
        if ancestors[p][i] != ancestors[q][i]:  # If the 2^i-th ancestors are different
            p, q = ancestors[p][i], ancestors[q][i]  # Move both p and q up by 2^i levels
    return parent[p]  # The parent of p (or q) is the LCA

# Sample Tree Setup
tree = TreeNode(3, TreeNode(5, TreeNode(6), TreeNode(2, TreeNode(7), TreeNode(4))),
                TreeNode(1, TreeNode(0), TreeNode(8)))
p, q = tree.left, tree.left.right.right  # Nodes 5 and 4

# Execute LCA Methods
print("Recursive LCA:", lca_recursive(tree, p, q).val)
print("BFS Parent Mapping LCA:", lca_bfs(tree, p, q).val)
print("Path Tracking LCA:", lca_path_tracking(tree, p, q).val)
print("Depth Adjustment LCA:", lca_depth_adjustment(tree, p, q).val)

# Preprocessing for Binary Lifting
parent_map, depth_map, ancestors_map = preprocess_lca(tree)
print("Binary Lifting LCA:", lca_binary_lifting(p, q, parent_map, depth_map, ancestors_map).val)
