# ifndef     _VECTOR_SORTING_ENHANCE_HPP_
# define    _VECTOR_SORTING_ENHANCE_HPP_

#include <algorithm>
#include <iostream>
#include <time.h>
#include <vector>
#include "CSVparser.hpp"
#include<stdio.h>

namespace VectorSorting
{
		//============================================================================
		// Global definitions visible to all methods and classes
		//============================================================================

		// forward declarations
		double strToDouble(std::string str, char ch);

		// define a structure to hold bid information
		struct Bid {
			std::string bidId; // unique identifier
			std::string title;
			std::string fund;
			double amount;
			Bid() {
				amount = 0.0;
			}
		};

		//============================================================================
		// Static methods used for testing
		//============================================================================

		/**
		 * Display the bid information to the console (std::out)
		 *
		 * @param bid struct containing the bid info
		 */

		 //Will display bid information that is called.
		void displayBid(Bid bid) {
			std::cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
					<< bid.fund << std::endl;
			return;
		}

		/**
		 * Prompt user for bid information using console (std::in)
		 * @return Bid struct containing the bid info
		 */
		Bid getBid() {
			Bid bid;

			std::cout << "Enter Id: ";
			std::cin.ignore();
			std::getline(std::cin, bid.bidId);

			std::cout << "Enter title: ";
			std::getline(std::cin, bid.title);

			std::cout << "Enter fund: ";
			std::cin >> bid.fund;

			std::cout << "Enter amount: ";
			std::cin.ignore();
			std::string strAmount;
			std::getline(std::cin, strAmount);
			bid.amount = strToDouble(strAmount, "$");

			return bid;
		}

		/**
		 * Load a CSV file containing bids into a container
		 *
		 * @param csvPath the path to the CSV file to load
		 * @return a container holding all the bids read
		 * Handles exception if path or file unavailable
		 *
		 */

		 //
		class std::vector<Bid> loadBids(std::string csvPath) {
			std::cout << "Loading CSV file " << csvPath << std::endl;

			std::vector<Bid> bids;

			csv::Parser file = csv::Parser(csvPath);

			try {

				for (int i = 0; i < file.rowCount(); i++) {

								Bid bid;
					bid.bidId = file[i][1];
					bid.title = file[i][0];
					bid.fund = file[i][8];
					bid.amount = strToDouble(file[i][4], '$');

					std::cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << std::endl;

					bids.push_back(bid);
				}
			} catch (csv::Error &e) {
				std::cerr << e.what() << std::endl;
			}
			return bids;
		}


		/**
		 * Partition the vector of bids into two parts, low and high
		 *
		 * @param bids Address of the vector<Bid> instance to be partitioned
		 * @param begin Beginning index to partition
		 * @param end Ending index to partition
		 */
		int partition(std::vector<Bid>& bids, int begin, int end)
		{
			int mid = 1+ (bids.size()/2); // initialized int mid to 1 plus the length of vector list + 1 as midpoint for partition
			std::string pivot = bids[mid].title; //  title string set bids at bids element mid for pivot comparison
			int l = (begin-1); // int l initialized for lowest element

			Bid temp; // initializes temp Bids container

			for(int x = begin; x <= end -1; x++) // loop to advance through side or partitioned vector list
			{
				if (bids[x].title <= pivot) // conditional statement to check  bid title at element x against pivot string
				{
					l++; // advances int l 1
					temp = bids[l]; // temp bid container is equal to bids at element l;
					bids[l] = bids[x]; // bids at element l is equal to bids at elemtent x, next element in list
					bids[x] = temp; // bids at element x is set to new lowest element in temp container
				}
			}
			Bid temp1 = bids[l+1]; // initializes Bid container temp1, passes bids at next element to temp container
			bids[l+1] = bids[end]; // passes  final element in vector list to next element in vector list
			bids[end] = temp1; // passes final element in vector list to temp container

			return (l+1); // return int l + 1
			}

