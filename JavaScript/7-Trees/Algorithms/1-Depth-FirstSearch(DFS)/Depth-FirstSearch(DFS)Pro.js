// Define a basic TreeNode class for our tree examples
class TreeNode {
  constructor(value) {
    this.value = value;
    this.children = [];
  }
}

// 1. DFS for File System Traversal (Real-world example: Finding a specific file)
//   - Iterative approach using a stack
//   - Useful for exploring directory structures
function dfsFileSystemTraversal(root, targetFile) {
  if (!root) return null;

  const stack = [root];

  while (stack.length > 0) {
    const currentNode = stack.pop();

    // Simulate file check (replace with actual file comparison)
    if (currentNode.value === targetFile) {
      console.log(`File found: ${targetFile}`);
      return currentNode; // Return the node if found
    }

    // Add children to the stack in reverse order for LIFO (pre-order traversal)
    for (let i = currentNode.children.length - 1; i >= 0; i--) {
      stack.push(currentNode.children[i]);
    }
  }

  console.log(`File not found: ${targetFile}`);
  return null; // Return null if not found
}

// 2. DFS for Website Sitemap Generation (Real-world example: Crawling a website)
//   - Recursive approach
//   - Useful for generating a list of all pages on a website
function dfsSitemap(node, visited = new Set(), sitemap = []) {
  if (!node) return sitemap;

  visited.add(node.value); // Use node.value as a unique identifier for a page

  sitemap.push(node.value); // Add the current page to the sitemap

  for (const child of node.children) {
    if (!visited.has(child.value)) {
      dfsSitemap(child, visited, sitemap);
    }
  }
  return sitemap;
}

// 3. DFS for Dependency Resolution (Real-world example: Building a software project)
//   - Recursive approach with post-order traversal
//   - Useful for determining the order in which modules need to be built
function dfsDependencyResolution(node, resolved = new Set(), resolutionOrder = []) {
  if (!node) return resolutionOrder;

  for (const child of node.children) {
    dfsDependencyResolution(child, resolved, resolutionOrder);
  }

  if (!resolved.has(node.value)) {
    resolutionOrder.push(node.value);
    resolved.add(node.value);
  }
  return resolutionOrder;
}

// 4. DFS for Game Tree Traversal (Real-world example: AI in a game like chess)
//    - Recursive approach
//    - Explore possible moves in a game
function dfsGameTreeTraversal(node, depthLimit, currentDepth = 0) {
  if (!node || currentDepth > depthLimit) {
    return; // Base case: reached the end of a branch or depth limit
  }

  // Simulate visiting/evaluating a game state
  console.log(`Visiting game state: ${node.value} at depth: ${currentDepth}`);

  for (const child of node.children) {
    dfsGameTreeTraversal(child, depthLimit, currentDepth + 1);
  }
  // In a real game, you would evaluate the node here and return a score.
}

// 5. DFS for Social Network Traversal (Real-world example: Finding connections)
//   - Iterative approach using a stack
function dfsSocialNetworkTraversal(startNode, targetUser, visited = new Set()) {
    if (!startNode) return null;

    const stack = [startNode];

    while (stack.length > 0) {
        const currentNode = stack.pop();

        if (visited.has(currentNode.value)) {
            continue; // Skip already visited nodes
        }

        visited.add(currentNode.value);
        console.log(`Visiting user: ${currentNode.value}`); // Simulate visiting

        if (currentNode.value === targetUser) {
            console.log(`Found target user: ${targetUser}`);
            return currentNode; // Return the node
        }

        for (let i = currentNode.children.length - 1; i >= 0; i--) {
            stack.push(currentNode.children[i]);
        }
    }
    console.log(`Target user: ${targetUser} not found`);
    return null;
}

// --- Example Usage ---
// 1. File System Traversal
const fileSystemRoot = new TreeNode("/");
const documents = new TreeNode("Documents");
const pictures = new TreeNode("Pictures");
const report1 = new TreeNode("report1.pdf");
const report2 = new TreeNode("report2.pdf");
const vacation = new TreeNode("vacation.jpg");
const family = new TreeNode("family.jpg");

fileSystemRoot.children = [documents, pictures];
documents.children = [report1, report2];
pictures.children = [vacation, family];

console.log("--- 1. File System Traversal ---");
dfsFileSystemTraversal(fileSystemRoot, "report1.pdf"); // File found
dfsFileSystemTraversal(fileSystemRoot, "nonexistent.pdf"); // File not found

// 2. Website Sitemap Generation
const websiteRoot = new TreeNode("home");
const about = new TreeNode("about");
const services = new TreeNode("services");
const contact = new TreeNode("contact");
const team = new TreeNode("team");
const history = new TreeNode("history");

websiteRoot.children = [about, services, contact];
about.children = [team, history];
services.children = [contact];

console.log("\n--- 2. Website Sitemap Generation ---");
const sitemap = dfsSitemap(websiteRoot);
console.log(sitemap);

// 3. Dependency Resolution
const a = new TreeNode("A");
const b = new TreeNode("B");
const c = new TreeNode("C");
const d = new TreeNode("D");
const e = new TreeNode("E");

a.children = [b, c];
b.children = [d];
c.children = [d, e];
d.children = [e];

console.log("\n--- 3. Dependency Resolution ---");
const buildOrder = dfsDependencyResolution(a);
console.log(buildOrder); // Expected: [ 'E', 'D', 'B', 'C', 'A' ] or similar

// 4. Game Tree Traversal
const gameRoot = new TreeNode("Start");
const move1 = new TreeNode("Move 1");
const move2 = new TreeNode("Move 2");
const move3 = new TreeNode("Move 3");
const move4 = new TreeNode("Move 4");
const move5 = new TreeNode("Move 5");

gameRoot.children = [move1, move2];
move1.children = [move3, move4];
move2.children = [move5];

console.log("\n--- 4. Game Tree Traversal ---");
dfsGameTreeTraversal(gameRoot, 2); // Explore up to depth 2

// 5. Social Network Traversal
const userA = new TreeNode("Alice");
const userB = new TreeNode("Bob");
const userC = new TreeNode("Charlie");
const userD = new TreeNode("David");
const userE = new TreeNode("Eve");

userA.children = [userB, userC];
userB.children = [userD];
userC.children = [userE];
userD.children = [userE];

console.log("\n--- 5. Social Network Traversal ---");
dfsSocialNetworkTraversal(userA, "Eve");
dfsSocialNetworkTraversal(userA, "Frank");
