#include <vector>
#include <iostream>
#include <typeinfo>
#include <string>
#include <unordered_map>

#include "dictrie.h"

using namespace std;
/*
 Author: imdc- Somang Nam

 The dicTrie is to help handling the dictionary parsed into Key-Value form,
 where Key : the stenoKey combination and
 the Value : English/human readable sentence/word stored.

 This class uses the dictrie.h as the Node definition, where it provides Trie data structure.
 Each level, the node contains hashmap of characters so that the search can be within
 O(n) where n is the length of stenWord provided.

 The memory usage can grow bigger however the stenograph keyset only allows no more than 24. (estimates.)

*/
dicTrie::dicTrie(){
	/* constructor, initializes the root node.*/
	root = new Node();
}

void dicTrie::addWord(string stenWord, string val){
	/* Given a sten-combination, this method adds value with given stenWord node into Trie.*/
	Node* currentNode = root;
	if (stenWord.length() == 0){
		currentNode->setEnd();
		return;
	}
	/* for each character key in given steno-combination,
	 * check if the key is already included or not. */
	for (int i = 0; i < stenWord.length(); i++){
		Node* child = currentNode->findChild(stenWord[i]);
		if (child != NULL){ // if there exists a key character,
			currentNode = child; // go to that child level
		}else{ // when child is NULL, create a new Node.
			Node* tmp = new Node();
			currentNode->appendChild(stenWord[i], tmp); // attach the children
			currentNode = tmp;
		}
		if (i == stenWord.length() - 1){ // is this the last character?
			currentNode->setValue(val); // then add the value (english word/sentence)
			currentNode->setEnd(); // this is the end of given key combination.
		}
	}
}

string dicTrie::getWord(string s){
	/* Search method, to find the value under given stenWord combination.*/
	Node* currentNode = root; // start from the root.	
	while (currentNode != NULL)	{ // While there exists a node
		for (int i = 0; i < s.length(); i++){ // Search through the Trie, by character from the Sten Word.
			Node* childNode = currentNode->findChild(s[i]); // Look for the branch/Node with the given character.
			if (childNode == NULL){	return NULL; } // Return Null, if doesn't exist in the Trie.
			currentNode = childNode;// Or else move to the child.
		}
		if (currentNode->isEnd()){ // If the node reaches to the leaf
			return currentNode->getValue(); // Look for the value stored in.
		}
	}
	return NULL; // if root is null then, return null.
}

void dicTrie::deleteWord(string s) {
	Node* currentNode = root;
	if (currentNode != NULL) { // While there exists a node
		for (int i = 0; i < s.length(); i++) { // Search through the Trie, by character from the Sten Word.
			Node* childNode = currentNode->findChild(s[i]); // Look for the branch/Node with the given character.
			if (childNode == NULL) { break; }
			currentNode = childNode;			
		}
		if (currentNode->isEnd()) { // If the node reaches to the leaf
			currentNode->setValue("");
		}
	}
}

void dicTrie::displayTrie() {
	Node* currentNode = root;
	if (currentNode != NULL) {
		std::unordered_map<char, Node*> childrenNode = currentNode->getChildren(); // [a,b,c,d,e ...]
		std::vector<char> keys;
		keys.reserve(childrenNode.size());
		std::vector<Node*> vals;
		vals.reserve(childrenNode.size());

		for (auto kv : childrenNode) {
			keys.push_back(kv.first);
			vals.push_back(kv.second);
		}

		for (auto it = childrenNode.begin(); it != childrenNode.end(); ++it){
			char c = it->first;
			std::cout << "[" << c << ":" << childrenNode[c]->getValue() << "]" << endl;
			Node* childNode = currentNode->findChild(c);
			if (childNode == NULL) { break; }
			currentNode = childNode;
		}
		
	}
}