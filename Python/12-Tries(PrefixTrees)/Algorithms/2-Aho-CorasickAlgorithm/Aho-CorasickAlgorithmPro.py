import collections

class AhoCorasick:
    """
    Aho-Corasick string matching algorithm implementation.  This class
    provides several methods to find multiple keywords within a text.
    """

    def __init__(self, keywords):
        """
        Initializes the AhoCorasick object with a list of keywords.

        Args:
            keywords (list): A list of strings representing the keywords to search for.
        """
        self.keywords = keywords
        self.trie = {}
        self.failure_links = {}
        self.outputs = {}
        self._build_trie()
        self._build_failure_links()

    def _build_trie(self):
        """
        Builds the Trie data structure from the keywords.
        """
        next_state = 0
        for i, keyword in enumerate(self.keywords):
            state = 0
            for char in keyword:
                if char not in self.trie.setdefault(state, {}):
                    next_state += 1
                    self.trie[state][char] = next_state
                state = self.trie[state][char]
            self.outputs.setdefault(state, []).append(i)  # Store keyword index, not the string

    def _build_failure_links(self):
        """
        Builds the failure links for each state in the Trie.
        """
        queue = collections.deque()
        self.failure_links[0] = 0
        for char in self.trie.get(0, {}):
            state = self.trie[0][char]
            self.failure_links[state] = 0
            queue.append(state)

        while queue:
            state = queue.popleft()
            for char in self.trie.get(state, {}):
                next_state = self.trie[state][char]
                queue.append(next_state)
                failure = self.failure_links[state]
                while failure != 0 and char not in self.trie.get(failure, {}):
                    failure = self.failure_links[failure]
                self.failure_links[next_state] = self.trie[failure][char] if char in self.trie.get(failure, {}) else 0
                self.outputs.setdefault(next_state, []).extend(self.outputs.get(self.failure_links[next_state], []))

    def search(self, text):
        """
        Searches for the keywords in the given text.

        Args:
            text (str): The text to search within.

        Returns:
            list: A list of tuples, where each tuple contains the start index of the match,
                  the end index of the match, and the matched keyword (from self.keywords).
                  Returns an empty list if no matches are found.
        """
        state = 0
        results = []
        for i, char in enumerate(text):
            while state != 0 and char not in self.trie.get(state, {}):
                state = self.failure_links[state]
            state = self.trie[state][char] if char in self.trie.get(state, {}) else 0
            if state in self.outputs:
                for keyword_index in self.outputs[state]:
                    keyword = self.keywords[keyword_index]
                    start_index = i - len(keyword) + 1
                    results.append((start_index, i, keyword))
        return results

    def search_with_context(self, text, context_size=10):
        """
        Searches for keywords and returns matches with surrounding context.

        Args:
            text (str): The text to search.
            context_size (int): The number of characters to include before and after the match.

        Returns:
             list: A list of dictionaries, where each dictionary contains:
                - 'start_index': Start index of the match.
                - 'end_index': End index of the match.
                - 'keyword': The matched keyword.
                - 'context': The surrounding text context.
        """
        matches = self.search(text)
        results = []
        for start, end, keyword in matches:
            start_context = max(0, start - context_size)
            end_context = min(len(text), end + context_size + 1)
            context = text[start_context:end_context]
            results.append({
                "start_index": start,
                "end_index": end,
                "keyword": keyword,
                "context": context
            })
        return results

    def replace_keywords(self, text, replacement="*"):
        """
        Replaces found keywords in the text with a replacement string.

        Args:
            text (str): The text to process.
            replacement (str, optional): The replacement string. Defaults to "*".

        Returns:
            str: The text with keywords replaced.
        """
        matches = self.search(text)
        offset = 0
        new_text = list(text)  # Convert to list for efficient modification
        for start, end, keyword in matches:
            start += offset
            end += offset
            new_text[start:end + 1] = list(replacement * len(keyword))
            offset += len(replacement) - len(keyword)
        return "".join(new_text)

    def get_trie(self):
        """
        Returns the Trie data structure.  Useful for debugging and visualization.

        Returns:
            dict: The Trie data structure representing the keywords.
        """
        return self.trie

    def get_failure_links(self):
        """
        Returns the failure links.  Useful for debugging and visualization.

        Returns:
            dict: The failure links for each state.
        """
        return self.failure_links

