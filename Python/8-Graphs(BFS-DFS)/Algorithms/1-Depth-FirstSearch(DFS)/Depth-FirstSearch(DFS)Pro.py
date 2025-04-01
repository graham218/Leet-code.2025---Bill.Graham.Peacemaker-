"""
Depth-First Search (DFS) Implementation with Six Real-World Applications

DFS is a graph traversal algorithm that explores as far as possible along each branch before backtracking.

Here are six different approaches with real-world project implementations:

1.  **Web Crawler:**
    * **Concept:** DFS can be used to traverse the links of a website. Starting from a root URL, the crawler visits linked pages recursively.
    * **Real-World Application:** Search engine indexing, website link analysis.

2.  **Maze Solving:**
    * **Concept:** Represent a maze as a graph where each cell is a node, and paths between cells are edges. DFS can find a path from the start to the end.
    * **Real-World Application:** Robotics navigation, game development (pathfinding).

3.  **Topological Sort:**
    * **Concept:** For a directed acyclic graph (DAG), DFS can produce a topological ordering of nodes.  A topological sort is an ordering of nodes such that for every directed edge from node A to node B, node A appears before node B in the ordering.
    * **Real-World Application:** Task scheduling, dependency resolution in software projects.

4.  **Cycle Detection:**
    * **Concept:** DFS can detect cycles in a graph. If a visited node is encountered again along the current path, there's a cycle.
    * **Real-World Application:** Detecting circular dependencies in data, detecting loops in linked lists.

5.  **Connected Components:**
    * **Concept:** DFS can identify groups of connected nodes in an undirected graph.  Each group of nodes is a connected component.
    * **Real-World Application:** Network analysis, clustering, image segmentation.

6.  **Sudoku Solver:**
    * **Concept:** DFS can be used to explore possible solutions to a Sudoku puzzle.  The grid can be thought of as a graph, where each empty cell is a node, and possible values are the edges.
    * **Real-World Application:** Artificial Intelligence, Constraint Satisfaction Problems.
"""

from collections import defaultdict
import time

class Graph:
    """
    A graph data structure implemented using an adjacency list.
    """
    def __init__(self):
        """
        Initializes an empty graph.
        """
        self.graph = defaultdict(list)

    def add_edge(self, u, v):
        """
        Adds an undirected edge between nodes u and v.
        """
        self.graph[u].append(v)
        self.graph[v].append(u)  # For undirected graph

    def add_directed_edge(self, u, v):
        """
        Adds a directed edge from node u to node v.
        """
        self.graph[u].append(v)

    def get_nodes(self):
        """
        Returns all nodes in the graph
        """
        return list(self.graph.keys())

    def get_neighbors(self, node):
        """
        Returns all neighbors of a given node.
        """
        return self.graph[node]

    def display_graph(self):
        """
        Displays the graph as an adjacency list.
        """
        for node in self.graph:
            print(f"{node}: {self.graph[node]}")

    def dfs(self, start_node, visited=None):
        """
        Performs Depth-First Search (DFS) starting from a given node.

        Args:
            start_node: The node to start the DFS traversal from.
            visited: A set to keep track of visited nodes (optional).

        Returns:
            A list of nodes visited in DFS order.
        """
        if visited is None:
            visited = set()
        visited.add(start_node)
        print(f"Visiting node: {start_node}")  # Track the order of node visits.
        neighbors = self.graph[start_node]
        for neighbor in neighbors:
            if neighbor not in visited:
                self.dfs(neighbor, visited)
        return list(visited)

# 1. Web Crawler
def web_crawler(start_url, max_depth=3):
    """
    Simulates a basic web crawler using DFS.

    Args:
        start_url: The starting URL for the crawl.
        max_depth: The maximum depth to crawl.

    Returns:
        A set of visited URLs.
    """
    visited_urls = set()
    stack = [(start_url, 0)]  # Use a stack for DFS, store (url, depth)

    print(f"\n[Web Crawler] Starting from: {start_url}, Max Depth: {max_depth}")

    while stack:
        current_url, depth = stack.pop()

        if current_url in visited_urls:
            continue
        visited_urls.add(current_url)
        print(f"Crawling: {current_url} (Depth: {depth})")

        if depth >= max_depth:
            continue  # Stop crawling at max depth

        # Simulate fetching links from the current URL
        links = get_links_from_url(current_url)  #  Replace with actual link extraction

        for link in links:
            if link not in visited_urls:
                stack.append((link, depth + 1))  # Push new links onto the stack

    return visited_urls

