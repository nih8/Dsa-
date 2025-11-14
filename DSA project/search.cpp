#include <bits/stdc++.h>
using namespace std;

// Defining trieNode: each node that has an array of 26 pointers

struct TrieNode {
    TrieNode* next[26];
    bool isEnd;
    int cnt; // word count, cnt increases by 1 when isEnd == True

    // initially, all 26 pinters are set to nullptr, and if path doesn't exist it returns to nullptr

    TrieNode() {
        for (int i = 0; i < 26; i++) next[i] = nullptr;
        isEnd = false; // end of word isn't reached yet
        cnt = 0;
    }
};

class Trie {
public:
    TrieNode* root; // pointer named root that points to a TrieNode(starting point of trie)

    Trie() {
        root = new TrieNode(); // Creates a new TrieNode on the heap and sets root to point to it
    }

    char tolower(char c) /*converts an uppercase letter to lowercase */{
        if (c >= 'A' && c <= 'Z') return c - 'A' + 'a';
        return c;
    }

    bool isletter(char c)/* checks if a character is a lowercase letter */{
        return (c >= 'a' && c <= 'z');
    }

    // Insert one word
    void insert(string word) {
        TrieNode* curr = root; // Creates a pointer curr that starts at the root of the trie.
        for (char c : word) {
            c = tolower(c);
            if (!isletter(c)) continue;
            int idx = c - 'a';
            if (!curr->next[idx])
                curr->next[idx] = new TrieNode();
            curr = curr->next[idx]; // Move curr to this child node to process the next character
        }
        curr->isEnd = true; // mark this node as the end of a word
        curr->cnt++;
    }

    // Search exact word: true if the word exists, false otherwise.

    bool search(string word) {
        TrieNode* curr = root; // pointer starts searching from root node, moves from letter to letter
        for (char c : word) {
            c = tolower(c); // converts to lower case
            if (!isletter(c)) continue;
            int idx = c - 'a';
            if (!curr->next[idx])
                return false;
            curr = curr->next[idx]; // next letter of the word
        }
        return curr->isEnd; // all letters of the word are checked
    }

    // Autocomplete helper: used to print all words in the trie that start with a given prefix

    void suggestions(TrieNode* node, string prefix) /* node: the current TrieNode; prefix: the string formed so far(root to node)*/{
        if (!node) return; // stop the recursion, prevents accessing a non-existent node
        if (node->isEnd) //end of a word
            cout << prefix << " (" << node->cnt << ")\n";
        for (int i = 0; i < 26; i++) {
            if (node->next[i])
                suggestions(node->next[i], prefix + char('a' + i)); // Calls suggestions recursively on that child node.
        }
    }

    // Autocomplete main: it prints suggestions directly

    void autocomplete(string prefix) {
        TrieNode* curr = root;
        for (char c : prefix) {
            c = tolower(c);
            if (!isletter(c)) continue;
            int idx = c - 'a';
            if (!curr->next[idx]) /*no word in the trie starts with this prefix.*/{
                cout << "No suggestions found for \"" << prefix << "\"\n"; // if no matching list is found by the end of the new word entered
                return;
            }
            curr = curr->next[idx];
        }
        cout << "Autocomplete suggestions for \"" << prefix << "\":\n";
        suggestions(curr, prefix); // calls the suggestions functions, and will recursively fill all words starting from those letters
    }
};
