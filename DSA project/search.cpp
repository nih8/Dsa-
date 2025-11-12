#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    TrieNode* next[26];
    bool isEnd;
    int cnt;

    TrieNode() {
        for (int i = 0; i < 26; i++) next[i] = nullptr;
        isEnd = false;
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
        TrieNode* curr = root;
        for (char c : word) {
            c = tolower(c);
            if (!isletter(c)) continue;
            int idx = c - 'a';
            if (!curr->next[idx])
                return false;
            curr = curr->next[idx];
        }
        return curr->isEnd;
    }

    // Autocomplete helper
    void suggestions(TrieNode* node, string prefix) {
        if (!node) return;
        if (node->isEnd)
            cout << prefix << " (" << node->cnt << ")\n";
        for (int i = 0; i < 26; i++) {
            if (node->next[i])
                suggestions(node->next[i], prefix + char('a' + i));
        }
    }

    // Autocomplete main
    void autocomplete(string prefix) {
        TrieNode* curr = root;
        for (char c : prefix) {
            c = tolower(c);
            if (!isletter(c)) continue;
            int idx = c - 'a';
            if (!curr->next[idx]) {
                cout << "No suggestions found for \"" << prefix << "\"\n";
                return;
            }
            curr = curr->next[idx];
        }
        cout << "Autocomplete suggestions for \"" << prefix << "\":\n";
        suggestions(curr, prefix);
    }
};

int main() {
    Trie trie;

    // Simulating words that would have been indexed from earlier stages
    vector<string> words = {
        "machine", "machinery", "learning", "learn", "leader", "lead", "league"
    };

    for (auto &w : words) trie.insert(w);

    cout << "Words inserted into Trie.\n";

    while (true) {
        cout << "\n1. Search word\n2. Autocomplete\n3. Exit\nChoice: ";
        int ch; cin >> ch; cin.ignore();
        if (ch == 3) break;

        if (ch == 1) {
            string word;
            cout << "Enter word: ";
            getline(cin, word);
            if (trie.search(word))
                cout << word << " found in Trie.\n";
            else
                cout << word << " not found.\n";
        } else if (ch == 2) {
            string prefix;
            cout << "Enter prefix: ";
            getline(cin, prefix);
            trie.autocomplete(prefix);
        }
    }

    return 0;
}

