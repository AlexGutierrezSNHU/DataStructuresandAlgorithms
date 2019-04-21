#include "HashTableEnhance.hpp"
#include "BinarySearchTreeEnhance.hpp"
#include "VectorSortingEnhance.hpp"
#include "CSVparser.hpp"
#include <string>
#include <iostream>

using namespace std;


int main(int argc, char* argv[]) {

	int choice = 0;
    while (choice != 9) {
		cout << "Menu:" << endl;
		cout << " 1. Search using Hash Table Algorithm" << endl;
		cout << " 2. Search using Binary Search Tree Algorithm" << endl;
		cout << " 3. Search using Vector Sorting Algorithm" << endl;
		cout << " 9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

		switch (choice) {

		case 1:
		hashTable::Selection();
		break;

		case 2:
		binarySearchTree::Selection();
		break;

		case 3:
		VectorSorting::Selection();
		break;
		}
	}

	cout << "Good bye." << endl;

    return 0;
}


