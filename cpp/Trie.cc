#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;

// Implemented using pointers similar to what's learned in CS138
// Will redo later with OOP

struct Node {
  unordered_map<char, Node*> children;
  bool eow = false;
  char val;
};

struct Trie {
  Node* root;
};

// Forward declarations
void initTrie(Trie& t);
void addWord(Trie& t, string word);
void add(Node* n, string word);
bool containsWord(Trie& t, string word);
bool contains(Node* n, string word);
int countWord(Trie& t, string word);
int countChildren(Node* n);

// Functions
void initTrie(Trie& t){
  t.root = new Node;
  t.root -> val = '\0';
}

void addWord(Trie& t, string word){
  add(t.root, word);
}

void add(Node* n, string word){
  if(word.length() == 0){
    n -> eow = true;
    return;
  } else {
    if(n -> children.find(word.at(0)) == n -> children.end()){
      n -> children[word.at(0)] = new Node;
      n -> children[word.at(0)] -> val = word.at(0);
    }
    add(n -> children[word.at(0)], word.substr(1, word.length() - 1));
  }
}

bool containsWord(Trie& t, string word){
  return contains(t.root, word);
}

bool contains(Node* n, string word){
  if(word.length() == 0){
    return true;
  } else {
    if(n -> children.find(word.at(0)) == n -> children.end()){
      return false;
    } else {
      return contains(n -> children[word.at(0)], word.substr(1, word.length() - 1));
    }
  }
}

int countWord(Trie& t, string word){
  Node* n = t.root;
  for(int i = 0; i < word.length(); i++){
    if(n -> children.find(word.at(i)) == n -> children.end()){
      return 0;
    } else {
      n = n -> children[word.at(i)];
    }
  }
  return countChildren(n);
}

int countChildren(Node* n){
  int sum = 0;
  if(n -> children.size() == 0){
    sum += 1;
  } else {
    if(n -> eow){
      sum += 1;
    }
    for(auto it = n -> children.begin(); it != n -> children.end(); ++it){
      sum += countChildren(it -> second);
    }
  }
  return sum;
}

int main(){
  Trie t;
  initTrie(t);
  addWord(t, "cat");
  addWord(t, "card");
  addWord(t, "car");
  addWord(t, "dog");
  cout << countWord(t, "ca") << endl;
}