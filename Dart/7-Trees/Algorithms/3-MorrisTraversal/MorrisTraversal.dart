// Dart program demonstrating Morris Traversal on Binary Trees
// Implementing 5 different approaches

class TreeNode {
  int value;
  TreeNode? left, right;
  TreeNode(this.value, [this.left, this.right]);
}

// 1. Morris Inorder Traversal (Without Recursion or Stack)
void morrisInorder(TreeNode? root) {
  TreeNode? current = root;
  // Traverse the tree
  while (current != null) {
    // If the current node has no left child
    if (current.left == null) {
      // Print the current node's value and move to the right child
      print(current.value);
      current = current.right;
    } else {
      // Find the inorder predecessor of the current node
      TreeNode? predecessor = current.left;
      // Traverse to the rightmost node of the left subtree or to the thread
      while (predecessor!.right != null && predecessor.right != current) {
        predecessor = predecessor.right;
      }
      // If the right child of the predecessor is null, create a thread to the current node
      if (predecessor.right == null) {
        predecessor.right = current;
        current = current.left; // Move to the left child
      } else {
        // If the thread exists, remove it, print the current node's value, and move to the right child
        predecessor.right = null;
        print(current.value);
        current = current.right;
      }
    }
  }
  // This traversal visits nodes in ascending order without using recursion or a stack.
}

// 2. Morris Preorder Traversal
void morrisPreorder(TreeNode? root) {
  TreeNode? current = root;
  while (current != null) {
    if (current.left == null) {
      print(current.value);
      current = current.right;
    } else {
      TreeNode? predecessor = current.left;
      while (predecessor!.right != null && predecessor.right != current) {
        predecessor = predecessor.right;
      }
      if (predecessor.right == null) {
        print(current.value); // Print before creating the thread
        predecessor.right = current;
        current = current.left;
      } else {
        predecessor.right = null;
        current = current.right;
      }
    }
  }
  // This traversal visits the current node before traversing its children.
}

// 3. Morris Postorder Traversal (Reverse Nodes)
void morrisPostorder(TreeNode? root) {
  // Create a dummy node to handle the root node's left subtree
  TreeNode? dummy = TreeNode(0);
  dummy.left = root;
  TreeNode? current = dummy;
  while (current != null) {
    if (current.left == null) {
      current = current.right;
    } else {
      TreeNode? predecessor = current.left;
      while (predecessor!.right != null && predecessor.right != current) {
        predecessor = predecessor.right;
      }
      if (predecessor.right == null) {
        predecessor.right = current;
        current = current.left;
      } else {
        // Reverse and print the nodes between current.left and predecessor (inclusive)
        printReverse(current.left!, predecessor);
        predecessor.right = null;
        current = current.right;
      }
    }
  }
  // This traversal visits the nodes of the left subtree, then the right subtree, then the current node.
}

void printReverse(TreeNode start, TreeNode end) {
  // Reverse the linked list of right children between start and end and print the values
  List<int> values = [];
  TreeNode? node = start;
  while (node != end) {
    values.add(node!.value);
    node = node.right;
  }
  values.add(end.value);
  values.reversed.forEach(print);
}

// 4. Morris Traversal for Finding the Kth Smallest Element
int? morrisKthSmallest(TreeNode? root, int k) {
  TreeNode? current = root;
  int count = 0;
  while (current != null) {
    if (current.left == null) {
      count++;
      if (count == k) return current.value;
      current = current.right;
    } else {
      TreeNode? predecessor = current.left;
      while (predecessor!.right != null && predecessor.right != current) {
        predecessor = predecessor.right;
      }
      if (predecessor.right == null) {
        predecessor.right = current;
        current = current.left;
      } else {
        predecessor.right = null;
        count++;
        if (count == k) return current.value;
        current = current.right;
      }
    }
  }
  return null;
  // This function finds the k-th smallest element in the tree.
}

// 5. Morris Traversal to Count Nodes
int morrisCountNodes(TreeNode? root) {
  TreeNode? current = root;
  int count = 0;
  while (current != null) {
    if (current.left == null) {
      count++;
      current = current.right;
    } else {
      TreeNode? predecessor = current.left;
      while (predecessor!.right != null && predecessor.right != current) {
        predecessor = predecessor.right;
      }
      if (predecessor.right == null) {
        predecessor.right = current;
        current = current.left;
      } else {
        predecessor.right = null;
        count++;
        current = current.right;
      }
    }
  }
  return count;
  // This function counts the total number of nodes in the tree.
}

void main() {
  // Constructing a binary tree
  TreeNode root = TreeNode(5,
      TreeNode(3, TreeNode(2), TreeNode(4)),
      TreeNode(8, TreeNode(7), TreeNode(9)));

  print("Morris Inorder Traversal:");
  morrisInorder(root);

  print("\nMorris Preorder Traversal:");
  morrisPreorder(root);

  print("\nMorris Postorder Traversal:");
  morrisPostorder(root);

  int k = 3;
  print("\n$k-th Smallest Element: ${morrisKthSmallest(root, k)}");
  print("\nTotal Nodes: ${morrisCountNodes(root)}");
}