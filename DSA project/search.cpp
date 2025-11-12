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

