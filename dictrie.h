#pragma once
#define DICTRIE_H

#include <string>
#include <unordered_map>
using namespace std;

class Node {
	public:
		Node() {
			wordEnd = false;
		}	
	
		std::string getValue() {
			return value;
		}
		void setValue(std::string stenWord) {
			value = stenWord;
		}		

		bool isEnd() {
			return wordEnd;
		}
		void setEnd() {
			wordEnd = true;
		}

		Node* findChild(char c){
			return childrenNode[c];
		}
		void appendChild(char key, Node* child) {
			childrenNode[key] = child;
		}
		std::unordered_map<char, Node*> getChildren() {
			return childrenNode;
		}

	private:
		std::string value;
		std::unordered_map<char, Node*> childrenNode;
		bool wordEnd;
};

class dicTrie {
	public:
		dicTrie();
		void addWord(std::string stenWord, std::string val);
		std::string getWord(std::string stenWord);
		void deleteWord(std::string stenWord);
		void dicTrie::displayTrie();

	private:
		Node* root;
};