#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include "hash_table.h"
#include "file.h"

int input() {
	std::cout << "Input your option: ";
	int opt;
	std::cin >> opt;
	while (opt < 1 && opt > 7) {
		std::cout << "Input an option in the range 1-7 (inclusive): ";
		std::cin >> opt;
	}
	return opt;
}

void menu() {
	std::cout << "1) Load File\n"
		<< "2) Insert File\n"
		<< "3) Delete File\n"
		<< "4) Access File\n"
		<< "5) Release Access\n"
		<< "6) Print Repo\n"
		<< "7) Exit\n\n";
}

void load_file(HashTable<int, File>& table) {
	std::cout << "Enter file's name: ";
	std::string file;
	std::cin.ignore();
	std::getline(std::cin, file);

	if (file.find(".txt") == std::string::npos)
		file += std::string(".txt");

	std::ifstream in(file);
	if (in.fail()) {
		std::cout << "Failed to load file\n";
		return;
	}

	std::string input, token;
	std::vector<std::string> vec;

	std::getline(in, input);
	while (std::getline(in, input)) {
		if (input != "" && input != ",") {

			std::istringstream ss(input);
			while (std::getline(ss, token, ','))
				vec.push_back(token);

			int j = atoi(vec[0].c_str());
			table.insert(j, File(j));

			for (int i = 0; i < vec.size() - 1; i += 3)
				table[j].value().get().access_file(atoi(vec[i + 1].c_str()), atoi(vec[i + 2].c_str()), vec[i + 3][0]);

			vec.clear();
		}
	}
	std::cout << "File loaded!\n";
	in.close();
}

void access_file(HashTable<int, File>& table) {
	std::cout << "Input File ID: ";
	int fid;
	std::cin >> fid;

	auto val = table[fid];
	if (!val) {
		std::cout << "File doesn't exist!\n";
		return;
	}

	std::cout << "\nInput User ID: ";
	int uid;
	std::cin >> uid;

	std::cout << "\nInput Operation type: ";
	char op;
	std::cin >> op;

	std::cout << "\n1) Input Priority number"
			  << "\n2) Auto Priority"
			  << "\n\nInput Option: ";

	int opt;
	std::cin >> opt;
	if (opt == 1) {
		int p;
		std::cout << "Input a number: ";
		std::cin >> p;
		val.value().get().access_file(uid, p, op);
	}
	else if (opt == 2) {
		std::string str;
		std::cout << "Input either high or low: ";
		std::cin.ignore();
		std::getline(std::cin, str);
		val.value().get().access_file(uid, str, op);
	}
	std::cout << "Access granted as per the rules!\n";
}