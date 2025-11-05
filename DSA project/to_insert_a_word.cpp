#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include <fstream>
#include <ctype.h>
#include <sstream>

using namespace std;
struct TrieNode{
    TrieeNode* next[26]; 
    bool isend; 
    int cnt; 

      TrieNode() {
        for(int i=0;i<26;i++){
            next[i]=NULL;
        }
        isend=false;
        cnt=0;
    }
};

class Trie{
public:
    TrieNode* root;

    Trie(){
        root=new TrieNode();
    }

    char tolower(char ch){
        if(ch>='A' && ch<='Z'){
            ch-='A'+'a';
        }
        return ch;
    }

    bool isletter(char ch){
        return(c>='a' && c<='z');
    }

    void insert(string word){
        TrieNode* curr=root;
        int n=word.size();
        for(int i=0;i<n;i++) {
            char c=tolower(word[i]);
            if(!isletter(c)){
                continue;
            }
            int ind=c-'a';
            if(curr->next[ind]==NULL){
                curr->next[ind]=new TrieNode();
            }
            curr=curr->next[ind];
        }
      
        curr->isend= true;
        curr->cntt++;
    }



