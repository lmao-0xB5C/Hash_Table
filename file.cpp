#include "file.h"

//Param Cstr. implementation
File::File(int id) : _ID(id) {
	current_users = std::make_shared<std::vector<std::pair<int, char>>>();
	waiting_list = std::make_shared<PriorityQueue<User>>();
}

//Copy Cstr. implementation
File::File(const File& file) : _ID(file._ID), waiting_list(file.waiting_list), current_users(file.current_users) {}

//Helps access file funcs to insert a User
void File::insert_helper(int user_id, int priority, char operation) {

	//Converts Operation char to upper case if its smaller, to prevent errors
	operation = toupper(operation);

	//CASE-1:
		//If file has no user accessing/wating for access
	if (waiting_list->size() == 0 && current_users->size() == 0)
		current_users->push_back(std::make_pair(user_id, operation));

	//CASE-2:
		//If file has users in waiting list
	else if (waiting_list->size() != 0) {
		
		//SUBCASE-1:
			//If new user and current user on the top are both READING and new user has priority > max in queue
		if (waiting_list->get_max().value().get().getPriority() < priority &&
			operation == 'R' && current_users->at(0).second == 'R') {

			current_users->push_back(std::make_pair(user_id, operation));
		}
		//SUBCASE-2:
			//If new user has less priority than max in queue, or has op = W/current has op = W
		else
			waiting_list->insert(User(user_id, priority, operation));
	}

	//CASE-3:
		//No one is waiting but some are accessing
	else if (waiting_list->size() == 0 && current_users->size() != 0) {
		//SUBCASE-1:
			//Either top user isn't W or new isn't W
		if (current_users->at(0).second != 'W' && operation == 'R')
			current_users->push_back(std::make_pair(user_id, operation));
		//SUBCASE-2:
			//Either top user is W or new is W
		else
			waiting_list->insert(User(user_id, priority, operation));
	}
}

//Calls insert_helper
void File::access_file(int user_id, int priority, char operation) { insert_helper(user_id, priority, operation); }

//Calls insert_helper
void File::access_file(int user_id, std::string priority, char operation) {

	int p = 0;
	//changes priority into lower case to prevent errors
	std::transform(priority.begin(), priority.end(), priority.begin(), ::tolower);

	if (priority == "high") {
		
		//if queue not empty, queue max + 1 priority
		if (waiting_list->size() != 0)
			p = waiting_list->get_max().value().get().getPriority() + 1;
		else
			p = 1;
	}
	else if (priority == "low") {

		//if queue not empty, queue min - 1 priority
		if (waiting_list->size() != 0)
			p = waiting_list->get_min().value().get().getPriority() - 1;
		if (p < 0)
			p = 0;
	}
	insert_helper(user_id, p, operation);
}

bool File::release_access(int user_id) {

	//checks if user is accessing or not
	auto iter = std::find_if(current_users->begin(), current_users->end(),
		[&user_id](std::pair<int, char>& pair) {
		return (pair.first == user_id);
	});

	//if not returns false
	if (iter == current_users->end())
		return false;

	//else removes user
	current_users->erase(iter);

	//if waiting list isn't empty and top user is R type
	if (waiting_list->size() != 0 && waiting_list->get_max().value().get().getOperation() == 'R') {
		
		//while waiting list isn't empty and waiting list top is R
		while (waiting_list->size() != 0 && waiting_list->get_max().value().get().getOperation() != 'W') {

			//put into current users vector and remove from queue
			int id = waiting_list->get_max().value().get().getId();
			int op = waiting_list->get_max().value().get().getOperation();
			waiting_list->extract_max();
			current_users->push_back(std::make_pair(id, op));
		}
	}
	//if top of queue is W
	else if (waiting_list->size() != 0 && waiting_list->get_max().value().get().getOperation() == 'W') {

		//if current users has no one
		if (current_users->size() == 0) {
			// extract top of queue and insert into current_users
			int id = waiting_list->get_max().value().get().getId();
			int op = waiting_list->get_max().value().get().getOperation();
			waiting_list->extract_max();
			current_users->push_back(std::make_pair(id, op));
		}
	}
	return true;
}