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
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    char tolower(char c) {
        if (c >= 'A' && c <= 'Z') return c - 'A' + 'a';
        return c;
    }

    bool isletter(char c) {
        return (c >= 'a' && c <= 'z');
    }

    // Insert one word
    void insert(string word) {
        TrieNode* curr = root;
        for (char c : word) {
            c = tolower(c);
            if (!isletter(c)) continue;
            int idx = c - 'a';
            if (!curr->next[idx])
                curr->next[idx] = new TrieNode();
            curr = curr->next[idx];
        }
        curr->isEnd = true;
        curr->cnt++;
    }

    // Search exact word
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
