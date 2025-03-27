'''
Advanced Sliding Window: Minimum Window Substring - Real-World Applications

Problem Statement:
Given two strings s and t, return the minimum window in s which contains all characters of t in any order.
If no such window exists, return an empty string "".
'''

from collections import Counter, defaultdict

# 1. Cybersecurity - Detecting Malicious Code Patterns (O(n))
def detect_malicious_code(source_code, signature):
    """
    Detects malicious code patterns within a source code string.  It identifies the smallest section of code
    that contains a given malicious code signature.  This is useful for locating potential threats within
    large codebases.

    Args:
        source_code (str): The source code to analyze.
        signature (str): The malicious code signature to detect (e.g., a specific sequence of instructions).

    Returns:
        str: The minimum window substring of the source code that contains the signature, or "" if not found.
    """
    signature_count = Counter(signature)  # Count character frequencies in the malicious code signature.
    window_count = Counter()  # Count character frequencies in the current window of the source code.
    left = 0  # Left pointer of the sliding window.
    min_len = float("inf")  # Initialize minimum length to infinity.
    min_snippet = ""  # Initialize the minimum code snippet.

    for right in range(len(source_code)):  # Iterate through the source code using the right pointer.
        window_count[source_code[right]] += 1  # Add the current character to the window count.
        while all(window_count[c] >= signature_count[c] for c in signature_count):
            # While the current window contains all characters of the signature with sufficient frequency:
            if right - left + 1 < min_len:  # If the current window is smaller than the smallest window found so far,
                min_len = right - left + 1  # update the minimum length,
                min_snippet = source_code[left:right+1]  # and store the corresponding code snippet.
            window_count[source_code[left]] -= 1  # Remove the leftmost character from the window count.
            left += 1  # Shrink the window from the left.
    return min_snippet  # Return the smallest code snippet containing the signature.

# 2. Financial Fraud Detection - Identifying Suspicious Transactions (O(n))
def detect_suspicious_transactions(transactions, pattern):
    """
    Identifies suspicious transaction patterns within a sequence of transactions.  It finds the shortest sequence
    of transactions that contains a given suspicious pattern.  This can help in flagging potentially fraudulent
    activities.

    Args:
        transactions (str): The sequence of transactions (e.g., "A-B-C-D-A-C-E").
        pattern (str): The suspicious transaction pattern to detect (e.g., "A-C-A").

    Returns:
        str: The minimum window of transactions that contains the pattern, or "" if not found.
    """
    pattern_count = Counter(pattern)  # Count the frequency of each transaction type in the suspicious pattern.
    window_count = Counter()  # Count the frequency of transactions in the current window.
    left = 0  # Left pointer of the sliding window.
    min_len = float("inf")  # Initialize minimum length to infinity.
    min_substring = ""  # Initialize the minimum substring.

    for right in range(len(transactions)):  # Iterate through the transactions.
        window_count[transactions[right]] += 1  # Add the current transaction to the window count.
        while all(window_count[c] >= pattern_count[c] for c in pattern_count):
            # While the current window contains all transactions of the pattern:
            if right - left + 1 < min_len:  # If the current window is smaller than the minimum length,
                min_len = right - left + 1  # update the minimum length,
                min_substring = transactions[left:right+1]  # and store the substring.
            window_count[transactions[left]] -= 1  # Remove the leftmost transaction from the window count.
            left += 1  # Shrink the window.
    return min_substring  # Return the shortest sequence of transactions matching the pattern.

# 3. Healthcare - Finding Genetic Mutation Sequences (O(n))
def find_mutation_sequence(dna_sequence, mutation):
    """
    Finds the shortest DNA subsequence that contains a given genetic mutation sequence.  This can be used to locate
    specific mutations within a larger DNA strand, which is crucial for genetic research and diagnostics.

    Args:
        dna_sequence (str): The DNA sequence to search within.
        mutation (str): The genetic mutation sequence to find.

    Returns:
        str: The minimum DNA subsequence containing the mutation, or "" if not found.
    """
    mutation_count = Counter(mutation)  # Count the frequency of each nucleotide in the mutation.
    window_count = Counter()  # Count the frequency of nucleotides in the current window.
    left = 0  # Left pointer of the sliding window.
    min_len = float("inf")  # Initialize minimum length.
    min_substring = ""  # Initialize the minimum substring.

    for right in range(len(dna_sequence)):  # Iterate through the DNA sequence.
        window_count[dna_sequence[right]] += 1  # Add the current nucleotide to the window count.
        while all(window_count[c] >= mutation_count[c] for c in mutation_count):
            # While the current window contains all nucleotides of the mutation:
            if right - left + 1 < min_len:  # If the current window is smaller than the minimum length,
                min_len = right - left + 1  # update the minimum length,
                min_substring = dna_sequence[left:right+1]  # and store the substring.
            window_count[dna_sequence[left]] -= 1  # Remove the leftmost nucleotide from the window count.
            left += 1  # Shrink the window.
    return min_substring  # Return the shortest DNA subsequence containing the mutation.

