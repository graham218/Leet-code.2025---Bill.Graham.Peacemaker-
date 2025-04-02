import collections

# Approach 1: Basic Trie Construction and Search (for understanding Trie structure)
class TrieNode1:
    def __init__(self):
        self.children = collections.defaultdict(TrieNode1)
        self.is_end_of_word = False
        self.word = None  # Store the complete word here

class Trie1:
    def __init__(self):
        self.root = TrieNode1()

    def insert(self, word):
        node = self.root
        for char in word:
            node = node.children[char]
        node.is_end_of_word = True
        node.word = word # Store the word
    def search(self, text):
        """
        Basic search: Returns True if the *entire* text matches a word in the trie.
        This is NOT what Aho-Corasick does, but it's useful for understanding Tries.
        """
        node = self.root
        for char in text:
            if char not in node.children:
                return False
            node = node.children[char]
        return node.is_end_of_word

    def get_all_words(self, node, current_word, words):
        """
        Helper function to get all words from a Trie.  Useful for testing.
        """
        if node.is_end_of_word:
            words.append(current_word)
        for char, child in node.children.items():
            self.get_all_words(child, current_word + char, words)

    def get_words(self):
        """
        Gets all words stored in the Trie.
        """
        words = []
        self.get_all_words(self.root, "", words)
        return words
# Approach 2: Trie Construction with Failure Links (Aho-Corasick's core)
class TrieNode2:
    def __init__(self):
        self.children = collections.defaultdict(TrieNode2)
        self.is_end_of_word = False
        self.failure_link = None  # Failure link for Aho-Corasick
        self.word = None

class Trie2:
    def __init__(self):
        self.root = TrieNode2()

    def insert(self, word):
        node = self.root
        for char in word:
            node = node.children[char]
        node.is_end_of_word = True
        node.word = word

    def build_failure_links(self):
        """
        Builds failure links using BFS.  This is the key to Aho-Corasick.
        """
        queue = collections.deque([self.root])
        self.root.failure_link = self.root  # Failure link of root points to itself

        while queue:
            node = queue.popleft()
            for char, child in node.children.items():
                queue.append(child)
                if node == self.root:
                    child.failure_link = self.root
                else:
                    temp = node.failure_link
                    while temp != self.root and char not in temp.children:
                        temp = temp.failure_link
                    if char in temp.children:
                        child.failure_link = temp.children[char]
                    else:
                        child.failure_link = self.root
    def search_with_failures(self, text):
        """
        Aho-Corasick search using failure links.  Finds all occurrences.
        Returns a list of tuples (start_index, matched_word).
        """
        node = self.root
        results = []
        for i, char in enumerate(text):
            while node != self.root and char not in node.children:
                node = node.failure_link
            if char in node.children:
                node = node.children[char]
            if node.is_end_of_word:
                results.append((i - len(node.word) + 1, node.word))
        return results

# Approach 3:  Optimized Trie Construction and Search
class TrieNode3:
    def __init__(self):
        self.children = {}  # Use a standard dict instead of defaultdict
        self.is_end_of_word = False
        self.failure_link = None
        self.word = None

class Trie3:
    def __init__(self):
        self.root = TrieNode3()

    def insert(self, word):
        node = self.root
        for char in word:
            if char not in node.children:  # More efficient check
                node.children[char] = TrieNode3()
            node = node.children[char]
        node.is_end_of_word = True
        node.word = word

    def build_failure_links(self):
        queue = collections.deque([self.root])
        self.root.failure_link = self.root

        while queue:
            node = queue.popleft()
            for char, child in node.children.items():
                queue.append(child)
                if node == self.root:
                    child.failure_link = self.root
                else:
                    temp = node.failure_link
                    while temp != self.root and char not in temp.children:
                        temp = temp.failure_link
                    child.failure_link = temp.children.get(char, self.root) # Use .get()

    def search_optimized(self, text):
        """
        Optimized search function.
        """
        node = self.root
        results = []
        for i, char in enumerate(text):
            while node != self.root and char not in node.children:
                node = node.failure_link
            if char in node.children:
                node = node.children[char]
            if node.is_end_of_word:
                results.append((i - len(node.word) + 1, node.word))
        return results

# Approach 4: Aho-Corasick with Output Links
class TrieNode4:
    def __init__(self):
        self.children = {}
        self.is_end_of_word = False
        self.failure_link = None
        self.output_link = None # Output link
        self.word = None

