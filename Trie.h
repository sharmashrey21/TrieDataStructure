/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  s276shar@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Fall 2016
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

#ifndef TRIE_H
#define TRIE_H


#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Trie_node.h"
#include "Exception.h"
#include <iostream>
#include <string>
#include <cctype>

class Trie {
	private:
		Trie_node *root_node;
		int trie_size;

	public:
		Trie();
		~Trie();

		// Accessors
		int size() const;
		bool empty() const;
		bool member( std::string const & ) const;
		Trie_node *root() const;
		// Mutators

		bool insert( std::string const & );
		bool erase( std::string const & );
		void clear();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Trie const & );
};

Trie::Trie():
root_node( nullptr ),
trie_size( 0 ) {
	// empty constructor
}

Trie::~Trie() {

}

int Trie::size() const {
	return trie_size; 
}

bool Trie::empty() const {
	if(trie_size == 0){
		return true;
	}
	else{
		return false;
	}
}

Trie_node *Trie::root() const {
	return root_node;
}

bool Trie::member( std::string const &str ) const {
	for(int i = 0; i < str.size(); i++){
 		if(!isalpha(str[i])){ //mkaing sure its a legit character
	 		throw illegal_argument();
		}
 	}
 	if (root_node == nullptr){ //cant be member in this case
		return false;
	}
	else if (trie_size == 0){ //trie doesnt even exist
		return false;
	}
	return root_node -> member(str, 0 );
}

bool Trie::insert( std::string const &str ) {
	if(member(str)){ //if string is already inside trie, return false
		return false;
	}
	for(int i = 0; i < str.size(); i++){
 		if(!isalpha(str[i])){ //needed values for the code ahead
	 		throw illegal_argument();
		}
 	}
	if(root_node == nullptr){ //make a new trie node at root
		root_node = new Trie_node();
		trie_size = 0;
	}
	trie_size++; //increase the size so we can add the string
	return root_node -> insert(str, 0 );
}	

bool Trie::erase( std::string const &str ) {
	if(!member(str)){ //if string not member, we cant remove that string
		return false;
	}
	return root_node -> erase(str, 0, root_node);
}

void Trie::clear() {
	root_node -> clear(); //clear the trie
	trie_size = 0;
}

std::ostream &operator<<( std::ostream &out, Trie const &trie ) {
	return out;
}

#endif