def keyword_search_example():
    """
    Example usage: Simple keyword search.
    """
    keywords = ["apple", "banana", "orange", "grape"]
    text = "I have an apple and a banana, but I want a grape."
    ac = AhoCorasick(keywords)
    results = ac.search(text)
    print("\nExample 1: Keyword Search")
    print(f"Text: {text}")
    print(f"Keywords: {keywords}")
    print("Matches:", results)

def context_search_example():
    """
     Example usage: Keyword search with context.
    """
    keywords = ["the", "quick", "brown", "fox"]
    text = "The quick brown fox jumps over the lazy dog."
    ac = AhoCorasick(keywords)
    results = ac.search_with_context(text, context_size=5)
    print("\nExample 2: Search with Context")
    print(f"Text: {text}")
    print(f"Keywords: {keywords}")
    for match in results:
        print(f"Match: {match['keyword']}, Context: {match['context']}")

def replace_keywords_example():
    """
    Example usage: Replacing keywords in text.
    """
    keywords = ["bad", "evil", "naughty"]
    text = "This is a bad, evil, and naughty sentence."
    ac = AhoCorasick(keywords)
    censored_text = ac.replace_keywords(text, replacement="***")
    print("\nExample 3: Replace Keywords")
    print(f"Original Text: {text}")
    print(f"Keywords: {keywords}")
    print(f"Censored Text: {censored_text}")

def large_text_search_example():
    """
    Example usage: Searching in a large text.
    """
    keywords = ["is", "are", "was", "were", "be", "been", "being"]
    # Simulate a large text (e.g., a paragraph or an article)
    large_text = """
    The Aho-Corasick algorithm is an efficient algorithm.  It can locate
    multiple keywords within a text.  The keywords are often from a dictionary.
    This is useful when you need to find all occurrences.  There were many
    applications of this algorithm.  Finding these patterns can be important.
    """
    ac = AhoCorasick(keywords)
    results = ac.search(large_text)
    print("\nExample 4: Large Text Search")
    print(f"Keywords: {keywords}")
    print(f"Text (first 100 chars): {large_text[:100]}...")
    print(f"Number of Matches: {len(results)}")
    if results:
        print(f"First Match: {results[0]}") # Print only the first match

def case_insensitive_search_example():
    """
    Example usage: Case-insensitive search.
    """
    keywords = ["apple", "Banana", "ORANGE"]
    text = "I have an Apple and a banana, but I want an orange."
    # Convert both keywords and text to lowercase for case-insensitive matching
    lower_keywords = [keyword.lower() for keyword in keywords]
    ac = AhoCorasick(lower_keywords) # use lower_keywords
    results = []
    lower_text = text.lower()
    for start, end, keyword in ac.search(lower_text):
        #Find the original case keyword
        original_keyword = ""
        for k in keywords:
            if k.lower() == keyword:
                original_keyword = k
                break
        results.append((start, end, original_keyword))

    print("\nExample 5: Case-Insensitive Search")
    print(f"Text: {text}")
    print(f"Keywords: {keywords}")
    print("Matches:", results)

def overlapping_matches_example():
    """
    Example of finding overlapping matches
    """
    keywords = ["he", "she", "hers", "his"]
    text = "This is a test of his and hers."
    ac = AhoCorasick(keywords)
    results = ac.search(text)
    print("\nExample 6: Overlapping Matches")
    print(f"Text: {text}")
    print(f"Keywords: {keywords}")
    print("Matches:", results)

if __name__ == "__main__":
    keyword_search_example()
    context_search_example()
    replace_keywords_example()
    large_text_search_example()
    case_insensitive_search_example()
    overlapping_matches_example()
