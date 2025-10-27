#include<bits/stdc++.h>
#include<fstream>
#include<sstream>
#include<ctype.h>
using namespace std;
//this is a list of articles,prepositions,conjunctions,pronouns which nlms mostly ignore
unordered_set<string>non_imp_words={"a", "an", "the", "and", "or", "but", "if", 
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
//fucntion for converting the word to lower case and also removing any punctuations if present
string norm(string &curr){
    int n = curr.size();
    for(char &c : curr){
        c = tolower(c);
    }
    if(curr[n-1]=='.' || curr[n-1]==',' || curr[n-1]=='?' ||
    curr[n-1]=='!' || curr[n-1]==':' || curr[n-1]==';'){
        curr.pop_back();
    }
    n = curr.size();
    if(curr[0]=='\"' || curr[0]=='\''){
        curr = curr.substr(1);
    }
    n = curr.size();
    if(curr[n-1]=='\"' || curr[n-1]=='\''){
        curr.pop_back();
    }
    n = curr.size();
    if(curr[n-1]=='.' || curr[n-1]==',' || curr[n-1]=='?' ||
    curr[n-1]=='!' || curr[n-1]==':' || curr[n-1]==';'){
        curr.pop_back();
    }
    return curr;
        
}

int main(){
    unordered_map<string,unordered_map<string,vector<int>>>global_index;//map of maps(this is the kinda stuff actually used in search engines)
    //unordered_map<string,vector<int>>m[4]; //array of 4 maps for the words with key as the word and value as the vector which contains the positions of the word
    for(int j=3;j>=0;j--){
    string filename = "sample" + to_string(j+1) + ".txt";
    ifstream file(filename);
    if(!file)cout<<"file no open :(";
    string currline,currword;
    int i=1;
    while(getline(file,currline)){   //reads a full line from the current file and stores it in currline variable
          stringstream s(currline); //stringstream breaks data by spaces making it ez to read
          while(s>>currword){ //reads words separated by spaces, tabs, newlines one at a time from the stringstream
                currword = norm(currword);
                if(currword.size()!=0){
                 global_index[currword][filename].push_back(i);
                 i++;
                }
          }
    }

}
    /*unordered_map<string,unordered_map<string,vector<int>>>global_index;
    for(int i=3;i>=0;i--){
        string filename = "sample" + to_string(i+1) + ".txt";
        for(auto word:m[i]){
            vector<int>curr_file_locs = word.second;
            string curr_word = word.first;
            global_index[curr_word][filename]=curr_file_locs;
        }
    }*/
    
    /*for(auto curr:m){
        cout<<curr.first<<" ";
        for(int i:curr.second){
            cout<<i<<" ";
        }
        cout<<endl;
    }*/
   cout<<"enter word"<<endl;
   string lol;
   cin>>lol;
   /*for(int i=0;i<4;i++){
     cout<<"sample" + to_string(i+1) + ".txt:"<<" "<<m[i][lol].size()<<" matches"<<endl;
   }*/
   if(global_index.find(lol)==global_index.end())cout<<"0 Matches Found"<<endl;
   for(auto inside_map : global_index[lol]){
    cout<<inside_map.first<<":"<<" ";
    vector<int>curr_locs = inside_map.second;
    cout<<curr_locs.size()<<" matches\n";
   }

}