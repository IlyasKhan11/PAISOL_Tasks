#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<unordered_map>
using namespace std;

class TrieNode {
public:
  unordered_map<char, TrieNode*> children;
  bool isWord;
  vector<string> suggestions;

  TrieNode() : isWord(false) {}
};

class SpelChecker{
public:
    TrieNode* root;
    SpelChecker(){
        root= new TrieNode();
    }

    void insert_word(const string& word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.count(c) == 0) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        current->isWord = true;
    }




    void loadDictonary(string fileName){
        ifstream file(fileName);
        if(!file.is_open()){
            cout<<"Could not open given dictonary file, please try again"<<endl;
            return;
        }

        string word;
        while(getline(file,word)){
            insert_word(word);
        }

        file.close();
    }



  bool is_word_correct(string word) {
    TrieNode* current = root;
    for (char c : word) {
      if (current->children.count(c) == 0) {
        return false;
      }
      current = current->children[c];
    }
    return current->isWord;
  }


  void find_suggestions(TrieNode* node, const string& remaining_word, vector<string>& suggestions, const string& current_word) {
    if (remaining_word.empty()) {
      if (node->isWord) {
        suggestions.push_back(current_word);
      }
      return;
    }
    for (auto& entry : node->children) {
      find_suggestions(entry.second, remaining_word.substr(1), suggestions, current_word + entry.first);
    }
  }


  vector<string> suggest_corrections(const string& word) {
    vector<string> suggestions;
    TrieNode* current = root;
    for (size_t i = 0; i < word.size(); ++i) {
      if (current->children.count(word[i]) == 0) {
        for (char c = 'a'; c <= 'z'; ++c) {
          if (c != word[i] && current->children.count(c) > 0) {
            find_suggestions(current->children[c], word.substr(i + 1), suggestions, word.substr(0, i) + c + word.substr(i + 1));
          }
        }
        return suggestions;
      }
      current = current->children[word[i]];
      if (current->isWord) {
        suggestions.push_back(word.substr(0, i + 1));
      }
    }

    find_suggestions(current, "", suggestions, word);
    return suggestions;
  }





};









// Function to check spelling in a text file
void check_spelling_in_file(string filename, SpelChecker checker) {
  ifstream file(filename);
  if (!file.is_open()) {
    cout << "Error: Could not open file '" << filename << "'" << endl;
    return;
  }

  string line;
  int line_number = 1;
  while (getline(file, line)) {
    stringstream ss(line); 
    string word;

    while (ss >> word) {
      string clean_word;
      for (char c : word) {
        if (isalpha(c)) {
          clean_word += tolower(c); 
        }
      }

      if (!checker.is_word_correct(clean_word)) {
        vector<string> suggestions = checker.suggest_corrections(clean_word);
        cout << "Line " << line_number << ": Potential misspelling '" << word << "'" << endl;
        if (!suggestions.empty()) {
          cout << "Did you mean: ";
          for (const string& suggestion : suggestions) {
            cout << suggestion << ", ";
          }
          cout << endl;
        } else {
          cout << "No suggestions found." << endl;
        }
      }
    }
    line_number++;
  }

  file.close();
}


int main() {

  SpelChecker checker;
  checker.loadDictonary("Dictonary.txt"); 

  string filename;
  cout << "Enter the text file name: ";
  getline(cin, filename);

  check_spelling_in_file(filename, checker);

  return 0;
}