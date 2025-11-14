# 🧭 Mini Search Engine (C++)

This project implements a mini text-search engine using core C++ data structures.
It supports Word Search, Phrase Search, and Autocomplete across multiple .txt files.

## Features

Indexes all words from multiple files

Stores word positions for fast lookup

Word search sorted by highest frequency

Phrase search with exact sequential matching

Trie-based autocomplete for prefixes

 ## How It Works

Load text files

Normalize: lowercase + remove punctuation

Skip stopwords

Build global index:

unordered_map<string, unordered_map<string, vector<int>>>


### Insert words into Trie

Provide search operations via menu

 ### Word Search

Directly fetch frequency from index and sort files by occurrences.

### Phrase Search

Check if phrase words appear sequentially using position matching.

### Autocomplete

Trie returns all words matching a given prefix.

### My Contribution (Stage 5)

Implemented graph bipartite check using BFS and color assignment
to validate relationships across files.

🔹 How to Run
g++ main.cpp -o search
./search
