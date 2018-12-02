#pragma once

#include <string>

#include "priority_queue.h"
#include "user.h"

class File {
private:
	int _ID;
	PriorityQueue<User> waiting_list;
	std::vector<std::pair<int, char>> current_users;

public:
	File(int id);
	File() = default;
	File(const File& file);

public:
	void access_file(int user_id, int priority, char operation);
	void access_file(int user_id, std::string priority, char operation);
	bool release_access(int user_id);

	inline bool operator==(int id) { return (_ID == id); }

	bool isFree() { return (current_users.size() == 0 && waiting_list.size() == 0); }

	friend std::ostream& operator<<(std::ostream& stream, File& file) {
		std::cout << "File " << file._ID;

		if (file.current_users.size() != 0)
			std::cout << "...Access Granted to User ";

		for (auto i = file.current_users.begin(); file.current_users.size() != 0 && i != file.current_users.end(); ++i)
			stream << (*i).first << ", ";

		if (file.current_users.size() != 0 && file.current_users[0].second == 'W')
			stream << "write";
		else if (file.current_users.size() != 0)
			stream << "read";

		if (file.waiting_list.size() != 0) {
			auto u = file.waiting_list.get_max();
			if (u) {
				stream << "\n\t" << "Next User " << u.value().get().getId() << ", ";
				if (u.value().get().getOperation() == 'W')
					stream << "write";
				else
					stream << "read";

				stream << " Waiting ";
				if (file.waiting_list.size() == 1)
					stream << "1 user";
				else
					stream << file.waiting_list.size() << " users";
			}
		}
		return stream;
	}

private:
	void insert_helper(int user_id, int priority, char operation);
};