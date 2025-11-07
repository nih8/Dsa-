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

    void splitninsert(string words){
        string word="";
        int n=words.length()
        for(int i=0;i<n;i++){
            char ch=words[i];

            if(isletter(tolower(ch))){
                word+=tolower(ch);
            }
            else{
                if(word!=""){
                    insert(word); 
                    word="";  
                }
            }
        }

        if(word!=""){
            insert(word);
        }
    }

    void display(TrieNode* node,string st){
        if(node==NULL) 
        return;

        if(node->isend){
            cout<<prefix<<"count: "<<node->cnt<<endl;
        }

        for(int i=0;i<26;i++){
            if(node->next[i]!=NULL){
                char ch='a'+i;
                display(node->next[i],st+ch);
            }
        }
    }

    void show(){
        cout<<"\nWords stored in Trie:\n";
        display(root,"");
    }
};



