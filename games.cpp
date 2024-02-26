
#include <iostream>
#include<fstream>
#include<vector>
#include<string>
#include "game.h"


using namespace std;














int main(int argc, char *argv[])
{
    bool was_file_changed = 0;
	string operation(argv[1]);
	GameDatabase database;
	if (argc == 4) {
		if (operation == "add") {
			database.add(argv[2], argv[3]);
            was_file_changed = 1;
		}
		else if (operation == "review") {
			database.add_rewiev(atoi(argv[2]), argv[3]);
            was_file_changed = 1;
		}
		else if (operation == "search") {
			database.search(argv[2], argv[3]);
		}
		else {
			cout << "Opperation not known" << endl;
		}
	}
	
	else if (argc == 3) {
		if (operation == "list") {
			database.list_sorted(argv[2]);
		}
		else if (operation == "delete") {
			database.delete_game(atoi(argv[2]));
            was_file_changed = 1;
		}
		else {
			cout << "Opperation not known" << endl;
		}
	}
	
	else if (argc == 2) {
		if (operation == "list") {
			database.list();
		}
		else if (operation == "csv") {
			database.csv();
		}
		else {
			cout << "Opperation not known" << endl;
		}
	}
	else {
		cout << "Niepoprawna ilosc argumentow" << endl;
	}
    if(was_file_changed){
        database.save_database();
    }




	return 0;
}


