#include "util.h"

#include <vld.h>

int main() {

	HashTable<int, File> table(1000);

	std::cout << "Welcome to our Repo!\n\n";

	int in = 0;
	bool flag = false;
	while (!flag) {
		std::cout << "\n";
		menu();
		in = input();
		system("cls");
		switch (in) {
		default:
			break;

		case 1:
			load_file(table);
			break;

		case 2: {
			int f_id;
			std::cout << "Input file ID: ";
			std::cin >> f_id;
			if (table.insert(f_id, File(f_id)))
				std::cout << "File inserted!\n";
			else
				std::cout << "File Already exists!\n";
			break;
		}

		case 3: {
			int id;
			std::cout << "Input file ID: ";
			std::cin >> id;
			auto val = table[id];
			if (!val)
				std::cout << "File doesn't exist!\n";

			else if (val && table[id].value().get().isFree()) {
				table.remove(id);
				std::cout << "File has been removed!\n";
			}

			else
				std::cout << "File is being used!\n";
			break;
		}

		case 4:
			access_file(table);
			break;

		case 5: {
			int fid;
			std::cout << "Input file ID: ";
			std::cin >> fid;

			auto val = table[fid];
			if (!val) {
				std::cout << "No such file!\n";
				break;
			}

			int uid;
			std::cout << "\nInput user ID: ";
			std::cin >> uid;
			bool ac = val.value().get().release_access(uid);
			if (ac)
				std::cout << "Released access to File: " << fid << " for User: " << uid << "\n";
			else
				std::cout << "No such User is currently accessing the file!\n";

			break;
		}

		case 6:
			table.print();
			break;

		case 7:
			flag = true;
			break;

		}
	}

	system("pause");
}