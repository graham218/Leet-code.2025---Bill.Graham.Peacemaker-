// --- 1. Basic BFS with a Binary Tree (for understanding the core concept) ---
class TreeNode {
  constructor(value) {
    this.value = value;
    this.left = null;
    this.right = null;
  }
}

function basicBFS(root) {
  if (!root) {
    return [];
  }

  const queue = [root];
  const result = [];

  while (queue.length > 0) {
    const node = queue.shift();
    result.push(node.value);

    if (node.left) {
      queue.push(node.left);
    }
    if (node.right) {
      queue.push(node.right);
    }
  }
  return result;
}

// Example Usage:
const root = new TreeNode(1);
root.left = new TreeNode(2);
root.right = new TreeNode(3);
root.left.left = new TreeNode(4);
root.left.right = new TreeNode(5);
root.right.left = new TreeNode(6);
root.right.right = new TreeNode(7);

console.log("1. Basic BFS:", basicBFS(root)); // Output: [1, 2, 3, 4, 5, 6, 7]

// --- 2. BFS for a File System (Directories and Files) ---
class FileNode {
  constructor(name, type) {
    this.name = name;
    this.type = type; // 'file' or 'directory'
    this.children = [];
  }
}

function fileSystemBFS(root) {
  if (!root) {
    return [];
  }

  const queue = [root];
  const result = [];

  while (queue.length > 0) {
    const node = queue.shift();
    result.push(`${node.name} (${node.type})`);

    if (node.type === 'directory') {
      for (const child of node.children) {
        queue.push(child);
      }
    }
  }
  return result;
}

// Example Usage:
const fileSystemRoot = new FileNode('root', 'directory');
const documents = new FileNode('documents', 'directory');
const pictures = new FileNode('pictures', 'directory');
const dataTxt = new FileNode('data.txt', 'file');
const reportPdf = new FileNode('report.pdf', 'file');
const image1Jpg = new FileNode('image1.jpg', 'file');
const image2Png = new FileNode('image2.png', 'file');

fileSystemRoot.children = [documents, pictures, dataTxt];
documents.children = [reportPdf];
pictures.children = [image1Jpg, image2Png];

console.log("2. File System BFS:", fileSystemBFS(fileSystemRoot));
// Output:
// [
//   'root (directory)',
//   'documents (directory)',
//   'pictures (directory)',
//   'data.txt (file)',
//   'report.pdf (file)',
//   'image1.jpg (file)',
//   'image2.png (file)'
// ]

// --- 3. BFS for a Social Network (Finding Friends of Friends) ---
class UserNode {
  constructor(name) {
    this.name = name;
    this.friends = [];
  }
}

function socialNetworkBFS(startUser, depthLimit = 2) {
  if (!startUser) {
    return [];
  }

  const queue = [{ user: startUser, depth: 0 }];
  const visited = new Set();
  const result = [];

  visited.add(startUser);

  while (queue.length > 0) {
    const { user, depth } = queue.shift();

    if (depth <= depthLimit) {
      result.push(`${user.name} (Depth: ${depth})`); // Include depth in result
    }

    if (depth < depthLimit) { // Only add friends if within depth limit
        for (const friend of user.friends) {
          if (!visited.has(friend)) {
            visited.add(friend);
            queue.push({ user: friend, depth: depth + 1 });
          }
        }
    }
  }
  return result;
}

// Example Usage:
const alice = new UserNode('Alice');
const bob = new UserNode('Bob');
const charlie = new UserNode('Charlie');
const david = new UserNode('David');
const eve = new UserNode('Eve');

alice.friends = [bob, charlie];
bob.friends = [alice, david];
charlie.friends = [alice, eve];
david.friends = [bob];
eve.friends = [charlie];

console.log("3. Social Network BFS (Friends of Friends):", socialNetworkBFS(alice, 2));
// Output:
// [
//   'Alice (Depth: 0)',
//   'Bob (Depth: 1)',
//   'Charlie (Depth: 1)',
//   'David (Depth: 2)',
//   'Eve (Depth: 2)'
// ]

// --- 4. BFS for Web Crawling (Exploring Linked Pages) ---
class PageNode {
  constructor(url) {
    this.url = url;
    this.links = []; // URLs of linked pages
    this.visited = false;
  }
}

