# ifndef     _HASH_TABLE_ENHANCE_HPP_
# define    _HASH TABLE_ENHANCE_HPP_


#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <time.h>
#include <sstream>

#include "CSVparser.hpp"

namespace hashTable
{

		//============================================================================
		// Global definitions visible to all methods and classes
		//============================================================================

		const unsigned int DEFAULT_SIZE = 179;

		// Forward declarations
		double strToDouble(std::string str, char ch);

		// Global data structure to hold variable inputs used in testing performance of
		// developed algorithm.
		struct Bid {
			std::string bidId;
			std::string title;
			std::string fund;
			double amount;
			Bid() {
				amount = 0.0;
			}
		};

		//============================================================================
		// Hash Table class definition
		//============================================================================

		/**
		 * Defines the class containing data members to implement a hash table with chaining.
		 */

		class bid_node
		{
			public:
				int key;
				Bid bid_info;
				bid_node *next;   // initializes node pointer next
					bid_node (int key, Bid bid_info) // defines bid_node
					{
						this -> key = key; // this instance of key inside node class
						this -> bid_info = bid_info; //this instance of bid_info inside node class
						this -> next = NULL; // node pointer next set to null
					}
		};

		/**
		 * Defines the class containing  both public and private methods to manipulate
		 * and traverse the hash table.
		 */

		class HashTable {

		private:
			unsigned int hash(int key);
			bid_node** table;

		public:
			HashTable();
			virtual ~HashTable();
			void Insert(Bid bid);
			void PrintAll();
			void Remove(std::string bidId);
			Bid Search(std::string bidId);
		};


		// Default constructor to initialize the hash table to create a number of buckets
		// equal default variable size.

		HashTable::HashTable() {
			table = new bid_node*[DEFAULT_SIZE];
			for (int i = 0; i < DEFAULT_SIZE; i++)
				table[i]= NULL;
				}

		// Default destructor used to delete all buckets associates with the hash table
		// and clearing the memory

		HashTable::~HashTable() {
			for (int i; i < DEFAULT_SIZE; i++)
			{
				bid_node* entry = table[i];
				while (entry != NULL)
				{
					bid_node* temp = entry;
					entry = entry -> next;
					delete temp;
				}
			}
			delete[] table;
		}

		/**
		 * Calculate the hash value of a given key.
		 * Note that key is specifically defined as
		 * unsigned int to prevent undefined results
		 * of a negative list index.
		 *
		 * @param key The key to hash
		 * @return The calculated hash
		 */
		unsigned int HashTable::hash(int key) {
			return key % DEFAULT_SIZE;

		}

		/**
		 * Insert a bid into the hash table
		 *
		 * @param bid The bid to insert
		 */

		void HashTable::Insert(Bid bid) {
			std::string id = bid.bidId;
			int l_key = atoi(id.c_str());
			int index = hash(l_key);
			bid_node* temp = NULL;
			bid_node* entry = table[index];
			while (entry != NULL)
			{
				temp = entry;
				entry = entry-> next;
			}
			if (entry == NULL)
			{
				entry = new bid_node(l_key, bid);
				if (temp == NULL)
				{
					table[index] = entry;
				}
				else
				{
					temp -> next = entry;
				}
			}

		}


		// function that will print all bids located in the hash table buckets, not only first value in bucket.


		void HashTable::PrintAll() {

			bid_node* entry;
			int key_num = 0;
			bool prev = false;
				for(int i = 0; i <= DEFAULT_SIZE; i++ )
				{

				for(entry = table[i] ; entry != NULL; entry = entry->next )
					{
					if (table[i] != NULL && prev == false)
						{
							std::cout << "Key " + std::to_string(key_num) + ": ";
							std::cout << entry-> bid_info.bidId + " | " << entry-> bid_info.title + " | " << entry-> bid_info.amount <<  " | " + entry-> bid_info.fund;
							prev = true;
						 }else {
							std::cout << "    " + std::to_string(key_num) + ": ";
							std::cout << entry-> bid_info.bidId + " | " << entry-> bid_info.title + " | " << entry-> bid_info.amount <<  " | " + entry-> bid_info.fund;
						 }
						std::cout << std::endl;
					}
				key_num++;
				prev = false;

				}
			 }


		/**
		 * Remove a bid from the hash table and reassociate bucket pointers.
		 *
		 * @param bidId The bid id to search for
		 */