class Trie4:
    def __init__(self):
        self.root = TrieNode4()

    def insert(self, word):
        node = self.root
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode4()
            node = node.children[char]
        node.is_end_of_word = True
        node.word = word

    def build_failure_links(self):
        queue = collections.deque([self.root])
        self.root.failure_link = self.root

        while queue:
            node = queue.popleft()
            for char, child in node.children.items():
                queue.append(child)
                if node == self.root:
                    child.failure_link = self.root
                else:
                    temp = node.failure_link
                    while temp != self.root and char not in temp.children:
                        temp = temp.failure_link
                    child.failure_link = temp.children.get(char, self.root)

    def build_output_links(self):
        """Build output links.  Output links point to the longest proper suffix
        that is also a prefix in the trie."""
        queue = collections.deque([self.root])
        while queue:
            node = queue.popleft()
            for child in node.children.values():
                queue.append(child)
            if node.failure_link is not None and node.failure_link.is_end_of_word:
                node.output_link = node.failure_link
            elif node.failure_link is not None:
                node.output_link = node.failure_link.output_link
            else:
                node.output_link = None

    def search_with_output_links(self, text):
        """Search using output links."""
        node = self.root
        results = []
        for i, char in enumerate(text):
            while node != self.root and char not in node.children:
                node = node.failure_link
            if char in node.children:
                node = node.children[char]
            temp = node
            while temp:
                if temp.is_end_of_word:
                    results.append((i - len(temp.word) + 1, temp.word))
                temp = temp.output_link
        return results

# Approach 5: Aho-Corasick using a Dictionary for Transitions
class TrieNode5:
    def __init__(self):
        self.transitions = {}  # Store transitions as a dictionary: {char: next_state}
        self.is_end_of_word = False
        self.failure_link = 0  # Store the state number of the failure link
        self.output = []  # List of words ending at this state.  Using a list.
        self.word = None

class AhoCorasick5:  # Not named Trie to avoid confusion.
    def __init__(self, words):
        self.states = [TrieNode5()]  # List of states.  State 0 is the root.
        self.build_trie(words)
        self.build_failure_links()

    def build_trie(self, words):
        """Builds the Trie and stores it as a state machine."""
        for word in words:
            self.add_word(word)

    def add_word(self, word):
        """Adds a word to the Trie."""
        state = 0  # Start at the root (state 0)
        for char in word:
            if char not in self.states[state].transitions:
                self.states[state].transitions[char] = len(self.states)  # New state
                self.states.append(TrieNode5())
            state = self.states[state].transitions[char]
        self.states[state].is_end_of_word = True
        self.states[state].output.append(word) # store the word in output
        self.states[state].word = word

    def build_failure_links(self):
        """Builds failure links."""
        queue = collections.deque([0])  # Start with the root (state 0)
        self.states[0].failure_link = 0

        while queue:
            state = queue.popleft()
            for char, next_state in self.states[state].transitions.items():
                queue.append(next_state)
                if state == 0:
                    self.states[next_state].failure_link = 0
                else:
                    fail_state = self.states[state].failure_link
                    while fail_state != 0 and char not in self.states[fail_state].transitions:
                        fail_state = self.states[fail_state].failure_link
                    self.states[next_state].failure_link = (
                        self.states[fail_state].transitions.get(char, 0)
                    )
                    self.states[next_state].output.extend(self.states[self.states[next_state].failure_link].output) # important

    def search(self, text):
        """Searches for all occurrences of the words in the text."""
        state = 0
        results = []
        for i, char in enumerate(text):
            while state != 0 and char not in self.states[state].transitions:
                state = self.states[state].failure_link
            if char in self.states[state].transitions:
                state = self.states[state].transitions[char]
            for word in self.states[state].output:
                results.append((i - len(word) + 1, word))
        return results

def test_all_approaches():
    """
    Tests all five approaches with the same example.
    """
    words = ["he", "she", "his", "hers"]
    text = "ahishers"

    print("--- Approach 1: Basic Trie Search ---")
    trie1 = Trie1()
    for word in words:
        trie1.insert(word)
    print(f"Words in Trie: {trie1.get_words()}")
    print(f"Search 'ahishers': {trie1.search('ahishers')}") # Should return false
    print(f"Search 'he': {trie1.search('he')}") # Should return true

    print("\n--- Approach 2: Trie with Failure Links ---")
    trie2 = Trie2()
    for word in words:
        trie2.insert(word)
    trie2.build_failure_links()
    results2 = trie2.search_with_failures(text)
    print(f"Search results for '{text}': {results2}")

    print("\n--- Approach 3: Optimized Trie ---")
    trie3 = Trie3()
    for word in words:
        trie3.insert(word)
    trie3.build_failure_links()
    results3 = trie3.search_optimized(text)
    print(f"Search results for '{text}': {results3}")

    print("\n--- Approach 4: Trie with Output Links ---")
    trie4 = Trie4()
    for word in words:
        trie4.insert(word)
    trie4.build_failure_links()
    trie4.build_output_links()
    results4 = trie4.search_with_output_links(text)
    print(f"Search results for '{text}': {results4}")

    print("\n--- Approach 5: Dictionary-based Aho-Corasick ---")
    ac5 = AhoCorasick5(words)
    results5 = ac5.search(text)
    print(f"Search results for '{text}': {results5}")
    text2 = "The quick brown fox jumps over the lazy dog"
    words2 = ["quick", "brown", "fox", "jumps", "lazy", "dog"]
    ac6 = AhoCorasick5(words2)
    results6 = ac6.search(text2)
    print(f"Search results for '{text2}': {results6}")

if __name__ == "__main__":
    test_all_approaches()

