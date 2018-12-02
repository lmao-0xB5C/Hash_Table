#pragma once

class User {
private:
	int _ID;
	int priority;
	char operation;

public:
	User(int id, int _priority, char _operation) : _ID(id), priority(_priority), operation(_operation) {}
	User() = default;
	User(const User& user) : _ID(user._ID), priority(user.priority), operation(user.operation) {}

public:
	inline int getId() { return _ID; }
	inline int getPriority() { return priority; }
	inline char getOperation() { return operation; }

	inline bool operator<(const User& user) { return (priority < user.priority); }
	inline bool operator>(const User& user) { return (priority > user.priority); }
	inline bool operator==(const User& user) { return (_ID == user._ID); }

	User& operator=(User user) {
		swap(*this, user);
		return *this;
	}

	friend void swap(User& first, User& second) {
		using std::swap; //ADL
		swap(first._ID, second._ID);
		swap(first.priority, second.priority);
		swap(first.operation, second.operation);
	}
};