		/**
		 * Perform a quick sort on bid title
		 * Average performance: O(n log(n))
		 * Worst case performance O(n^2))
		 *
		 */
		void quickSort(std::vector<Bid>& bids, int begin, int end)
			{

				if (begin < end)
						{
					int index = partition(bids, begin,end);
					quickSort(bids, begin, index-1);
					quickSort(bids, index+1 ,end);
					return;
					}
				}

		/**
		 * Perform a selection sort on bid title
		 * Average performance: O(n^2))
		 * Worst case performance O(n^2))
		 *
		 *
		 */
		void selectionSort(std::vector<Bid>& bids) {
			{
					int n = bids.size();
					int i , j;
					Bid temp;
					for (i = 0; i < n - 1; i++)
					{
						int index = i;
						temp = bids[i];
						for (j = i + 1; j < n; j++)
						if(bids[j].title < bids[index].title)
								index = j;

						temp = bids[index];
						bids[index] = bids[i];
						bids[i] = temp;
					}
				}

		}

		/**
		 * Simple C function to convert a string to a double
		 * after stripping out unwanted char
		 *
		 * credit: http://stackoverflow.com/a/24875936
		 *
		 * @param ch The character to strip out
		 */
		double strToDouble(std::string str, char ch) {
			str.erase(remove(str.begin(), str.end(), ch), str.end());
			return atof(str.c_str());
		}


		// Selection class allows used to test perfomrance and accuracy od data structures and algorithms.
		// Preliminary performance is tested using cpu clock ticks, performance will vary greatly depending
		// on the specifications of the system being used. There is currently no timeout interupt in place.

		class Selection {
			int main()
			{

				// process command line arguments
				std::string csvPath = "src/eBid_Monthly_Sales_Dec_2016.csv";


				// Define a vector to hold all the bids
				std::vector<Bid> bids;

				// Define a timer variable
				clock_t ticks;

				//int end = bids.size();
				int start = 0;
				int choice = 0;
				while (choice != 9) {
					std::cout << "Menu:" << std::endl;
					std::cout << "  1. Load Bids" << std::endl;
					std::cout << "  2. Display All Bids" << std::endl;
					std::cout << "  3. Selection Sort All Bids" << std::endl;
					std::cout << "  4. Quick Sort All Bids" << std::endl;
					std::cout << "  9. Exit" << std::endl;
					std::cout << "Enter choice: ";
					std::cin >> choice;

					switch (choice) {

					case 1:
						// Initialize a timer variable before loading bids
						ticks = clock();

						// Complete the method call to load the bids
						bids = loadBids(csvPath);

						std::cout << bids.size() << " bids read" << std::endl;

						// Calculate elapsed time and display result
						ticks = clock() - ticks; // current clock ticks minus starting clock ticks
						std::cout << "time: " << ticks << " clock ticks" << std::endl;
						std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl;

						break;

					case 2:
						// Loop and display the bids read
						for (int i = 0; i < bids.size(); ++i) {
							displayBid(bids[i]);
						}
						std::cout << std::endl;

						break;

					case 3:
						ticks = clock(); // initializes clock
						selectionSort(bids);

						ticks = clock() - ticks; // current clock ticks minus starting clock ticks
						std::cout << "time: " << ticks << " clock ticks" << std::endl; // system out time in cpu clock ticks
						std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl; // system out time in approximate seconds
						std::cout << bids.size() << " bids sorted" << std::endl; // system out number of bids sorted

						break;


					case 4:
						int end = bids.size(); // local variable end to set to size of bids list
						ticks = clock(); // calls clock method

						quickSort(bids, 0 , end-1); // calls quicksort methods, passes bids, 0 as lowest element and bid size -1 as highest element
						ticks = clock() - ticks; // current clock ticks minus starting clock ticks
						std::cout << "time: " << ticks << " clock ticks" << std::endl; // system out time in cpu clock ticks
						std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl;// system out time in approximate seconds
						std::cout << bids.size() << " bids sorted" << std::endl;// system out number of bids sorted

						break;

					}
			}

			std::cout << "Good bye." << std::endl;

			return 0;
			}
		};

}

#endif
