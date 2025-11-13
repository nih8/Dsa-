#include<bits/stdc++.h>
#include<fstream>
#include<sstream>
#include<ctype.h>
#include "to_insert_a_word.cpp"
using namespace std;

// stopwords list
unordered_set<string> non_imp_words = {
    "a", "an", "the", "and", "or", "but", "if", 
    "about", "against", "between", "into", "through", "during", "before", "after", 
    "above", "below", "to", "from", "up", "down", "in", "out", "on", "off", "over", 
    "under", "again", "further", "then", "once", "here", "there", "when", "where", 
    "why", "how", "all", "any", "both", "each", "few", "more", "most", "other", 
    "some", "such", "no", "nor", "not", "only", "own", "same", "so", "than", "too", 
    "very", "can", "will", "just", "don", "should", "now", "is", "am", "are", "was", 
    "were", "be", "been", "being", "have", "has", "had", "having", "do", "does", 
    "did", "doing", "this", "that", "these", "those", "he", "she", "it", "they", 
    "we", "you", "me", "him", "her", "us", "them", "my", "your", "his", "their", 
    "its", "ours", "yours", "myself", "yourself", "himself", "herself", "itself", 
    "ourselves", "yourselves", "themselves", "what", "which", "who", "whom", "whose", 
    "while", "at", "by", "for", "with"
};

// normalization function
string norm(string &curr) {
    int n = curr.size();
    for(char &c : curr) c = tolower(c);
    if(curr.empty()) return curr;
    if(ispunct(curr.front())) curr = curr.substr(1);
    while(!curr.empty() && ispunct(curr.back())) curr.pop_back();
    return curr;
}

bool binary_search(vector<int> v, int pos) {
    int left = 0, right = v.size() - 1;
    while(left <= right) {
        int mid = (left + right) / 2;
        if(v[mid] == pos) return true;
        else if(v[mid] < pos) left = mid + 1;
        else right = mid - 1;
    }
    return false;
}

void word_search(unordered_map<string, unordered_map<string, vector<int>>> &global_index, string word) {
    if(global_index.find(word) == global_index.end()) {
        cout << "0 Matches Found" << endl;
        return;
    }

    vector<pair<string, int>> results;
    for(auto &inside_map:global_index[word]) {
        results.push_back({inside_map.first,(int)inside_map.second.size()});
    }

    // 🔥 sort by frequency (descending)
    sort(results.begin(),results.end(),[](auto &a,auto &b){
        return a.second > b.second;
    });

    cout << "Found in (sorted by frequency):\n";
    for(auto &r:results) {
        cout<<r.first<<" ("<<r.second<<")\n";
    }
}

// helper for phrase match count
int lol(unordered_map<string,unordered_map<string,vector<int>>> &global_index, string phrase, string file) {
    stringstream phrase_s(phrase);
    string word;
    vector<string> p_w;
    while(phrase_s >> word) p_w.push_back(word);

    int count = 0;
    for(int pos : global_index[p_w[0]][file]) {
        int current = pos;
        bool match = true;
        for(int i=1; i<p_w.size(); i++) {
            vector<int> next_pos = global_index[p_w[i]][file];
            if(!binary_search(next_pos, current+1)) {
                match = false;
                break;
            }
            current++;
        }
        if(match) count++;
    }
    return count;
}

void phrase_search(unordered_map<string,unordered_map<string,vector<int>>> &global_index, string phrase) {
    vector<pair<string,int>> results;
    bool total = false;

    for(int i=0; i<4; i++) {
        string filename = "sample" + to_string(i+1) + ".txt";
        stringstream phrase_s(phrase);
        string word;
        bool flag = true;
        while(phrase_s >> word) {
            if(global_index[word][filename].empty()) {
                flag = false;
                break;
            }
        }
        if(flag) {
            int freq = lol(global_index, phrase, filename);
            if(freq > 0) {
                results.push_back({filename, freq});
                total = true;
            }
        }
    }

    if(!total) {
        cout << "No matches found\n";
        return;
    }

    sort(results.begin(), results.end(), [](auto &a, auto &b){
        return a.second > b.second;
    });

    cout << "Phrase found in (sorted by frequency):\n";
    for(auto &r : results) {
        cout << r.first << " (" << r.second << ")\n";
    }
}

int main() {
    unordered_map<string, unordered_map<string, vector<int>>> global_index;

    Trie trie;
    for(int j=3; j>=0; j--) {
        string filename = "sample" + to_string(j+1) + ".txt";
        ifstream file(filename);
        if(!file) {
            cout << "Could not open " << filename << endl;
            continue;
        }

        string currline, currword;
        int i = 1;
        while(getline(file, currline)) {
            stringstream s(currline);
            while(s >> currword) {
                currword = norm(currword);
                if(currword.size()!=0){
                    global_index[currword][filename].push_back(i);
                    trie.insert(currword);
                    i++;
                }
            }
        }
    }

    while(true) {
        cout << "\n1. Search Word\n2. Search Phrase\n3. Autocompete\n4. Exit\nChoice: ";
        int ch; cin >> ch; cin.ignore();
        if(ch==3) break;

        if(ch==1) {
            string word;
            cout<<"Enter word: ";
            getline(cin, word);
            word = norm(word);
            word_search(global_index, word);
        }
        else if(ch==2) {
            string phrase;
            cout<<"Enter phrase: ";
            getline(cin, phrase);
            phrase_search(global_index, phrase);
        }
        else if(ch==3){
            string word;
            cout<<"Enter Word For Autocomplete:";
        }
    }

    return 0;
}
