#pragma once

#include <vector>
#include <list>
#include <algorithm>
#include <optional>
#include <memory>

#include "hash.h"

/*~~~~~~~~~~~Preprocessor Directives to clean the code a bit~~~~~~~~~~~*/
template<class KEY, class ITEM>
#define RETURN_TYPE std::optional<std::reference_wrapper<ITEM>>
#define RWRAPPER(x) std::reference_wrapper(x)
#define TABLE_TEMPLATE std::list<std::pair<KEY, std::shared_ptr<ITEM>>>
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class HashTable {
private:
	std::vector<TABLE_TEMPLATE> table;		//Vector of list, where list is of type pair, where pair has key and value
	int current_size;					   //Current size, had to keep it since resizing vector effects size and max_size

public:
	HashTable(int size);				 //Param Cstr. inits table size with next prime of size passed to it
	
public:
	bool insert(KEY key, const ITEM& item);		//Inserts key and value* pair into the vector[i].list, if not already present
	bool remove(KEY key);					   //Removes a value with the given key if it exists

	void print();							  //Prints hashtable

	//Overloaded operator to get value at a certain key
	RETURN_TYPE operator[](KEY key) {

		//hashes key, and returns index
		int index = hash(key);
		//checks if item exists
		auto iter = has_item(key, index);
		//if it does returns it
		if (iter != table[index].end())
			return std::make_optional(RWRAPPER(*((*iter).second)));
		//else "nothing" is returned
		return std::nullopt;
	}


private:
	//iterates the list at given index to check if it has the item
	auto has_item(KEY key, int index) {
		return std::find_if(table[index].begin(), table[index].end(),
			[&key](std::pair<KEY, std::shared_ptr<ITEM>> item) {
			return (item.first == key);
		});
	}
	/*Helper funcs used by Cstr.*/
	bool is_prime(int n);
	int next_prime(int n);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//hashes a key using hashing algorithm based on folding and bitwise operations and universal hash function
	int hash(KEY key) {
		return (ostl::hash(key) % table.size());
	}
};

//Param Cstr.
template<typename KEY, typename ITEM>
HashTable<KEY, ITEM>::HashTable(int size) {
	table.resize(next_prime(size));
}

/*~~~~~~~~~~~Helper funcs for Param Cstr.~~~~~~~~~~~*/
template<typename KEY, typename ITEM>
bool HashTable<KEY, ITEM>::is_prime(int n) {
	for (int i = 2; i <= n / 2; i++) {
		if (n % i == 0)
			return false;
	}
	return true;
}

template<typename KEY, typename ITEM>
int HashTable<KEY, ITEM>::next_prime(int n) {

	if (n == 2)
		return n;

	while (!is_prime(++n))
		return n;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<typename KEY, typename ITEM>
bool HashTable<KEY, ITEM>::insert(KEY key, const ITEM& item) {
	int index = hash(key);	//finds index

	if (has_item(key, index) != table[index].end())	//if not already present
		return false;
	//inputs data
	table[index].push_back(std::make_pair(key, std::make_shared<ITEM>(item)));
	current_size++;
	return true;
}

template<typename KEY, typename ITEM>
bool HashTable<KEY, ITEM>::remove(KEY key) {
	int index = hash(key);		//finds index

	if (table[index].size() == 0)	//if list empty
		return false;

	auto iter = has_item(key, index);	//if not present
	if (iter == table[index].end())
		return false;

	table[index].erase(iter);		//removes if present
	current_size--;
	return true;
}

template<typename KEY, typename ITEM>
void HashTable<KEY, ITEM>::print() {
	int k = 1;
	for (auto i = table.begin(); i != table.end(); ++i) {
		for (auto j = (*i).begin(); j != (*i).end(); ++j) {
			std::cout << "H# " << k << "-> " << *((*j).second) << "\n\n";
		}
		k++;
	}
}