function webCrawlBFS(startUrl, maxPages = 10) {
    const startPage = new PageNode(startUrl);
    const queue = [startPage];
    const visitedUrls = new Set();
    const result = [];
    let pagesCrawled = 0;

    visitedUrls.add(startUrl);

    while (queue.length > 0 && pagesCrawled < maxPages) {
        const currentPage = queue.shift();
        currentPage.visited = true;
        result.push(currentPage.url);
        pagesCrawled++;

        // Simulate fetching links (replace with actual fetching logic)
        const fetchedLinks = simulateLinks(currentPage.url); //  Simulate link fetching
        currentPage.links = fetchedLinks;

        for (const link of currentPage.links) {
            if (!visitedUrls.has(link)) {
                visitedUrls.add(link);
                const newPage = new PageNode(link); //create a new pageNode for each link
                queue.push(newPage);
            }
        }
    }
    return result;
}

// Simulate fetching links for a given URL (replace with actual fetching)
function simulateLinks(url) {
  const linkMap = {
    'https://www.example.com': ['https://www.example.com/about', 'https://www.example.com/services'],
    'https://www.example.com/about': ['https://www.example.com/contact'],
    'https://www.example.com/services': ['https://www.example.com/about', 'https://www.example.com/products'],
    'https://www.example.com/contact': [],
    'https://www.example.com/products': []
  };
  return linkMap[url] || [];
}

// Example Usage:
const startUrl = 'https://www.example.com';
console.log("4. Web Crawling BFS:", webCrawlBFS(startUrl, 5));
// Output (simulated):
// [
//   'https://www.example.com',
//   'https://www.example.com/about',
//   'https://www.example.com/services',
//   'https://www.example.com/contact'
//   'https://www.example.com/products'
// ]

// --- 5. BFS for Pathfinding in a Game Map ---
class MapNode {
  constructor(x, y, type = 'O') { // 'O' for open, 'W' for wall, 'S' for start, 'G' for goal
    this.x = x;
    this.y = y;
    this.type = type;
    this.visited = false;
    this.parent = null; // For reconstructing the path
  }

  toString() {
    return `(${this.x}, ${this.y}, ${this.type})`;
  }
}

function gameMapBFS(map, start, goal) {
  const rows = map.length;
  const cols = map[0].length;
  const queue = [start];
  start.visited = true;

  while (queue.length > 0) {
    const current = queue.shift();

    if (current === goal) {
      return reconstructPath(current); // Return the path
    }

    const neighbors = getNeighbors(map, current.x, current.y, rows, cols);
    for (const neighbor of neighbors) {
      if (!neighbor.visited && neighbor.type !== 'W') {
        neighbor.visited = true;
        neighbor.parent = current; // Track where we came from
        queue.push(neighbor);
      }
    }
  }
  return null; // No path found
}

function getNeighbors(map, x, y, rows, cols) {
  const neighbors = [];
  const directions = [
    [0, 1],
    [1, 0],
    [0, -1],
    [-1, 0],
  ]; // Right, Down, Left, Up

  for (const [dx, dy] of directions) {
    const newX = x + dx;
    const newY = y + dy;

    if (newX >= 0 && newX < rows && newY >= 0 && newY < cols) {
      neighbors.push(map[newX][newY]);
    }
  }
  return neighbors;
}

function reconstructPath(node) {
  const path = [];
  let current = node;
  while (current) {
    path.unshift(current.toString()); // Add to the beginning
    current = current.parent;
  }
  return path;
}

// Example Usage:
const gameMap = [
  [new MapNode(0, 0, 'S'), new MapNode(0, 1, 'O'), new MapNode(0, 2, 'O'), new MapNode(0, 3, 'O'), new MapNode(0, 4, 'O')],
  [new MapNode(1, 0, 'O'), new MapNode(1, 1, 'W'), new MapNode(1, 2, 'O'), new MapNode(1, 3, 'W'), new MapNode(1, 4, 'O')],
  [new MapNode(2, 0, 'O'), new MapNode(2, 1, 'W'), new MapNode(2, 2, 'O'), new MapNode(2, 3, 'W'), new MapNode(2, 4, 'O')],
  [new MapNode(3, 0, 'O'), new MapNode(3, 1, 'O'), new MapNode(3, 2, 'O'), new MapNode(3, 3, 'O'), new MapNode(3, 4, 'G')],
];

const startNode = gameMap[0][0];
const goalNode = gameMap[3][4];

console.log("5. Game Map BFS (Pathfinding):", gameMapBFS(gameMap, startNode, goalNode));
// Output:
// [
//   '(0, 0, S)',
//   '(1, 0, O)',
//   '(2, 0, O)',
//   '(3, 0, O)',
//   '(3, 1, O)',
//   '(3, 2, O)',
//   '(3, 3, O)',
//   '(3, 4, G)'
// ]
