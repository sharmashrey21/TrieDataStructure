/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:   s276shar@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Fall 2106
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <string>
#include <cstring>
#include <cctype>
#include "ece250.h"

class Trie;

class Trie_node {
	private:
		Trie_node **children;
		bool is_terminal;
		static int const CHARACTERS = 26;


	public:
		Trie_node();
		Trie_node *child( int ) const;
		int converttolower(std::string const &, int depth) const;
		bool member( std::string const &, int ) const;
		bool insert( std::string const &, int );
		bool erase( std::string const &, int, Trie_node *& );

		void clear();

		friend class Trie;

};

Trie_node::Trie_node():
children( nullptr ),
is_terminal( false ) {
	// empty constructor
}

Trie_node *Trie_node::child( int n ) const {
	if ( children == nullptr ) {
		return nullptr;
	} else {
		return children[n];
	}
}

bool Trie_node::member( std::string const &str, int depth ) const {
	std::string finalstr = str; //this method is borrowed from stackoverflow, converts to lowercase
	std::transform(finalstr.begin(), finalstr.end(), finalstr.begin(), ::tolower);

	if (str.length() == depth){ //if the length are the same, we know we have reached the end, so we can return true/false
		return is_terminal;
	}
	if (children == nullptr){ //if the array of children dont exist for a trie node, we return false
		return false;
	}
	int index = finalstr[depth] - int('a'); //need to find the index compared to lowercase
	if(children[index] != nullptr){ //if at index where we have trie node is letter we need, we go to next letter and recursion
		depth++;
		return children[index] -> member(finalstr, depth);
	}
	return false; //return false otherwise
}

bool Trie_node::insert( std::string const &str, int depth ) {
	std::string finalstr = str; //this method is borrowed from stackoverflow, converts to lowercase
	std::transform(finalstr.begin(), finalstr.end(), finalstr.begin(), ::tolower);
	//needed values for the code ahead
	int index = finalstr[depth] - int('a');
	int length = str.length();
	if(depth == length){ //we have arrived to the end of the word, finally done
		is_terminal = true;
		return true;
	}
	else if(children == nullptr){ //no array of children
		children = new Trie_node*[CHARACTERS]; //make a new trienode which is an array of 26
		for (int i = 0; i < CHARACTERS; i++){
			children[i] = nullptr; //make each index in array = null ptr
		}
		children[index] = new Trie_node(); //the index we need, needs to point to another tri-node
	}
	else if(children[index] == nullptr){ //if at index need, it is null, we make new trienode
		children[index] = new Trie_node();
	}
	depth++;//else increment depth
	return children[index]->insert(finalstr, depth); //call function recursively on next letter
}

 bool Trie_node::erase( std::string const &str, int depth, Trie_node *&ptr_to_this ) {
	std::string finalstr = str; //this method is borrowed from stackoverflow, converts to lowercase
	std::transform(finalstr.begin(), finalstr.end(), finalstr.begin(), ::tolower);
	//needed values for the code ahead
	//hardest method to implement
 	int index = finalstr[depth] - int('a');
 	int length = str.size();
 	//base case
 	if(is_terminal && length == depth){  //if at end of word
 		if(children == nullptr){ //and if no array of children exist
			ptr_to_this = nullptr; //make the current node(end of word) point to nullptr
 			return true;
		}
 		else if(children != nullptr){ //if array of children does exist
 			is_terminal = false; //not is_terminal
		}
 		return true; //return true other wise
 	}
 	//recursion takes place here
	children[index]->erase(finalstr, depth+1, ptr_to_this); //perform erase on next letter
		for(int i = 0; i < CHARACTERS; ++i){
 			if(children[i] != nullptr){ 
				return true;
 			}
 		}
 		delete[] children; //delete these things, free memory also
 		delete[] ptr_to_this;
 		children = nullptr;
 		ptr_to_this = nullptr;
 }

void Trie_node::clear() {
	//return exists so that we can return to earlier node
	if (children == nullptr) {
		delete[] this;
	return;
	}
	for (int i = 0; i < CHARACTERS; i++){
		if (children[i] != nullptr){
			children[i]->clear();
		}
	}
	delete[] children;
	delete this;
	return;
}

#endif