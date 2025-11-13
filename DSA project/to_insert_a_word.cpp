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
    // created for the alphabets as all words will have 26 paths to go
    TrieNode* next[26]; 
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

    //this code to convert the uppercase to lowercase
    char tolower(char ch){
        if(ch>='A' && ch<='Z'){
            ch=ch-'A'+'a';
        }
        return ch;
    }

    //to check if we are having alphabets or not
    bool isletter(char ch){
        return(ch>='a' && ch<='z');
    }

    void insert(string word){
        TrieNode* curr=root;
        int n=word.size();
        //to get each alphabet in the word
        for(int i=0;i<n;i++) {
            char c=tolower(word[i]);
            // to ignore any other things except the alphabets
            if(!isletter(c)){
                continue;
            }
            int ind=c-'a';
            if(curr->next[ind]==NULL){
                curr->next[ind]=new TrieNode();
                // if we cannot find the word then we will create a new node
            }
            curr=curr->next[ind];
        }
      
        curr->isend= true;
        curr->cnt++;
    }

    //this part is to split the words
    void splitninsert(string words){
        string word="";
        //reading the whole word
        int n=words.length();
        for(int i=0;i<n;i++){
            char ch=words[i];

            //checking if the word is lower or not
            if(isletter(tolower(ch))){
                word+=tolower(ch);
            }
            else{
                //if the word is not there and there are other things like number or symobol then the word is ended
                if(word!=""){
                    insert(word); 
                    word="";  
                }
            }
        }

        //if any words left then insert it
        if(word!=""){
            insert(word);
        }
    }

    //to display the words
    void display(TrieNode* node,string st){
        if(node==NULL) 
        return;

        if(node->isend){
            cout<<st<<"=>count: "<<node->cnt<<endl;
        }

        for(int i=0;i<26;i++){
            if(node->next[i]!=NULL){
                char ch='a'+i;
                display(node->next[i],st+ch);
            }
        }
    }

    //to show the words that are stored
    void show(){
        cout<<"\nWords stored in Trie:\n";
        display(root,"");
    }
};



