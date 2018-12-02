#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <optional>
#include <memory>

template<class ITEM>
#define RETURN_TYPE std::optional<std::reference_wrapper<ITEM>>
#define RWRAPPER(x) std::reference_wrapper(x)

class PriorityQueue {
private:
	std::vector<std::shared_ptr<ITEM>> queue;
	std::shared_ptr<ITEM> min_item;


public:
	PriorityQueue();

	void print() {
		for (int i = 0; i < queue.size(); i++) {
			std::cout << *queue[i] << " ";
		}
	}

public:
	void insert(const ITEM& item);
	RETURN_TYPE extract_max();

	int max_child(int i);

	inline RETURN_TYPE get_max() { return (!isEmpty()) ? std::make_optional(RWRAPPER(*(queue[0]))) : std::nullopt; }

	inline RETURN_TYPE get_min() { return (min_item != nullptr) ? std::make_optional(RWRAPPER(*min_item)) : std::nullopt; }

	inline int size() { return queue.size(); }

	void build_queue(const std::vector<std::shared_ptr<ITEM>>& arr);

private:
	inline bool isEmpty() { return (queue.size() == 0); }
	void reheap_up(int current, int end);
	void reheap_down(int current, int end);
};

template<typename ITEM>
PriorityQueue<ITEM>::PriorityQueue() : min_item(nullptr) {}

template<typename ITEM>
void PriorityQueue<ITEM>::reheap_up(int current, int end) {
	if (current > end) {
		int parent = (current - 1) / 2;
		if (*queue[current] > *queue[parent])
			std::swap(queue[current], queue[parent]);
		reheap_up(parent, end);
	}
}

template<typename ITEM>
void PriorityQueue<ITEM>::reheap_down(int current, int end) {
	if ((current * 2 + 1) < queue.size()) {

		int m_child = max_child(current);

		if (*queue[m_child] > *queue[current])
			std::swap(queue[m_child], queue[current]);
		reheap_down(m_child, end);
	}
}

template<typename ITEM>
int PriorityQueue<ITEM>::max_child(int i) {
	if ((2 * i + 2) >= queue.size())
		return (2 * i + 1);

	return (*queue[2 * i + 1] > *queue[2 * i + 2]) ? (2 * i + 1) : (2 * i + 2);
}

template<typename ITEM>
void PriorityQueue<ITEM>::insert(const ITEM& item) {

	if (isEmpty())
		min_item = std::make_shared<ITEM>(item);
	else if (*min_item > item)
		min_item = std::make_shared<ITEM>(item);

	queue.push_back(std::make_shared<ITEM>(item));
	reheap_up(queue.size() - 1, 0);
}

template<typename ITEM>
RETURN_TYPE PriorityQueue<ITEM>::extract_max() {

	ITEM temp = *queue[0];
	queue[0] = queue[queue.size() - 1];
	queue.pop_back();
	reheap_down(0, queue.size() - 1);
	return std::make_optional(RWRAPPER(temp));
}

template<typename ITEM>
void PriorityQueue<ITEM>::build_queue(const std::vector<std::shared_ptr<ITEM>>& arr) {
	for (int i = 0; i < arr.size(); i++)
		queue.push_back(arr[i]);

	for (int i = arr.size() / 2 - 1; i >= 0; i--)
		reheap_down(i, queue.size() - 1);
}