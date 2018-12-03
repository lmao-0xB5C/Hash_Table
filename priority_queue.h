#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <optional>
#include <memory>

/*~~~~~Preprocessor Directives used to clean the code a bit~~~~~*/
template<class ITEM>
#define RETURN_TYPE std::optional<std::reference_wrapper<ITEM>>
#define RWRAPPER(x) std::reference_wrapper(x)
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class PriorityQueue {
private:
	std::vector<std::shared_ptr<ITEM>> queue;	//Queue
	std::shared_ptr<ITEM> min_item;			   //To find min in O(1)


public:
	PriorityQueue();						//Default Cstr.

public:
	void insert(const ITEM& item);		   //Inserts given item
	RETURN_TYPE extract_max();			  //Removes max item

	//Returns max if present
	inline RETURN_TYPE get_max() { return (!isEmpty()) ? std::make_optional(RWRAPPER(*(queue[0]))) : std::nullopt; }
	//Returns min if present
	inline RETURN_TYPE get_min() { return (min_item != nullptr) ? std::make_optional(RWRAPPER(*min_item)) : std::nullopt; }

	//returns queue size
	inline int size() { return queue.size(); }
	//checks if queue is empty
	inline bool isEmpty() { return (queue.size() == 0); }
	//builds a queue from a vector of unsorted elements
	void build_queue(const std::vector<std::shared_ptr<ITEM>>& arr);

private:
	//Helps in reheap_down
	int max_child(int i);
	/*~~~~~To maintain heap property~~~~~*/
	void reheap_up(int current, int end);
	void reheap_down(int current, int end);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
};

//Default Cstr.
template<typename ITEM>
PriorityQueue<ITEM>::PriorityQueue(): min_item(nullptr) {}

template<typename ITEM>
void PriorityQueue<ITEM>::reheap_up(int current, int end) {
	if (current > end) {	//while not end
		int parent = (current - 1) / 2;	//find parent
		if (*queue[current] > *queue[parent])	//check if current is bigger
			std::swap(queue[current], queue[parent]);	//swap
		reheap_up(parent, end);	//repeat
	}
}

template<typename ITEM>
void PriorityQueue<ITEM>::reheap_down(int current, int end) {
	if ((current * 2 + 1) < queue.size()) {	//while left child is present

		int m_child = max_child(current);	//finds index of max_child

		if (*queue[m_child] > *queue[current])	//if max_child bigger than parent
			std::swap(queue[m_child], queue[current]);	//swap
		reheap_down(m_child, end);	//repeat
	}
}

template<typename ITEM>
int PriorityQueue<ITEM>::max_child(int i) {
	if ((2 * i + 2) >= queue.size())	//if only left child
		return (2 * i + 1);

	return (*queue[2 * i + 1] > *queue[2 * i + 2]) ? (2 * i + 1) : (2 * i + 2);	//else compare and return max
}

template<typename ITEM>
void PriorityQueue<ITEM>::insert(const ITEM& item) {

	if (isEmpty())
		min_item = std::make_shared<ITEM>(item);	//sets min directly if first time
	else if (*min_item > item)
		min_item = std::make_shared<ITEM>(item);	//sets min by comparing otherwise

	queue.push_back(std::make_shared<ITEM>(item));	//adds item* to vector
	reheap_up(queue.size() - 1, 0);					//to maintain heap property
}

template<typename ITEM>
RETURN_TYPE PriorityQueue<ITEM>::extract_max() {

	ITEM temp = *queue[0];					//stores max element
	queue[0] = queue[queue.size() - 1];	    //moves last element to the top
	queue.pop_back();						//removes last
	reheap_down(0, queue.size() - 1);		//to maintain heap property
	return std::make_optional(RWRAPPER(temp));
}

template<typename ITEM>
void PriorityQueue<ITEM>::build_queue(const std::vector<std::shared_ptr<ITEM>>& arr) {
	for (int i = 0; i < arr.size(); i++)
		queue.push_back(arr[i]);	//copies vector

	for (int i = arr.size() / 2 - 1; i >= 0; i--)
		reheap_down(i, queue.size() - 1);	//reheaps
}