# 4. Content Moderation - Detecting Offensive Phrases (O(n))
def detect_offensive_phrases(text, phrase):
    """
    Detects the shortest segment of text that contains a given offensive phrase.  This can be used to identify
    and flag potentially harmful content in online platforms.

    Args:
        text (str): The text to analyze.
        phrase (str): The offensive phrase to detect.

    Returns:
        str: The minimum text segment containing the offensive phrase, or "" if not found.
    """
    phrase_count = Counter(phrase)  # Count the frequency of each character in the offensive phrase.
    window_count = Counter()  # Count the frequency of characters in the current window.
    left = 0  # Left pointer of the sliding window.
    min_len = float("inf")  # Initialize minimum length.
    min_substring = ""  # Initialize the minimum substring.

    for right in range(len(text)):  # Iterate through the text.
        window_count[text[right]] += 1  # Add the current character to the window count.
        while all(window_count[c] >= phrase_count[c] for c in phrase_count):
            # While the current window contains all characters of the offensive phrase:
            if right - left + 1 < min_len:  # If the current window is smaller than the minimum length,
                min_len = right - left + 1  # update the minimum length,
                min_substring = text[left:right+1]  # and store the substring.
            window_count[text[left]] -= 1  # Remove the leftmost character from the window count.
            left += 1  # Shrink the window.
    return min_substring  # Return the shortest text segment containing the offensive phrase.

# 5. AI Chatbot - Detecting Key Commands (O(n))
def detect_key_commands(conversation, command):
    """
    Detects the shortest segment of a conversation that contains a given key command.  This can be used to identify
    user intents or trigger specific actions in a chatbot.

    Args:
        conversation (str): The conversation history.
        command (str): The key command to detect.

    Returns:
        str: The minimum conversation segment containing the key command, or "" if not found.
    """
    command_count = Counter(command)  # Count the frequency of each word/character in the command.
    window_count = Counter()  # Count the frequency of words/characters in the current window.
    left = 0  # Left pointer of the sliding window.
    min_len = float("inf")  # Initialize minimum length.
    min_substring = ""  # Initialize the minimum substring.

    for right in range(len(conversation)):  # Iterate through the conversation.
        window_count[conversation[right]] += 1  # Add the current word/character to the window count.
        while all(window_count[c] >= command_count[c] for c in command_count):
            # While the current window contains all words/characters of the command:
            if right - left + 1 < min_len:  # If the current window is smaller than the minimum length,
                min_len = right - left + 1  # update the minimum length,
                min_substring = conversation[left:right+1]  # and store the substring.
            window_count[conversation[left]] -= 1  # Remove the leftmost word/character from the window count.
            left += 1  # Shrink the window.
    return min_substring  # Return the shortest conversation segment containing the key command.

# 6. Network Security - Identifying Anomalous Packet Sequences (O(n))
def detect_anomalous_packets(network_stream, anomaly_pattern):
    """
    Identifies the shortest sequence of network packets that contains a given anomaly pattern.  This can be used to
    detect suspicious network activity, such as denial-of-service attacks or data exfiltration attempts.

    Args:
        network_stream (str): The sequence of network packets.
        anomaly_pattern (str): The anomaly pattern to detect.

    Returns:
        str: The minimum packet sequence containing the anomaly pattern, or "" if not found.
    """
    anomaly_count = Counter(anomaly_pattern)  # Count the frequency of each packet type in the anomaly pattern.
    window_count = Counter()  # Count the frequency of packets in the current window.
    left = 0  # Left pointer of the sliding window.
    min_len = float("inf")  # Initialize minimum length.
    min_substring = ""  # Initialize the minimum substring.

    for right in range(len(network_stream)):  # Iterate through the network stream.
        window_count[network_stream[right]] += 1  # Add the current packet to the window count.
        while all(window_count[c] >= anomaly_count[c] for c in anomaly_pattern):
            # While the current window contains all packets of the anomaly pattern:
            if right - left + 1 < min_len:  # If the current window is smaller than the minimum length,
                min_len = right - left + 1  # update the minimum length,
                min_substring = network_stream[left:right+1]  # and store the substring.
            window_count[network_stream[left]] -= 1  # Remove the leftmost packet from the window count.
            left += 1  # Shrink the window.
    return min_substring  # Return the shortest packet sequence containing the anomaly pattern.

# Test Cases
source_code = "if(malware_detected) then { block_network(); }"
signature = "block"
print("Malicious Code Detection:", detect_malicious_code(source_code, signature))

transactions = "txn1txn2txn3txn4txn5txn6txn7txn8"
pattern = "txn4txn5"
print("Fraud Detection:", detect_suspicious_transactions(transactions, pattern))

dna_sequence = "AGCTGATCGTAGCTA"
mutation = "GATC"
print("Genetic Mutation Detection:", find_mutation_sequence(dna_sequence, mutation))

text = "This message contains offensive content."
phrase = "offensive"
print("Content Moderation:", detect_offensive_phrases(text, phrase))

conversation = "bot_help_startbot_help_stop"
command = "help"
print("Chatbot Command Detection:", detect_key_commands(conversation, command))

network_stream = "ABCDXABCDYABCDZ"
anomaly_pattern = "ABCD"
print("Network Anomaly Detection:", detect_anomalous_packets(network_stream, anomaly_pattern))
