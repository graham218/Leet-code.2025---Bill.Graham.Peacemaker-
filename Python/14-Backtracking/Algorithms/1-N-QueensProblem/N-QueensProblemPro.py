import time

class NQueens:
    """
    Solves the N-Queens problem using backtracking with various optimization techniques.
    The N-Queens problem is the challenge of placing N chess queens on an N×N chessboard
    so that no two queens threaten each other.  Thus, a solution requires that no two
    queens share the same row, column, or diagonal.
    """

    def __init__(self, n):
        """
        Initializes the N-Queens solver.

        Args:
            n (int): The size of the chessboard (N x N).
        """
        if not isinstance(n, int) or n <= 0:
            raise ValueError("N must be a positive integer.")
        self.n = n
        self.board = [-1] * n  # Representation: board[i] is the column of the queen in row i.
        self.solutions = 0
        self.execution_times = {} # Store execution times for each approach

    def is_safe(self, row, col):
        """
        Checks if placing a queen at board[row] = col is safe.

        Args:
            row (int): The row to place the queen in.
            col (int): The column to place the queen in.

        Returns:
            bool: True if the position is safe, False otherwise.
        """
        for prev_row in range(row):
            if self.board[prev_row] == col or \
                    self.board[prev_row] - col == prev_row - row or \
                    self.board[prev_row] - col == row - prev_row:
                return False
        return True

    def solve_n_queens_recursive(self, row=0):
        """
        Solves the N-Queens problem using a simple recursive backtracking approach.

        Args:
            row (int, optional): The current row to place a queen in. Defaults to 0.
        """
        if row == self.n:
            self.solutions += 1
            return

        for col in range(self.n):
            if self.is_safe(row, col):
                self.board[row] = col
                self.solve_n_queens_recursive(row + 1)
                # No need to explicitly backtrack here (reset board[row] = -1)
                # because the next iteration of the loop will overwrite it.

    def solve_n_queens_optimized(self, row=0, cols=None, diag1=None, diag2=None):
        """
        Solves the N-Queens problem using backtracking with bitwise optimization.
        This approach uses sets to track occupied columns and diagonals,
        which is generally faster than iterating through previous rows.

        Args:
            row (int, optional): The current row. Defaults to 0.
            cols (set, optional): Set of occupied columns. Defaults to None.
            diag1 (set, optional): Set of occupied main diagonals (row - col). Defaults to None.
            diag2 (set, optional): Set of occupied anti-diagonals (row + col). Defaults to None.
        """
        if cols is None:
            cols = set()
        if diag1 is None:
            diag1 = set()
        if diag2 is None:
            diag2 = set()

        if row == self.n:
            self.solutions += 1
            return

        for col in range(self.n):
            if col not in cols and row - col not in diag1 and row + col not in diag2:
                self.board[row] = col
                cols.add(col)
                diag1.add(row - col)
                diag2.add(row + col)
                self.solve_n_queens_optimized(row + 1, cols, diag1, diag2)
                cols.remove(col)
                diag1.remove(row - col)
                diag2.remove(row + col)

    def solve_n_queens_iterative(self):
        """
        Solves the N-Queens problem using an iterative approach with a stack.
        This avoids recursion and can be more memory-efficient for large N.
        """
        stack = [(0, 0, set(), set(), set())]  # (row, col, cols, diag1, diag2)
        while stack:
            row, col, cols, diag1, diag2 = stack.pop()
            if row == self.n:
                self.solutions += 1
                continue
            for c in range(col, self.n): # Start from 'col' to avoid redundant checks
                if c not in cols and row - c not in diag1 and row + c not in diag2:
                    self.board[row] = c
                    new_cols = set(cols)
                    new_diag1 = set(diag1)
                    new_diag2 = set(diag2)
                    new_cols.add(c)
                    new_diag1.add(row - c)
                    new_diag2.add(row + c)
                    stack.append((row + 1, 0, new_cols, new_diag1, new_diag2))
                # Optimization:  Don't explore other columns in the *current* row
                # if a safe one is found.  The 'continue' sends us to the next
                # iteration of the *outer* 'while' loop.
                col = self.n # Force exit of inner loop.

    def solve_n_queens_forward_checking(self, row=0, cols=None, diag1=None, diag2=None, possible_cols=None):
        """
        Solves the N-Queens problem using forward checking.  This is a more
        constrained backtracking.  Before placing a queen, we check if there are
        any valid columns available in future rows.  If not, we backtrack early.
        This can significantly reduce the search space.

        Args:
            row (int, optional): Current row. Defaults to 0.
            cols (set, optional): Occupied columns. Defaults to None.
            diag1 (set, optional): Occupied main diagonals. Defaults to None.
            diag2 (set, optional): Occupied anti-diagonals. Defaults to None.
            possible_cols (list of sets, optional): possible columns for each row.
        """
        if cols is None:
            cols = set()
        if diag1 is None:
            diag1 = set()
        if diag2 is None:
            diag2 = set()
        if possible_cols is None:
            possible_cols = [set(range(self.n)) for _ in range(self.n)]

        if row == self.n:
            self.solutions += 1
            return

        for col in list(possible_cols[row]):  # Iterate over a *copy*
            if col not in cols and row - col not in diag1 and row + col not in diag2:
                self.board[row] = col
                new_cols = set(cols)
                new_diag1 = set(diag1)
                new_diag2 = set(diag2)
                new_cols.add(col)
                new_diag1.add(row - col)
                new_diag2.add(row + col)

                # Forward checking:  Update possible columns for *future* rows
                next_possible_cols = [set(pc) for pc in possible_cols] # Copy
                for next_row in range(row + 1, self.n):
                    if col in next_possible_cols[next_row]:
                        next_possible_cols[next_row].remove(col)
                    if col - (next_row - row) in next_possible_cols[next_row]:
                        next_possible_cols[next_row].remove(col - (next_row - row))
                    if col + (next_row - row) in next_possible_cols[next_row]:
                        next_possible_cols[next_row].remove(col + (next_row - row))

                # Pruning: If any future row has no possible columns, backtrack.
                valid = True
                for next_row in range(row + 1, self.n):
                    if not next_possible_cols[next_row]:
                        valid = False
                        break
                if valid:
                    self.solve_n_queens_forward_checking(row + 1, new_cols, new_diag1, new_diag2, next_possible_cols)
                # No explicit backtracking needed, loop iteration handles it.

    def solve_n_queens_heuristic(self):
        """
        Solves the N-Queens problem using a heuristic approach (Min-Conflicts).
        This is *not* guaranteed to find *all* solutions, but it's very efficient
        for large N.  It starts with a random placement and iteratively reduces
        the number of conflicts.
        """
        import random

        # 1. Start with a random initial placement.
        for i in range(self.n):
            self.board[i] = random.randrange(self.n)

        max_iterations = 1000  # Maximum iterations to prevent infinite loops
        for _ in range(max_iterations):
            conflicts = self.count_conflicts()
            if conflicts == 0:
                self.solutions = 1 # Heuristic only finds *one* solution.
                return

            # 2. Find a queen with conflicts.
            queen_row = random.randrange(self.n)
            while self.count_conflicts_in_row(queen_row) == 0 and queen_row < self.n:
                queen_row = random.randrange(self.n) # keep looking for a conflicting row

            # 3. Move the queen to the column with the fewest conflicts.
            min_conflicts_col = -1
            min_conflicts = float('inf')
            for col in range(self.n):
                self.board[queen_row] = col
                current_conflicts = self.count_conflicts_in_row(queen_row)
                if current_conflicts < min_conflicts:
                    min_conflicts = current_conflicts
                    min_conflicts_col = col

            self.board[queen_row] = min_conflicts_col  # Move the queen
        print(f"Min-Conflicts heuristic stopped after {max_iterations} iterations.")
        print("A solution may not have been found.")

    def count_conflicts(self):
        """
        Counts the total number of conflicts on the board.
        """
        conflicts = 0
        for row in range(self.n):
            conflicts += self.count_conflicts_in_row(row)
        return conflicts

    def count_conflicts_in_row(self, row):
        """
        Counts the number of conflicts for the queen in a given row.
        """
        conflicts = 0
        for other_row in range(self.n):
            if other_row != row:
                if self.board[row] == self.board[other_row] or \
                        self.board[row] - self.board[other_row] == row - other_row or \
                        self.board[row] - self.board[other_row] == other_row - row:
                    conflicts += 1
        return conflicts

    def solve_n_queens_genetic(self):
        """
        Solves the N-Queens problem using a genetic algorithm.
        This approach treats board configurations as "chromosomes" and evolves
        them towards a solution.  Like the Min-Conflicts heuristic, this does
        not guarantee finding *all* solutions.
        """
        import random

        def create_population(size):
            """Creates an initial population of random board configurations."""
            population = []
            for _ in range(size):
                chromosome = [random.randrange(self.n) for _ in range(self.n)]
                population.append(chromosome)
            return population

        def calculate_fitness(chromosome):
            """Calculates the fitness of a chromosome (number of non-conflicts)."""
            conflicts = 0
            for i in range(self.n):
                for j in range(i + 1, self.n):
                    if chromosome[i] == chromosome[j] or \
                            chromosome[i] - chromosome[j] == i - j or \
                            chromosome[i] - chromosome[j] == j - i:
                        conflicts += 1
            return self.n * (self.n - 1) // 2 - conflicts  # Max conflicts - actual conflicts

        def selection(population, fitnesses):
            """Selects parents for crossover using roulette wheel selection."""
            total_fitness = sum(fitnesses)
            pick = random.uniform(0, total_fitness)
            current = 0
            for i, fitness in enumerate(fitnesses):
                current += fitness
                if current > pick:
                    return population[i]
            return population[-1]  # Should not happen, but added for safety

        def crossover(parent1, parent2):
            """Performs single-point crossover to create two offspring."""
            point = random.randrange(self.n)
            child1 = parent1[:point] + parent2[point:]
            child2 = parent2[:point] + parent1[point:]
            return child1, child2

        def mutate(chromosome, mutation_rate):
            """Mutates a chromosome with a given probability."""
            for i in range(self.n):
                if random.random() < mutation_rate:
                    chromosome[i] = random.randrange(self.n)
            return chromosome

        # --- Main genetic algorithm ---
        population_size = 100
        mutation_rate = 0.05
        generations = 500

        population = create_population(population_size)

        for generation in range(generations):
            fitnesses = [calculate_fitness(chromosome) for chromosome in population]
            best_fitness = max(fitnesses)
            best_chromosome = population[fitnesses.index(best_fitness)]

            if best_fitness == self.n * (self.n - 1) // 2:  # Perfect fitness (no conflicts)
                self.solutions = 1 # Genetic alg finds one solution
                self.board = best_chromosome
                return

            new_population = []
            for _ in range(population_size // 2):
                parent1 = selection(population, fitnesses)
                parent2 = selection(population, fitnesses)
                child1, child2 = crossover(parent1, parent2)
                child1 = mutate(child1, mutation_rate)
                child2 = mutate(child2, mutation_rate)
                new_population.extend([child1, child2])
            population = new_population

        print(f"Genetic algorithm stopped after {generations} generations.")
        print("A solution may not have been found.")
        # Best solution found (if any) is in self.board

    def print_board(self):
        """Prints the board configuration."""
        for row in range(self.n):
            line = ['.'] * self.n
            if self.board[row] != -1:
                line[self.board[row]] = 'Q'
            print(' '.join(line))
        print()

    def run_all_solvers(self):
        """
        Runs all N-Queens solvers and prints the results.
        """
        approaches = [
            ("Recursive Backtracking", self.solve_n_queens_recursive),
            ("Optimized Backtracking", self.solve_n_queens_optimized),
            ("Iterative Backtracking", self.solve_n_queens_iterative),
            ("Forward Checking", self.solve_n_queens_forward_checking),
            ("Min-Conflicts Heuristic", self.solve_n_queens_heuristic),
            ("Genetic Algorithm", self.solve_n_queens_genetic),
        ]

        print(f"Solving N-Queens for N = {self.n}\n")
        for name, solver in approaches:
            self.solutions = 0  # Reset solution count for each approach
            start_time = time.time()
            solver()
            end_time = time.time()
            execution_time = end_time - start_time
            self.execution_times[name] = execution_time
            print(f"{name}:")
            print(f"  Solutions found: {self.solutions}")
            print(f"  Execution time: {execution_time:.4f} seconds")
            if self.solutions > 0:
                print("  First Solution:")
                self.print_board()  # Print the board for the first solution found
            else:
                print("  No solution found.")
            print("-" * 40)
        self.display_execution_times()

    def display_execution_times(self):
        """Displays the execution times for each approach."""
        print("\nExecution Times Summary:")
        for name, time in self.execution_times.items():
            print(f"{name}: {time:.4f} seconds")

if __name__ == "__main__":
    n = 8  # Change this to the desired board size
    n_queens = NQueens(n)
    n_queens.run_all_solvers()
