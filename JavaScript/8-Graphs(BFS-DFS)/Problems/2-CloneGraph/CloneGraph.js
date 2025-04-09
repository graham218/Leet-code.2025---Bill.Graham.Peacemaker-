// Definition for a Node.
function Node(val, neighbors) {
    this.val = val === undefined ? 0 : val;
    this.neighbors = neighbors === undefined ? [] : neighbors;
}

// Helper function to visualize the graph (for testing purposes)
function visualizeGraph(node, visited = new Set()) {
    if (!node) return "null";
    if (visited.has(node)) return; // Prevent infinite recursion for cyclic graphs
    visited.add(node);

    let result = `${node.val} -> [`;
    for (let neighbor of node.neighbors) {
        result += neighbor.val + ", ";
    }
    result = result.slice(0, -2) + "]"; // Remove the last ", " and add "]"
    return result;
}

// Create a sample graph (for testing)
const createSampleGraph = () => {
    const node1 = new Node(1);
    const node2 = new Node(2);
    const node3 = new Node(3);
    const node4 = new Node(4);

    node1.neighbors = [node2, node4];
    node2.neighbors = [node1, node3];
    node3.neighbors = [node2, node4];
    node4.neighbors = [node1, node3];

    return node1;
};

/**
 * Clones an undirected graph.
 *
 * @param {Node} node The starting node of the graph to clone.
 * @return {Node} A deep copy of the input graph.
 */

// Approach 1: Depth-First Search (Recursive)
const cloneGraphDFS = (node, visited = new Map()) => {
    if (!node) return null;

    if (visited.has(node)) {
        return visited.get(node);
    }

    const clonedNode = new Node(node.val);
    visited.set(node, clonedNode);

    for (const neighbor of node.neighbors) {
        clonedNode.neighbors.push(cloneGraphDFS(neighbor, visited));
    }

    return clonedNode;
};

// Approach 2: Depth-First Search (Iterative)
const cloneGraphDFSIterative = (node) => {
    if (!node) return null;

    const visited = new Map();
    const stack = [node];
    const clonedNodeMap = new Map(); // Store original to cloned node mapping

    // Create the initial clone node
    const clonedStartNode = new Node(node.val);
    visited.set(node, clonedStartNode);
    clonedNodeMap.set(node, clonedStartNode);


    while (stack.length > 0) {
        const current = stack.pop();
        const clonedCurrent = visited.get(current);

        for (const neighbor of current.neighbors) {
            if (!visited.has(neighbor)) {
                const clonedNeighbor = new Node(neighbor.val);
                visited.set(neighbor, clonedNeighbor);
                clonedNodeMap.set(neighbor, clonedNeighbor); //map the new node
                clonedCurrent.neighbors.push(clonedNeighbor);
                stack.push(neighbor);
            } else {
                clonedCurrent.neighbors.push(visited.get(neighbor));
            }
        }
    }
    return clonedStartNode;
};


// Approach 3: Breadth-First Search
const cloneGraphBFS = (node) => {
    if (!node) return null;

    const visited = new Map();
    const queue = [node];
    const clonedNodeMap = new Map();

    const clonedStartNode = new Node(node.val);
    visited.set(node, clonedStartNode);
    clonedNodeMap.set(node, clonedStartNode);


    while (queue.length > 0) {
        const current = queue.shift();
        const clonedCurrent = visited.get(current);

        for (const neighbor of current.neighbors) {
            if (!visited.has(neighbor)) {
                const clonedNeighbor = new Node(neighbor.val);
                visited.set(neighbor, clonedNeighbor);
                clonedNodeMap.set(neighbor, clonedNeighbor);
                clonedCurrent.neighbors.push(clonedNeighbor);
                queue.push(neighbor);
            } else {
                clonedCurrent.neighbors.push(visited.get(neighbor));
            }
        }
    }
    return clonedStartNode;
};

// Approach 4: Using a Map (similar to DFS iterative, but more concise)
const cloneGraphMap = (node) => {
    if (!node) return null;

    const map = new Map();
    const q = [node];

    map.set(node, new Node(node.val));

    while (q.length) {
        const u = q.shift();
        const clonedU = map.get(u);

        for (const v of u.neighbors) {
            if (!map.has(v)) {
                map.set(v, new Node(v.val));
                q.push(v);
            }
            const clonedV = map.get(v);
            clonedU.neighbors.push(clonedV);
        }
    }
    return map.get(node);
};

// Approach 5: Recursive with Memoization (optimized DFS)
const cloneGraphMemo = (node) => {
    const memo = new Map();

    const clone = (n) => {
        if (!n) return null;
        if (memo.has(n)) return memo.get(n);

        const cloned = new Node(n.val);
        memo.set(n, cloned);

        for (const neighbor of n.neighbors) {
            cloned.neighbors.push(clone(neighbor));
        }
        return cloned;
    };

    return clone(node);
};



// Test the functions
const originalGraph = createSampleGraph();

console.log("Original Graph:");
console.log(visualizeGraph(originalGraph));

const clonedGraphDFSResult = cloneGraphDFS(originalGraph);
console.log("Cloned Graph (DFS Recursive):");
console.log(visualizeGraph(clonedGraphDFSResult));

const clonedGraphDFSIterativeResult = cloneGraphDFSIterative(originalGraph);
console.log("Cloned Graph (DFS Iterative):");
console.log(visualizeGraph(clonedGraphDFSIterativeResult));

const clonedGraphBFSResult = cloneGraphBFS(originalGraph);
console.log("Cloned Graph (BFS):");
console.log(visualizeGraph(clonedGraphBFSResult));

const clonedGraphMapResult = cloneGraphMap(originalGraph);
console.log("Cloned Graph (Map):");
console.log(visualizeGraph(clonedGraphMapResult));

const clonedGraphMemoResult = cloneGraphMemo(originalGraph);
console.log("Cloned Graph (Memoization):");
console.log(visualizeGraph(clonedGraphMemoResult));
