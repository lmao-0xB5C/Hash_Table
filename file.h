#pragma once

/*////////////////////////*/
#include <string>
#include <memory>
/*////////////////////////*/

/*////////////////////////*/
#include "priority_queue.h"
#include "user.h"
/*////////////////////////*/

/*~~~~~Preprocessor Directives just to clean the code a bit~~~~~*/
#define QUEUE	std::shared_ptr<PriorityQueue<User>>
#define VECTOR	std::shared_ptr<std::vector<std::pair<int, char>>>
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//FILE CLASS ADT
class File {
private:
	int _ID;
	QUEUE waiting_list;				//Pointer to a Priority Queue(Max) for waiting users
	VECTOR current_users;		   //Pointer to a Vector of current users accesing the file

public:
	File(int id);					//Param Cstr. uses ID to create the file
	File() = default;			   //Default Cstr.
	File(const File& file);		  //Copy Cstr.

public:
	/*Function taking in user details and putting that user in an appropriate place*/
	void access_file(int user_id, int priority, char operation);
	void access_file(int user_id, std::string priority, char operation);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//Function to release access for a certain user
	bool release_access(int user_id);

	//Compares ID of this file with param ID
	inline bool operator==(int id) { return (_ID == id); }
	
	//Checks of a file is in use or not
	bool isFree() { return (current_users->size() == 0 && waiting_list->size() == 0); }

	//Overloading of (<<) stream operator to print the file details
	friend std::ostream& operator<<(std::ostream& stream, File& file) {
		std::cout << "File " << file._ID;

		if (file.current_users->size() != 0)
			std::cout << "...Access Granted to User ";

		//auto deduces the variable type automatically, used here to prevent manually writing lengthy name of iterator
		for (auto i = file.current_users->begin(); file.current_users->size() != 0 && i != file.current_users->end(); ++i)
			stream << (*i).first << ", ";

		if (file.current_users->size() != 0 && file.current_users->at(0).second == 'W')
			stream << "write";
		else if (file.current_users->size() != 0)
			stream << "read";

		if (file.waiting_list->size() != 0) {
			auto u = file.waiting_list->get_max();
			if (u) {
				stream << "\n\t" << "Next User " << u.value().get().getId() << ", ";
				if (u.value().get().getOperation() == 'W')
					stream << "write";
				else
					stream << "read";

				stream << "\n\tWaiting ";
				if (file.waiting_list->size() == 1)
					stream << "1 user";
				else
					stream << file.waiting_list->size() << " users";
			}
		}
		return stream;
	}

private:
	//Used by access file function to insert a user as per the rules (implemented in file.cpp)
	void insert_helper(int user_id, int priority, char operation);
};