		void HashTable::Remove(std::string bidId) {
			std::string id = bidId;
			int l_key = atoi(id.c_str());
			int index = hash(l_key);
			bid_node* entry;
			bid_node* delPtr;
			bid_node* temp = NULL;

			if (table[index] == NULL)
				{
					return;
				}
			entry= table[index];
			if (entry -> bid_info.bidId != bidId)
				{
					entry = entry -> next;
				}
			if (entry -> next == NULL && entry -> bid_info.bidId == bidId)
				{
					table[index] = NULL;
				}else {

					delPtr = entry;
					entry = entry -> next;
					delete delPtr;
						}
			table[index] = temp;
		}


		/**
		 * Search for the specified bidId in the hash table if the bucket exsists.
		 *
		 * @param bidId The bid id to search for
		 */


		Bid HashTable::Search(std::string bidId) {
			int l_key = atoi(bidId.c_str());
			int index = hash(l_key);
			bid_node* entry = table[index];
				while (entry != NULL)
				{
					if (entry -> bid_info.bidId != bidId)
					{
						entry = entry -> next;
					}
					return entry -> bid_info;
				}
				if (entry == NULL){

			}

		  }



		/**
		 * Display the bid information to the console utilizing std::out
		 *
		 * @param bid struct containing the bid info
		 */

		 void displayBid(Bid bid) {
			 std::cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
					<< bid.fund << std::endl;
			return;
		}

		/**
		 * Load a CSV file containing bids into a container
		 *
		 * @param csvPath the path to the CSV file to load
		 * @return a container holding all the bids read
		 *
		 * Provided as part of the template for the project.
		 */


		void loadBids(std::string csvPath, HashTable* hashTable) {
			std::cout << "Loading CSV file " << csvPath << std::endl;

			csv::Parser file = csv::Parser(csvPath);

			std::vector<std::string> header = file.getHeader();
			for (auto const& c : header) {
				std::cout << c << " | ";
			}
			std::cout << "" <<std:: endl;

			try {

				for (unsigned int i = 0; i < file.rowCount(); i++) {

					// Create a data structure and add to the collection of bids
					Bid bid;
					bid.bidId = file[i][1];
					bid.title = file[i][0];
					bid.fund = file[i][8];
					bid.amount = strToDouble(file[i][4], '$');

					std::cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << std::endl;

					hashTable->Insert(bid);
				}
			} catch (csv::Error &e) {
				std::cerr << e.what() << std::endl;
			}
		}

		/**
		 * Simple C function to convert a string to a double
		 * after stripping out unwanted char
		 *
		 * credit: http://stackoverflow.com/a/24875936
		 *
		 * @param ch The character to strip out
		 * Provided as part of the template for the project.
		 */


		double strToDouble(std::string str, char ch) {
			str.erase(remove(str.begin(), str.end(), ch), str.end());
			return atof(str.c_str());
		}

		// Selection class allows used to test performance and accuracy of data structures and algorithms.
		// Preliminary performance is tested using cpu clock ticks, performance will vary greatly depending
		// on the specifications of the system being used. There is currently no timeout interupt in place.

		class Selection {

			int main(){
				std::string csvPath = "src/eBid_Monthly_Sales_Dec_2016.csv";
				std::string	bidKey = "98109";

				clock_t ticks;


				HashTable* bidTable;
				Bid bid;

				int choice = 0;
				while (choice != 9) {
					std::cout << "Menu:" << std::endl;
					std::cout << "  1. Load Bids" << std::endl;
					std::cout << "  2. Display All Bids" << std::endl;
					std::cout << "  3. Find Bid" << std::endl;
					std::cout << "  4. Remove Bid" << std::endl;
					std::cout << "  9. Exit" << std::endl;
					std::cout << "Enter choice: ";
					std::cin >> choice;

					switch (choice) {

					case 1:
						bidTable = new HashTable();

						// Initialize a timer variable before loading bids
						ticks = clock();

						// Complete the method call to load the bids
						loadBids(csvPath, bidTable);

						// Calculate elapsed time and display result
						ticks = clock() - ticks;
						std::cout << "time: " << ticks << " clock ticks" << std::endl;
						std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl;
						break;

					case 2:
						bidTable->PrintAll();
						break;

					case 3:
						ticks = clock();

						bid = bidTable->Search(bidKey);

						ticks = clock() - ticks;

						if (!bid.bidId.empty()) {
							displayBid(bid);
						} else {
							std::cout << "Bid Id " << bidKey << " not found." << std::endl;
						}

						std::cout << "time: " << ticks << " clock ticks" << std::endl;
						std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl;
						break;

					case 4:
						bidTable->Remove(bidKey);
						break;
					}
				}

				std::cout << "Good bye." << std::endl;


				return 0;
				}
		};

}

#endif
