#include "file.h"

File::File(int id) : _ID(id) {}

File::File(const File& file) : _ID(file._ID), waiting_list(file.waiting_list), current_users(file.current_users) {}

void File::insert_helper(int user_id, int priority, char operation) {

	if (waiting_list.size() == 0 && current_users.size() == 0)
		current_users.push_back(std::make_pair(user_id, operation));

	else if (waiting_list.size() != 0)
		waiting_list.insert(User(user_id, priority, operation));

	else if (waiting_list.size() == 0 && current_users.size() != 0) {

		if (current_users[0].second != 'W' && operation == 'R')
			current_users.push_back(std::make_pair(user_id, operation));
		else
			waiting_list.insert(User(user_id, priority, operation));
	}
}

void File::access_file(int user_id, int priority, char operation) { insert_helper(user_id, priority, operation); }

void File::access_file(int user_id, std::string priority, char operation) {

	int p = 0;
	if (priority == "high") {
		if (waiting_list.size() != 0)
			p = waiting_list.get_max().value().get().getPriority();
		else
			p = 1;
	}
	else if (priority == "low") {
		if (waiting_list.size() != 0)
			p = waiting_list.get_min().value().get().getPriority();
	}
	insert_helper(user_id, p, operation);
}

bool File::release_access(int user_id) {

	auto iter = std::find_if(current_users.begin(), current_users.end(),
		[&user_id](std::pair<int, char>& pair) {
		return (pair.first == user_id);
	});

	if (iter == current_users.end())
		return false;

	current_users.erase(iter);

	if (waiting_list.size() != 0 && waiting_list.get_max().value().get().getOperation() == 'R') {

		while (waiting_list.size() != 0 && waiting_list.get_max().value().get().getOperation() != 'W') {

			int id = waiting_list.get_max().value().get().getId();
			int op = waiting_list.get_max().value().get().getOperation();
			waiting_list.extract_max();
			current_users.push_back(std::make_pair(id, op));
		}
	}
	else if (waiting_list.size() != 0 && waiting_list.get_max().value().get().getOperation() == 'W') {

		if (current_users.size() == 0) {

			int id = waiting_list.get_max().value().get().getId();
			int op = waiting_list.get_max().value().get().getOperation();
			waiting_list.extract_max();
			current_users.push_back(std::make_pair(id, op));
		}
	}
	return true;
}