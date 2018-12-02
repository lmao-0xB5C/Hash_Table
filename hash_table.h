#pragma once

#include <vector>
#include <list>
#include <algorithm>
#include <optional>
#include <memory>

template<class KEY, class ITEM>
#define RETURN_TYPE std::optional<std::reference_wrapper<ITEM>>
#define RWRAPPER(x) std::reference_wrapper(x)
#define TABLE_TEMPLATE std::list<std::pair<KEY, std::shared_ptr<ITEM>>>

class HashTable {
private:
	std::vector<TABLE_TEMPLATE> table;
	int current_size;

public:
	HashTable(int size);
	
public:
	bool insert(KEY key, const ITEM& item);
	bool remove(KEY key);

	void print();

	RETURN_TYPE operator[](KEY key) {

		int index = hash(key);
		auto iter = has_item(key, index);
		if (iter != table[index].end())
			return std::make_optional(RWRAPPER(*((*iter).second)));

		return std::nullopt;
	}


private:
	auto has_item(KEY key, int index) {
		return std::find_if(table[index].begin(), table[index].end(),
			[&key](std::pair<KEY, std::shared_ptr<ITEM>> item) {
			return (item.first == key);
		});
	}

	bool is_prime(int n);
	int next_prime(int n);

	int hash(KEY key) {
		int val = 3217 * key + 4423;
		return (((val ^ ((val << 3) & (val >> 5))) % 1257787) % table.size());
	}
};

template<typename KEY, typename ITEM>
HashTable<KEY, ITEM>::HashTable(int size) {
	table.resize(next_prime(size));
}

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

template<typename KEY, typename ITEM>
bool HashTable<KEY, ITEM>::insert(KEY key, const ITEM& item) {
	int index = hash(key);

	if (has_item(key, index) != table[index].end())
		return false;

	table[index].push_back(std::make_pair(key, std::make_shared<ITEM>(item)));
	current_size++;
	return true;
}

template<typename KEY, typename ITEM>
bool HashTable<KEY, ITEM>::remove(KEY key) {
	int index = hash(key);

	if (table[index].size() == 0)
		return false;

	auto iter = has_item(key, index);
	if (iter == table[index].end())
		return false;

	table[index].erase(iter);
	current_size--;
	return true;
}

template<typename KEY, typename ITEM>
void HashTable<KEY, ITEM>::print() {
	int k = 1;
	for (auto i = table.begin(); i != table.end(); ++i) {
		for (auto j = (*i).begin(); j != (*i).end(); ++j) {
			std::cout << "H" << k << "->" << *((*j).second) << "\n\n";
		}
		k++;
	}
}