def get_links_from_url(url):
    """
    Simulates fetching links from a URL (replace with actual implementation).

    Args:
        url: The URL to fetch links from.

    Returns:
        A list of dummy URLs.
    """
    # In a real web crawler, you would use a library like requests and
    # BeautifulSoup to fetch the HTML content and extract links.
    # Here, we just return some dummy links for demonstration.
    if url == "https://www.example.com":
        return ["https://www.example.com/page1", "https://www.example.com/page2", "https://www.example.com/page3"]
    elif url == "https://www.example.com/page1":
        return ["https://www.example.com/page4", "https://www.example.com/page5"]
    elif url == "https://www.example.com/page2":
        return ["https://www.example.com/page6"]
    else:
        return []  # No links for other dummy URLs

# 2. Maze Solving
def solve_maze_dfs(maze, start, end):
    """
    Solves a maze using DFS.

    Args:
        maze: A 2D list representing the maze. 0 is path, 1 is wall.
        start: The starting coordinates (row, col).
        end: The ending coordinates (row, col).

    Returns:
        A list of coordinates representing the path from start to end, or None if no path exists.
    """
    rows = len(maze)
    cols = len(maze[0])
    path = []
    visited = set()

    def is_valid(r, c):
        """
        Checks if a cell is within the maze bounds and is a valid path.
        """
        return 0 <= r < rows and 0 <= c < cols and maze[r][c] == 0

    def dfs(r, c):
        """
        DFS function to explore the maze.
        """
        if (r, c) == end:
            path.append((r, c))
            return True

        if not is_valid(r, c) or (r, c) in visited:
            return False

        visited.add((r, c))
        path.append((r, c))

        # Explore adjacent cells (up, down, left, right)
        if dfs(r - 1, c) or \
                dfs(r + 1, c) or \
                dfs(r, c - 1) or \
                dfs(r, c + 1):
            return True

        path.pop()  # Backtrack: remove the current cell from the path
        return False

    if dfs(start[0], start[1]):
        return path
    else:
        return None

# 3. Topological Sort
def topological_sort(graph):
    """
    Performs topological sort on a directed acyclic graph (DAG) using DFS.

    Args:
        graph: A dictionary representing the graph as an adjacency list.

    Returns:
        A list of nodes in topological order, or None if the graph has a cycle.
    """
    visited = set()
    stack = []

    def dfs(node):
        """
        DFS function to traverse the graph.
        """
        if node in visited:
            return  # Already visited

        visited.add(node)
        for neighbor in graph.get(node, []):
            dfs(neighbor)
        stack.insert(0, node)  # Prepend the node to the result list

    for node in graph:
        dfs(node)

    # Check for cycles (Improved):
    if len(visited) != len(graph):
        return None # Cycle exists.  Not a DAG.

    return stack

# 4. Cycle Detection
def detect_cycle(graph):
    """
    Detects cycles in a directed graph using DFS.

    Args:
        graph: A dictionary representing the graph as an adjacency list.

    Returns:
        True if the graph contains a cycle, False otherwise.
    """
    visited = set()
    recursion_stack = set()  # Keep track of nodes in the current recursion stack

    def dfs(node):
        """
        DFS function to traverse the graph and detect cycles.
        """
        visited.add(node)
        recursion_stack.add(node)

        for neighbor in graph.get(node, []):
            if neighbor in recursion_stack:
                return True  # Cycle detected
            if neighbor not in visited:
                if dfs(neighbor):
                    return True

        recursion_stack.remove(node)  # Remove node from recursion stack after processing
        return False

    for node in graph:
        if node not in visited:
            if dfs(node):
                return True
    return False

