// Breadth-First Search (BFS) - 5 Real-World Implementations

// 1. Social Network Analysis - Finding connections up to a degree of separation
//    (e.g., "Find friends of friends")
function socialNetworkBFS(graph, startNode, degrees) {
  const visited = new Set();
  const queue = [{ node: startNode, distance: 0 }];
  const results = [];

  while (queue.length > 0) {
    const { node, distance } = queue.shift();

    if (visited.has(node)) continue;
    visited.add(node);

    if (distance <= degrees) {
      results.push(node);
    }

    if (distance < degrees) {
      for (const neighbor of graph[node] || []) { // Handle undefined neighbors
        queue.push({ node: neighbor, distance: distance + 1 });
      }
    }
  }
  return results;
}

// 2. Web Crawler - Exploring links on a website
function webCrawlerBFS(startUrl, maxPages) {
  const visited = new Set();
  const queue = [startUrl];
  const pagesCrawled = [];
  let pageCount = 0;

  while (queue.length > 0 && pageCount < maxPages) {
    const url = queue.shift();

    if (visited.has(url)) continue;
    visited.add(url);
    pagesCrawled.push(url);
    pageCount++;

    // Simulate fetching links (replace with actual fetch)
    const links = simulateFetchLinks(url); //  Simulate fetching
    if (links) {
        for (const link of links) {
          if (!visited.has(link)) {
            queue.push(link);
          }
        }
    }
  }
  return pagesCrawled;
}

function simulateFetchLinks(url) {
    // In a real crawler, you'd fetch the HTML and extract links.
    // Here, we just return some dummy links based on the URL.
    const dummyLinks = {
        "https://www.example.com": ["https://www.example.com/about", "https://www.example.com/services", "https://www.example.com/contact"],
        "https://www.example.com/about": ["https://www.example.com", "https://www.example.com/team"],
        "https://www.example.com/services": ["https://www.example.com", "https://www.example.com/pricing"],
        "https://www.example.com/contact": ["https://www.example.com"],
        "https://www.example.com/team": ["https://www.example.com/about"],
        "https://www.example.com/pricing": ["https://www.example.com/services"],
        "https://www.wikipedia.org": [
            "https://en.wikipedia.org/wiki/Breadth-first_search",
            "https://en.wikipedia.org/wiki/Depth-first_search",
            "https://en.wikipedia.org/wiki/Graph_theory"
        ],
        "https://en.wikipedia.org/wiki/Breadth-first_search": [
            "https://en.wikipedia.org/wiki/Graph_theory",
            "https://en.wikipedia.org/wiki/Search_algorithm"
        ],
        "https://en.wikipedia.org/wiki/Depth-first_search": [
            "https://en.wikipedia.org/wiki/Graph_theory",
            "https://en.wikipedia.org/wiki/Search_algorithm"
        ],
        "https://en.wikipedia.org/wiki/Graph_theory": [
            "https://en.wikipedia.org/wiki/Graph_(discrete_mathematics)",
            "https://en.wikipedia.org/wiki/Mathematics"
        ]
    };

    return dummyLinks[url] || []; // Return [] for URLs not in dummyLinks
}


// 3. Routing in a Navigation System (Shortest path with equal weights)
function navigationBFS(graph, start, destination) {
  const visited = new Set();
  const queue = [{ node: start, path: [start] }];

  while (queue.length > 0) {
    const { node, path } = queue.shift();

    if (node === destination) {
      return path;
    }

    if (visited.has(node)) continue;
    visited.add(node);

    for (const neighbor of graph[node] || []) { // Handle undefined neighbors
      const newPath = [...path, neighbor];
      queue.push({ node: neighbor, path: newPath });
    }
  }
  return null; // No path found
}

