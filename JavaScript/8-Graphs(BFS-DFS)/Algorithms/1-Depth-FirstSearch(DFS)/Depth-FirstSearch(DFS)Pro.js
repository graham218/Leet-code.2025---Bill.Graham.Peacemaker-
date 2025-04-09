// Depth-First Search (DFS) in JavaScript - 5 Approaches

// 1. Basic DFS Traversal (Graph Representation with Adjacency List)
//    - Real-world application: Finding connected components in a social network.

function dfsBasic(graph, startNode, visited = new Set()) {
  console.log("DFS Basic - Starting at node:", startNode);
  visited.add(startNode);
  console.log("DFS Basic - Visited node:", startNode);

  for (const neighbor of graph[startNode] || []) {
    if (!visited.has(neighbor)) {
      dfsBasic(graph, neighbor, visited);
    }
  }
}

const graphBasic = {
  'A': ['B', 'C'],
  'B': ['D', 'E'],
  'C': ['F'],
  'D': [],
  'E': ['F'],
  'F': []
};

console.log("1. Basic DFS Traversal");
dfsBasic(graphBasic, 'A');
console.log("------------------------------------------------------");

// 2. DFS to Find a Path (Path Existence)
//    - Real-world application:  Checking if a route exists between two locations in a navigation system.
function dfsFindPath(graph, startNode, endNode, visited = new Set()) {
    console.log(`DFS Path - Visiting node: ${startNode}, looking for ${endNode}`);
    if (startNode === endNode) {
        console.log(`DFS Path - Found path to: ${endNode}`);
        return true;
    }
    visited.add(startNode);

    for (const neighbor of graph[startNode] || []) {
        if (!visited.has(neighbor)) {
            if (dfsFindPath(graph, neighbor, endNode, visited)) {
                return true; // Path found!  Propagate the 'true' back up the call stack.
            }
        }
    }
    console.log(`DFS Path - No path from ${startNode} to ${endNode}`);
    return false; // No path found from this node
}

const graphPath = {
    'A': ['B', 'C'],
    'B': ['D', 'E'],
    'C': ['F'],
    'D': ['G'],
    'E': ['F'],
    'F': [],
    'G': []
};

console.log("2. DFS to Find a Path");
console.log("Path from A to F:", dfsFindPath(graphPath, 'A', 'F')); // true
console.log("Path from A to G:", dfsFindPath(graphPath, 'A', 'G'));
console.log("Path from C to B:", dfsFindPath(graphPath, 'C', 'B'));  //false
console.log("------------------------------------------------------");

// 3. DFS for Topological Sort (Directed Acyclic Graph)
//    - Real-world application: Task scheduling or dependency resolution in a build system.
function dfsTopologicalSort(graph, startNode, visited = new Set(), result = []) {
  console.log("DFS Topological - Visiting:", startNode);
  visited.add(startNode);

  for (const neighbor of graph[startNode] || []) {
    if (!visited.has(neighbor)) {
      dfsTopologicalSort(graph, neighbor, visited, result);
    }
  }
  result.unshift(startNode); // Add to the *beginning* of the result
  console.log("DFS Topological - Adding to result:", startNode, "Result:", result);
  return result;
}

function topologicalSort(graph) {
    const visited = new Set();
    const result = [];
    for (const node in graph) {
        if (!visited.has(node)) {
            dfsTopologicalSort(graph, node, visited, result);
        }
    }
    return result;
}
const graphTopological = {
  'A': ['C'],
  'B': ['C', 'D'],
  'C': ['E'],
  'D': ['F'],
  'E': ['F'],
  'F': []
};

console.log("3. DFS for Topological Sort");
console.log("Topological Sort:", topologicalSort(graphTopological));
console.log("------------------------------------------------------");

// 4. DFS to Detect Cycles in a Directed Graph
//     - Real-world application: Detecting circular dependencies in software projects.
function dfsCycleDetection(graph, startNode, visited = new Set(), recursionStack = new Set()) {
    console.log(`DFS Cycle - Visiting: ${startNode}, Visited: ${[...visited]}, Recursion Stack: ${[...recursionStack]}`);
    visited.add(startNode);
    recursionStack.add(startNode);

    for (const neighbor of graph[startNode] || []) {
        if (recursionStack.has(neighbor)) {
            console.log(`DFS Cycle - Cycle detected at: ${neighbor}`);
            return true; // Cycle detected!
        }
        if (!visited.has(neighbor)) {
            if (dfsCycleDetection(graph, neighbor, visited, recursionStack)) {
                return true; // Cycle detected in recursive call
            }
        }
    }

    recursionStack.delete(startNode); // Remove from recursion stack when finished
    console.log(`DFS Cycle - Finished with: ${startNode}, Recursion Stack: ${[...recursionStack]}`);
    return false; // No cycle found
}

function detectCycle(graph) {
    const visited = new Set();
    for (const node in graph) {
        if (!visited.has(node)) {
            if (dfsCycleDetection(graph, node, visited, new Set())) {
                return true; // Cycle found
            }
        }
    }
    return false; // No cycles
}

const graphCycle1 = {
    'A': ['B', 'C'],
    'B': ['C', 'D'],
    'C': ['D'],
    'D': ['A']  // Cycle: D -> A -> B -> C -> D
};

const graphCycle2 = {
    'A': ['B', 'C'],
    'B': ['D', 'E'],
    'C': ['F'],
    'D': [],
    'E': ['F'],
    'F': []
};

console.log("4. DFS to Detect Cycles in a Directed Graph");
console.log("Cycle in graphCycle1:", detectCycle(graphCycle1)); // true
console.log("Cycle in graphCycle2:", detectCycle(graphCycle2)); // false
console.log("------------------------------------------------------");

// 5. DFS for Maze Solving
//    - Real-world application: Pathfinding in games or robotics.

function dfsMazeSolver(maze, start, end, path = [], visited = new Set()) {
  const rows = maze.length;
  const cols = maze[0].length;

  function isValid(r, c) {
    return r >= 0 && r < rows && c >= 0 && c < cols && maze[r][c] === 0; // 0 is path
  }

  function toKey(r, c) {
      return `${r},${c}`;
  }
  console.log(`DFS Maze - Visiting: ${start[0]},${start[1]}  End: ${end[0]},${end[1]}`);
  if (start[0] === end[0] && start[1] === end[1]) {
    path.push(start);
    console.log("DFS Maze - Found Path:", path);
    return true;
  }

  const [r, c] = start;
  visited.add(toKey(r,c));
  path.push(start);

  const directions = [[0, 1], [1, 0], [0, -1], [-1, 0]]; // Right, Down, Left, Up

  for (const [dr, dc] of directions) {
    const newR = r + dr;
    const newC = c + dc;

    if (isValid(newR, newC) && !visited.has(toKey(newR,newC))) {
      if (dfsMazeSolver(maze, [newR, newC], end, path, visited)) {
        return true;
      }
    }
  }

  path.pop(); // Backtrack
  console.log(`DFS Maze - Backtracking from: ${r},${c}`);
  return false;
}

const maze = [
  [0, 1, 0, 0, 0],
  [0, 1, 0, 1, 0],
  [0, 0, 0, 0, 0],
  [0, 1, 1, 1, 1],
  [0, 0, 0, 0, 0]
]; // 0: path, 1: wall

const start = [0, 0];
const end = [4, 4];

console.log("5. DFS for Maze Solving");
const pathMaze = [];
dfsMazeSolver(maze, start, end, pathMaze);
if (pathMaze.length > 0){
  console.log("Maze Solved! Path:", pathMaze);
}
else{
  console.log("No path found");
}

console.log("------------------------------------------------------");
