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

bool binary_search(vector<int>v, int pos){
    int left = 0;
    int right = v.size() -1;
    while(left<=right){
        int mid = (left+right)/2;
        if(v[mid]==pos)return true;
        else if(v[mid]<pos){
            left = mid+1;
        }
        else{
            right = mid -1;
        }
    }
    return false;
}
void word_search(unordered_map<string,unordered_map<string,vector<int>>>global_index,string word){
    if(global_index.find(word)==global_index.end()){
        cout<<"0 Matches Found"<<endl;
    }
    for(auto inside_map : global_index[word]){
    cout<<inside_map.first<<":"<<" ";
    vector<int>curr_locs = inside_map.second;
    cout<<curr_locs.size()<<" matches\n";
   }
}
int lol(unordered_map<string,unordered_map<string,vector<int>>>global_index,string phrase,string file){
    stringstream phrase_s(phrase); //converting phrase into a stringstream
    string word;int count=0;
    vector<string>p_w;
    while(phrase_s >>word){
        p_w.push_back(word);       //pushing separated words into a vector 
    }
    for(int pos : global_index[p_w[0]][file]){ //iterating through the positions of the first word in phrase
        int current = pos;
        bool match = true;
        for(int i=1;i<p_w.size();i++){
            vector<int>next_pos = global_index[p_w[i]][file];  //checking that for a current position of the word are their positions of the next words
            if(!binary_search(next_pos,current+1)){
                match = false;                         //if any position doesnt exist,break the loop and move on to the next position go the first word
                break;
            }
            current++;
        }
        if(match){
            count++;
        }
    }
    return count;
}

void phrase_search(unordered_map<string,unordered_map<string,vector<int>>>global_index,string phrase){
        
        string word;
        bool total=false;
        for(int i=0;i<4;i++){
            stringstream phrase_s(phrase);
            string filename = "sample" + to_string(i+1) + ".txt";
            bool flag = true;
            while(phrase_s >> word){
                if(global_index[word][filename].size()==0){
                flag = false;
                break;
                }
            }
            if(flag){
            cout<<filename<<" "<<lol(global_index,phrase,filename)<<endl;
            total = true;
            }
        }
        if(!total){           //output if no matches found in all files
            cout<<"No matches found\n";
        }
}

int main(){
    unordered_map<string,unordered_map<string,vector<int>>>global_index;//map of maps(this is the kinda stuff actually used in search engines)
    
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
}