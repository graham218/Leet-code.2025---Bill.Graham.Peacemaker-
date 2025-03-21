import 'dart:collection';

void main() {
  final String beginWord = "hit";
  final String endWord = "cog";
  final List<String> wordList = ["hot", "dot", "dog", "lot", "log", "cog"];

  print("Word Ladder: $beginWord -> $endWord, Word List: $wordList");

  print("Approach 1: BFS (Queue)");
  print(wordLadderBFS(beginWord, endWord, wordList));

  print("\nApproach 2: BFS (Queue) Optimized");
  print(wordLadderBFSOptimized(beginWord, endWord, wordList));

  print("\nApproach 3: Bidirectional BFS");
  print(wordLadderBidirectionalBFS(beginWord, endWord, wordList));

  print("\nApproach 4: DFS (Recursion) - Pruning");
  print(wordLadderDFSPruning(beginWord, endWord, wordList));
}

// Approach 1: BFS (Queue)
int wordLadderBFS(String beginWord, String endWord, List<String> wordList) {
  // If the endWord is not in the wordList, no transformation is possible.
  if (!wordList.contains(endWord)) return 0;

  // Convert the wordList to a Set for efficient lookup.
  Set<String> wordSet = wordList.toSet();

  // Initialize a queue for BFS, starting with the beginWord.
  Queue<String> queue = Queue()..cast<String>();
  queue.add(beginWord);

  // Initialize a map to store the distance from the beginWord to each word.
  Map<String, int> distance = {beginWord: 1};

  // Perform BFS until the queue is empty.
  while (queue.isNotEmpty) {
    // Get the current word from the front of the queue.
    String currentWord = queue.removeFirst();

    // If the current word is the endWord, return the distance.
    if (currentWord == endWord) return distance[currentWord]!;

    // Iterate through each character of the current word.
    for (int i = 0; i < currentWord.length; i++) {
      // Iterate through all possible characters (a-z).
      for (int j = 97; j <= 122; j++) { // a-z
        // Create a new word by replacing the i-th character with the current character.
        String newWord = currentWord.substring(0, i) + String.fromCharCode(j) + currentWord.substring(i + 1);

        // If the new word is in the wordSet and has not been visited, add it to the queue.
        if (wordSet.contains(newWord) && !distance.containsKey(newWord)) {
          // Update the distance of the new word.
          distance[newWord] = distance[currentWord]! + 1;
          queue.add(newWord);
        }
      }
    }
  }

  // If the endWord is not reached, return 0.
  return 0;
}

// Approach 2: BFS (Queue) Optimized
int wordLadderBFSOptimized(String beginWord, String endWord, List<String> wordList) {
  if (!wordList.contains(endWord)) return 0;

  Set<String> wordSet = wordList.toSet();
  Queue<String> queue = Queue().cast<String>();
  queue.add(beginWord);
  int level = 1; //keeps track of the level, which is the transformation count
  while(queue.isNotEmpty){
    int size = queue.length; //process all items at the current level
    for(int k = 0; k < size; k++){
      String current = queue.removeFirst();
      if(current == endWord) return level; //found the end word

      for(int i = 0; i < current.length; i++){
        for(int j = 97; j <= 122; j++){
          String next = current.substring(0, i) + String.fromCharCode(j) + current.substring(i+1);
          if(wordSet.remove(next)){ //remove from word set, so it is not processed twice.
            queue.add(next);
          }
        }
      }
    }
    level++; //move to next level
  }
  return 0;
}

// Approach 3: Bidirectional BFS
int wordLadderBidirectionalBFS(String beginWord, String endWord, List<String> wordList) {
  if (!wordList.contains(endWord)) return 0;

  Set<String> wordSet = wordList.toSet();
  Set<String> beginSet = {beginWord};
  Set<String> endSet = {endWord};
  int level = 1;

  while (beginSet.isNotEmpty && endSet.isNotEmpty) {
    // Swap beginSet and endSet if beginSet is larger to optimize.
    if (beginSet.length > endSet.length) {
      Set<String> temp = beginSet;
      beginSet = endSet;
      endSet = temp;
    }

    Set<String> nextSet = {};
    for (String currentWord in beginSet) {
      for (int i = 0; i < currentWord.length; i++) {
        for (int j = 97; j <= 122; j++) {
          String newWord = currentWord.substring(0, i) + String.fromCharCode(j) + currentWord.substring(i + 1);
          if (endSet.contains(newWord)) {
            return level + 1; // Found the intersection.
          }
          if (wordSet.remove(newWord)) {
            nextSet.add(newWord);
          }
        }
      }
    }
    beginSet = nextSet;
    level++;
  }

  return 0;
}

// Approach 4: DFS (Recursion) - Pruning
int wordLadderDFSPruning(String beginWord, String endWord, List<String> wordList) {
  if (!wordList.contains(endWord)) return 0;
  Set<String> wordSet = wordList.toSet();
  int minLength = 1000000; // Initialize with a large value.

  void dfs(String current, String end, int length) {
    if (current == end) {
      minLength = minLength < length ? minLength : length; // Update minLength.
      return;
    }
    if (length >= minLength) return; // Prune if length is already greater than minLength.

    for (int i = 0; i < current.length; i++) {
      for (int j = 97; j <= 122; j++) {
        String next = current.substring(0, i) + String.fromCharCode(j) + current.substring(i + 1);
        if (wordSet.remove(next)) {
          dfs(next, end, length + 1);
          wordSet.add(next); // Backtrack.
        }
      }
    }
  }

  dfs(beginWord, endWord, 1);
  return minLength == 1000000 ? 0 : minLength;
}