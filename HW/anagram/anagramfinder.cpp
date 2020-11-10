/*******************************************************************************
 * Name        : anagramfinder.cpp
 * Author      : Brandon Cao
 * Date        : November 11, 2019
 * Description : Finds the largest group or groups of words that are anagrams of one another.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>

using namespace std;

bool sortt(string a, string b) {
    return a < b;
}

inline string to_lower_str(string &str) {
    string result;
    for (auto &c : str) {
        result += tolower(c);
    }
    return result;
}

inline bool isStringAlpha(string str) {
    for(unsigned int j=0; j < str.size();++j) {
        if(isalpha(str[j]) == false) {
            return false;
        }
    }
    return true;
}

bool sort_ascii(const vector<string>& v1, const vector<string>& v2) { 
    return v1[0] < v2[0]; 
} 

vector<vector<string>> findAnagrams (vector<string>& word_list, unsigned int &amt_words) {
    unordered_map<string, unsigned int> hash_map;
    vector<vector<string>> result;
    unsigned int index = 0;

    for(auto str:word_list) {
        if(isStringAlpha(str) == false)
           continue;
        string word = str;
        word = to_lower_str(word);
        sort(word.begin(), word.end());

        if(hash_map.find(word) != hash_map.end()) { 
            result[hash_map[word]].push_back(str);
            vector<string> ve = result[hash_map[word]];
            if(ve.size() > amt_words) {
               amt_words = ve.size();
            }
        }
        else { 
            hash_map[word] = index++;
            vector<string> temp;
            temp.push_back(str);
            result.push_back(temp);
        }
    }
    return result;
}

vector<vector<string>> findAnagrams_dict(ifstream &dict, unsigned int &amt_words) {
    unordered_map<string, unsigned int> hash_map;
    vector<vector<string>> result;
    unsigned int index = 0;
    string word;

    while(std::getline(dict, word)) {
        string sorted_word = word;
        sorted_word = to_lower_str(sorted_word);
        sort(sorted_word.begin(), sorted_word.end());

        if(hash_map.find(sorted_word) != hash_map.end()) { // String already in hashmap
            result[hash_map[sorted_word]].push_back(word); // Push word into sorted key
            vector<string> ve = result[hash_map[sorted_word]];
            if(ve.size() > amt_words) { // Checks which key has more words
               amt_words = ve.size();
            }
        }
        else { // String not in hashmap. New word
            hash_map[sorted_word] = index++;
            vector<string> temp;
            temp.push_back(word);
            result.push_back(temp);
        }
    }
    // Sorts anagrams in increasing order
    sort(result.begin(), result.end(), sort_ascii); 
    return result;
}

int main(int argc, char *argv[]) {
    unsigned int max_anagram = 1;
    bool file = false;

    if(argc != 2) {
        cerr<<"Usage: ./anagramfinder <dictionary file>"<<endl;
        return 1;
    }
    
    ifstream readfile(argv[1]);
    if(readfile.fail()) {
        cerr<<"Error: File " << "\'" << argv[1] << "\'" << " not found."<<endl;
        return 1;
    }
    
    vector<vector<string>> result;
    if(file == false) {
        string str;
        vector<string> dictVector;
        while (std::getline(readfile, str)) {
            if(str.size() > 0) {
                dictVector.push_back(str);
            }
        }
        sort(dictVector.begin(), dictVector.end());
        result = findAnagrams(dictVector, max_anagram);
        readfile.close();
    } else {
        result = findAnagrams_dict(readfile, max_anagram);
        readfile.close();
    }

    if(max_anagram == 1) {
        cout<<"No anagrams found."<<endl;
        return 0;
    }
 
    cout<<"Max anagrams: "<<max_anagram<<endl;
    for(auto &vec:result) {
       if(vec.size() > 1) {
           if(vec.size() ==  max_anagram) {
               sort(vec.begin(), vec.end(), sortt);
               for(auto const& res:vec) {
                   cout<<res<<endl;
               }
               cout<<endl;
           }
       }
    }
    return 0;
}
