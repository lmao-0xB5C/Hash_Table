#pragma once

class User {
private:
	int _ID;
	int priority;
	char operation;

public:
	//Param Cstr.
	User(int id, int _priority, char _operation) : _ID(id), priority(_priority), operation(_operation) {}
	//Default Cstr.
	User() = default;
	//Copy Cstr.
	User(const User& user) : _ID(user._ID), priority(user.priority), operation(user.operation) {}

public:
	/*~~~~~~~~~~~~~~~~~~Getters~~~~~~~~~~~~~~~~~~*/
	inline int getId() { return _ID; }
	inline int getPriority() { return priority; }
	inline char getOperation() { return operation; }
	/*~~~~~~~~~~~~~~~~~~Getters~~~~~~~~~~~~~~~~~~*/

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~Comparison Operators~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	inline bool operator<(const User& user) { return (priority < user.priority); }
	inline bool operator>(const User& user) { return (priority > user.priority); }
	inline bool operator==(const User& user) { return (_ID == user._ID); }
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/*Part of copy Swap Idiom*/
	User& operator=(User user) {
		swap(*this, user);
		return *this;
	}

	/*Part of Copy Swap Idiom*/
	friend void swap(User& first, User& second) {
		using std::swap; //ADL
		swap(first._ID, second._ID);
		swap(first.priority, second.priority);
		swap(first.operation, second.operation);
	}
};