// 4. Game AI (Pathfinding for a character in a simple maze)
function gameAIPathfinding(maze, start, end) {
    const rows = maze.length;
    const cols = maze[0].length;
    const visited = new Array(rows).fill(null).map(() => new Array(cols).fill(false));
    const queue = [{ row: start[0], col: start[1], path: [start] }];

    const isValid = (r, c) => r >= 0 && r < rows && c >= 0 && c < cols && maze[r][c] === 0; // 0: path, 1: wall
    const directions = [[0, 1], [1, 0], [0, -1], [-1, 0]]; // Right, Down, Left, Up

    while (queue.length > 0) {
        const { row, col, path } = queue.shift();

        if (row === end[0] && col === end[1]) {
            return path;
        }

        if (visited[row][col]) continue;
        visited[row][col] = true;

        for (const [dr, dc] of directions) {
            const newRow = row + dr;
            const newCol = col + dc;

            if (isValid(newRow, newCol)) {
                const newPath = [...path, [newRow, newCol]];
                queue.push({ row: newRow, col: newCol, path: newPath });
            }
        }
    }
    return null; // No path found
}

// 5. Network Broadcasting (Sending a message to all nodes in a network)
function networkBroadcastBFS(network, startNode) {
  const visited = new Set();
  const queue = [startNode];
  const messageLog = {}; // Store nodes and the order they received the message

  let messageOrder = 1; // Keep track of the order of message delivery

  while (queue.length > 0) {
    const node = queue.shift();

    if (visited.has(node)) continue;
    visited.add(node);
    messageLog[node] = messageOrder++; // Store the order

    for (const neighbor of network[node] || []) { // Handle undefined neighbors
      queue.push(neighbor);
    }
  }
  return { visitedNodes: Array.from(visited), messageLog };
}



// --- Example Usage ---
console.log("--- 1. Social Network Analysis ---");
const socialNetworkGraph = {
  'A': ['B', 'C'],
  'B': ['A', 'D', 'E'],
  'C': ['A', 'F'],
  'D': ['B'],
  'E': ['B', 'F'],
  'F': ['C', 'E', 'G'],
  'G': ['F']
};
console.log("Friends of A up to 2 degrees:", socialNetworkBFS(socialNetworkGraph, 'A', 2)); // Output: ['A', 'B', 'C', 'D', 'E', 'F']
console.log("Friends of A up to 1 degree:", socialNetworkBFS(socialNetworkGraph, 'A', 1));

console.log("\n--- 2. Web Crawler ---");
const crawledPages = webCrawlerBFS("https://www.example.com", 10);
console.log("Crawled pages:", crawledPages);

console.log("\n--- 3. Navigation System Routing ---");
const navigationGraph = {
  'A': ['B', 'C'],
  'B': ['A', 'D', 'E'],
  'C': ['A', 'F'],
  'D': ['B'],
  'E': ['B', 'F'],
  'F': ['C', 'E', 'G'],
  'G': ['F']
};
console.log("Shortest path from A to G:", navigationBFS(navigationGraph, 'A', 'G')); // Output: ['A', 'C', 'F', 'G']
console.log("Shortest path from A to D:", navigationBFS(navigationGraph, 'A', 'D'));

console.log("\n--- 4. Game AI Pathfinding ---");
const maze = [
  [0, 1, 0, 0, 0],
  [0, 1, 0, 1, 0],
  [0, 0, 0, 0, 0],
  [0, 1, 1, 1, 1],
  [0, 0, 0, 0, 0]
];
const start = [0, 0];
const end = [4, 4];
const path = gameAIPathfinding(maze, start, end);
console.log("Path from start to end:", path);

const maze2 = [
    [0, 0, 0, 0, 0, 0],
    [0, 1, 1, 1, 1, 0],
    [0, 0, 0, 0, 0, 0],
    [1, 1, 0, 1, 1, 1],
    [0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0]
];
const start2 = [0, 0];
const end2 = [5, 5];
const path2 = gameAIPathfinding(maze2, start2, end2);
console.log("Path from start2 to end2", path2);


console.log("\n--- 5. Network Broadcasting ---");
const networkGraph = {
  'A': ['B', 'C'],
  'B': ['A', 'D', 'E'],
  'C': ['A', 'F'],
  'D': ['B'],
  'E': ['B', 'F'],
  'F': ['C', 'E', 'G'],
  'G': ['F', 'H'],
  'H': ['G']
};
const broadcastResult = networkBroadcastBFS(networkGraph, 'A');
console.log("Visited nodes:", broadcastResult.visitedNodes);
console.log("Message log (node: order):", broadcastResult.messageLog);