# 5. Connected Components
def find_connected_components(graph):
    """
    Finds the connected components in an undirected graph using DFS.

    Args:
        graph: A dictionary representing the graph as an adjacency list.

    Returns:
        A list of sets, where each set represents a connected component.
    """
    visited = set()
    connected_components = []

    def dfs(node, component):
        """
        DFS function to traverse the graph and build a connected component.
        """
        visited.add(node)
        component.add(node)
        for neighbor in graph.get(node, []):
            if neighbor not in visited:
                dfs(neighbor, component)

    for node in graph:
        if node not in visited:
            component = set()
            dfs(node, component)
            connected_components.append(component)
    return connected_components

# 6. Sudoku Solver
def solve_sudoku(board):
    """
    Solves a Sudoku puzzle using DFS (backtracking).

    Args:
        board: A 9x9 2D list representing the Sudoku board.  0 represents empty cells.

    Returns:
        True if the Sudoku puzzle is solved, False otherwise.  The board is modified in place.
    """

    def find_empty_cell():
        """
        Finds the next empty cell (0) in the board.
        Returns:
            A tuple (row, col) of the empty cell's coordinates, or None if no empty cell exists.
        """
        for r in range(9):
            for c in range(9):
                if board[r][c] == 0:
                    return r, c
        return None

    def is_valid(r, c, num):
        """
        Checks if placing a number is valid in the given cell.

        Args:
            r: The row index.
            c: The column index.
            num: The number to place (1-9).

        Returns:
            True if the number is valid, False otherwise.
        """
        # Check row and column
        for i in range(9):
            if board[r][i] == num or board[i][c] == num:
                return False

        # Check 3x3 subgrid
        start_r = (r // 3) * 3
        start_c = (c // 3) * 3
        for i in range(3):
            for j in range(3):
                if board[start_r + i][start_c + j] == num:
                    return False
        return True

    def dfs():
        """
        DFS function to solve the Sudoku puzzle.
        """
        empty_cell = find_empty_cell()
        if not empty_cell:
            return True  # No empty cells left, puzzle is solved

        r, c = empty_cell
        for num in range(1, 10):
            if is_valid(r, c, num):
                board[r][c] = num
                if dfs():  # Recursively try to solve the rest of the board
                    return True
                board[r][c] = 0  # Backtrack: reset the cell if the solution doesn't work
        return False  # No valid number found for this cell

    return dfs()

def print_sudoku_board(board):
    """Prints the Sudoku board in a user-friendly format."""
    for r in range(9):
        if r % 3 == 0 and r != 0:
            print("-" * 21)  # Separator lines
        for c in range(9):
            if c % 3 == 0 and c != 0:
                print("|", end=" ")  # Separator bars
            print(board[r][c], end=" ")
        print()

if __name__ == "__main__":
    # 1. Web Crawler Example
    start_time = time.time()
    visited_urls = web_crawler("https://www.example.com", max_depth=2)
    end_time = time.time()
    print("\n[Web Crawler] Visited URLs:")
    for url in visited_urls:
        print(url)
    print(f"[Web Crawler] Time taken: {end_time - start_time:.4f} seconds")

    # 2. Maze Solving Example
    maze = [
        [0, 1, 1, 1, 1, 1, 1, 1],
        [0, 0, 0, 0, 0, 0, 0, 1],
        [1, 1, 1, 1, 1, 1, 0, 1],
        [1, 0, 0, 0, 0, 1, 0, 0],
        [1, 0, 1, 1, 0, 1, 1, 1],
        [1, 0, 0, 1, 0, 0, 0, 1],
        [1, 1, 0, 1, 1, 1, 0, 1],
        [1, 1, 0, 0, 0, 0, 0, 0],
    ]
    start = (0, 0)
    end = (7, 7)
    start_time = time.time()
    path = solve_maze_dfs(maze, start, end)
    end_time = time.time()
    print("\n[Maze Solving] Maze:")
    for row in maze:
        print(row)
    print(f"[Maze Solving] Path from {start} to {end}: {path}")
    print(f"[Maze Solving] Time taken: {end_time - start_time:.4f} seconds")

    # 3. Topological Sort Example
    graph = {
        'A': ['B', 'C'],
        'B': ['D', 'E'],
        'C': ['F'],
        'D': ['E'],
        'E': ['F'],
        'F': []
    }
    start_time = time.time()
    sorted_nodes = topological_sort(graph)
    end_time = time.time()
    print("\n[Topological Sort] Graph:")
    for node in graph:
        print(f"{node}: {graph[node]}")
    print(f"[Topological Sort] Topological ordering: {sorted_nodes}")
    print(f"[Topological Sort] Time taken: {end_time - start_time:.4f} seconds")

    # Example with a graph containing a cycle (for demonstration):
    graph_with_cycle = {
        'A': ['B'],
        'B': ['C'],
        'C': ['A']  # Cycle: C -> A
    }
    start_time = time.time()
    result_with_cycle = topological_sort(graph_with_cycle)
    end_time = time.time()
    print("\n[Topological Sort] Graph with cycle:")
    for node in graph_with_cycle:
        print(f"{node}: {graph_with_cycle[node]}")
    if result_with_cycle is None:
        print("[Topological Sort] Graph contains a cycle: Cannot perform topological sort.")
    else:
        print(f"[Topological Sort] Topological ordering: {result_with_cycle}")
    print(f"[Topological Sort] Time taken: {end_time - start_time:.4f} seconds")

    # 4. Cycle Detection Example
    graph_no_cycle = {
        'A': ['B', 'C'],
        'B': ['D', 'E'],
        'C': ['F'],
        'D': ['E'],
        'E': ['F'],
        'F': []
    }

    graph_with_cycle = {
        'A': ['B'],
        'B': ['C'],
        'C': ['A']  # Cycle: C -> A
    }
    start_time = time.time()
    has_cycle1 = detect_cycle(graph_no_cycle)
    has_cycle2 = detect_cycle(graph_with_cycle)
    end_time = time.time()
    print("\n[Cycle Detection] Graph without cycle:")
    for node in graph_no_cycle:
        print(f"{node}: {graph_no_cycle[node]}")
    print(f"[Cycle Detection] Has cycle: {has_cycle1}")  # False
    print("\n[Cycle Detection] Graph with cycle:")
    for node in graph_with_cycle:
        print(f"{node}: {graph_with_cycle[node]}")
    print(f"[Cycle Detection] Has cycle: {has_cycle2}")  # True
    print(f"[Cycle Detection] Time taken: {end_time - start_time:.4f} seconds")

    # 5. Connected Components Example
    graph = {
        0: [1, 2],
        1: [0, 2],
        2: [0, 1],
        3: [4],
        4: [3, 5],
        5: [4],
        6: [7, 8],
        7: [6, 8],
        8: [6, 7]
    }
    start_time = time.time()
    components = find_connected_components(graph)
    end_time = time.time()
    print("\n[Connected Components] Graph:")
    for node in graph:
        print(f"{node}: {graph[node]}")
    print(f"[Connected Components] Connected components: {components}")
    print(f"[Connected Components] Time taken: {end_time - start_time:.4f} seconds")

    # 6. Sudoku Solver Example
    # 0 represents empty cells
    sudoku_board = [
        [5, 3, 0, 0, 7, 0, 0, 0, 0],
        [6, 0, 0, 1, 9, 5, 0, 0, 0],
        [0, 9, 8, 0, 0, 0, 0, 6, 0],
        [8, 0, 0, 0, 6, 0, 0, 0, 3],
        [4, 0, 0, 8, 0, 3, 0, 0, 1],
        [7, 0, 0, 0, 2, 0, 0, 0, 6],
        [0, 6, 0, 0, 0, 0, 2, 8, 0],
        [0, 0, 0, 4, 1, 9, 0, 0, 5],
        [0, 0, 0, 0, 8, 0, 0, 7, 9]
    ]
    print("\n[Sudoku Solver] Initial Sudoku Board:")
    print_sudoku_board(sudoku_board)
    start_time = time.time()
    if solve_sudoku(sudoku_board):
        end_time = time.time()
        print("\n[Sudoku Solver] Solved Sudoku Board:")
        print_sudoku_board(sudoku_board)
        print(f"[Sudoku Solver] Time taken: {end_time - start_time:.4f} seconds")
    else:
        end_time = time.time()
        print("[Sudoku Solver] No solution exists.")
        print(f"[Sudoku Solver] Time taken: {end_time - start_time:.4f} seconds")
