#include "util.h"

#include <vld.h>

int main() {

	HashTable<int, File> table(1000);

	std::cout << "Welcome to our Repo!\n\n";

	int in = 0;
	bool flag = false;
	while (!flag) {
		menu();
		in = input();
		system("cls");

		switch (in) {
		default:
			break;

		case 1:
			load_file(table);
			break;

		case 2:
			int f_id;
			std::cout << "Input file ID: ";
			std::cin >> f_id;
			table.insert(f_id, File(f_id));
			std::cout << "File inserted!\n";
			break;

		case 3:
			int id;
			std::cout << "Input file ID: ";
			std::cin >> id;
			if (table[id].value().get().isFree())
				table.remove(id);
			else
				std::cout << "File is being used!\n";
			break;

		case 4:
			access_file(table);
			break;

		case 5:
			int fid;
			std::cout << "Input file ID: ";
			std::cin >> fid;

			int uid;
			std::cout << "Input user ID: ";
			std::cin >> uid;
			table[fid].value().get().release_access(uid);
			break;

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