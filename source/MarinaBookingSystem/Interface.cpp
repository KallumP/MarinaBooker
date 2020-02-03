#include "Interface.h"
#include <iostream>
#include <vector>

//Constructor
Interface::Interface() {

	for (size_t i = 0; i < 24; i++)

		timeTable.push_back(TimeStamp(i));

	LoadOrders();
}

//Desctructor
Interface::~Interface() {


}

//Loads up previous orders
void Interface::LoadOrders() {

	//load from a text file (same file location as the exe)

	MainMenu();
}

//The main menu that the user is presented with
void Interface::MainMenu() {

	//variable used to keep track of when to close the app
	bool exit = true;

	do {

		std::cout << "Enter what number you want to do below" << std::endl;
		std::cout << "1. Create a new order" << std::endl;
		std::cout << "2. Delete an order" << std::endl;
		std::cout << "3. View all orders in a marina simulation" << std::endl;
		std::cout << "4. Show all orders in console" << std::endl;
		std::cout << "5. Exit program" << std::endl;
		std::cout << "6. Help" << std::endl;

		int input;

		std::cin >> input;

		//checks what the input was
		switch (input) {

			case  1:
			system("CLS");
			TakeOrder();
			break;


			case  2:
			system("CLS");
			break;


			case  3:
			system("CLS");
			break;

			case 4:
			system("XLS");
			break;

			case  5:
			system("CLS");
			exit = Exit();
			break;

			default:
			system("CLS");
			std::cout << "Please enter one of the numbers shown above." << std::endl << std::endl << std::endl;
			break;
		}

		//loops until the user tries to exit
	} while (!exit);
}

//allows a use to take an order
void Interface::TakeOrder() {

	//resets the order values
	order = Order();

	int minDepth = 5;
	int minLength = 15;

	TakeDepth(minDepth);

	system("CLS");

	TakeLength(minLength);

	system("CLS");

	//gets the start and end month
	FindTimeIntervals();

	system("CLS");

	TakeName();

	system("CLS");

	CalculateCosts();

	ConfirmEntries();

	int input;
	std::cin >> input;
}

//takes the user input for the boat depth
void Interface::TakeDepth(int minDepth) {

	float input;

	//gets the depth of the boat being ordered for
	do {
		std::cout << "Enter the depth of the boat: ";

		std::cin >> input;
		std::cout << std::endl;

		//checks to see if the input was within the bounds
		if (input <= minDepth || input > 0)
			order.depth = input;
		else if (input > minDepth)
			std::cout << "This entry was too big (boat must be less than " << minDepth << " meters deep" << std::endl;
		else if (input < 0)
			std::cout << "A boat cannot be smaller than 0 meters deep!";

	} while (input > minDepth || input <= 0);
}

//takes the user input for the boat length
void Interface::TakeLength(int minLength) {

	float input;

	//loops until a valid length was inputted
	do {

		//shows currently entered values
		std::cout << "Entered depth: " << order.depth << std::endl << std::endl;

		std::cout << "Enter the length of the boat: ";

		std::cin >> input;
		std::cout << std::endl;

		//checks to see if the input was within the bounds
		if (input <= minLength || input > 0)
			order.length = input;
		else if (input > minLength)
			std::cout << "This entry was too big (the boat must be less than " << minLength << " meteres long" << std::endl;
		else if (input <= 0)
			std::cout << "A boat cannot be less than 0 meters long!";

	} while (input > minLength || input <= 0);
}

//outputs all the available times for a given boat length
void Interface::FindTimeIntervals() {

	bool endFound = false;

	std::vector<FoundTime> foundTimes;

	//loops through each month on the timetable
	for (size_t i = 0; i < timeTable.size(); i++) {

		//checks to see if there is enough space in the current start check month's length left
		if (TimeStamp::MAX_LENGTH - timeTable[i].GetLengthUsed() >= order.length) {

			//loops past the found start month
			for (size_t j = i + 1; j < timeTable.size(); j++) {

				//checks to see if the current end check month does not have enough space
				if (TimeStamp::MAX_LENGTH - timeTable[i].GetLengthUsed() < order.length) {

					//registers that there was an end month found
					endFound = true;

					//adds the found time gap to the list of times
					foundTimes.push_back(FoundTime(i, j));

					//sets i to j+1 so that the next set of available days can be found
					i = j + 1;

					//stops searching for an end
					break;
				}
			}

			//checks to see if an end month was not found
			if (!endFound) {

				int foundCount = timeTable.size();

				//adds on the last month, because it is the final usable date
				foundTimes.push_back(FoundTime(i, foundCount - 1));

				//stops searching for start months, as end of the list was reached 
				break;
			}
		}
	}
}

//gets the start month from the user
void Interface::TakeStartMonth(std::vector<FoundTime> foundTimes) {

	int chosenIndex;

	bool repeat = false;

	if (foundTimes.size() != 0) {

		//loops until a correct input was entered
		do {

			//shows currently entered values
			std::cout << "Entered depth: " << order.depth << std::endl;
			std::cout << "Entered length: " << order.length << std::endl << std::endl;

			std::cout << "Below is a list of all the times that you can book. " << std::endl;

			for (size_t i = 0; i < foundTimes.size(); i++) {

				//outputs what month was found
				std::cout << i + 1 << ". Month: " << foundTimes[i].start << " until ";

				//outputs what end month was found
				std::cout << "month: " << foundTimes[i].end << std::endl;
			}

			std::cout << "Enter the number of the starting date you want";

			//takes an input
			std::cin >> chosenIndex;

			//sets the normalises the input to be zero based
			chosenIndex--;


			//checks to see if the input was wrong
			if (chosenIndex < 0 && chosenIndex >= foundTimes.size()) {

				system("CLS");

				std::cout << "Please enter the first number from the starting month you want" << std::endl << std::endl;

				repeat = true;

			} else {


				//sets the chosen time to be the start time of the chosenIndex (I will set the end time later)
				order.timeings = foundTimes[chosenIndex];

				repeat = true;
			}

		} while (repeat);

		system("CLS");

		TakeEndMonth();
	}
}

//gets the end month from the user
void Interface::TakeEndMonth() {

	int input;
	bool repeat = false;

	//finds out how many months can be booked
	int availableMonths = 0;

	//loops until a correct end time was entered
	do {

		//shows currently entered values
		std::cout << "Entered depth: " << order.depth << std::endl;
		std::cout << "Entered length: " << order.length << std::endl;
		std::cout << "Start month: " << order.timeings.start << std::endl << std::endl;

		//finds out how many months can be booked
		int availableMonths = order.timeings.end - order.timeings.start;

		//asks how many months were wanted
		std::cout << "You can book for:  " << availableMonths << " months." << std::endl;
		std::cout << "How many months do you want to book for (you must book for atleast one month)" << std::endl;

		//gets the input
		std::cin >> input;

		//sets the end date
		order.timeings.end = order.timeings.start + input;

		//checks to see if a correct number was inputed
		if (input < 1 && input >= availableMonths) {

			system("CLS");

			std::cout << "Please enter a valid number of months" << std::endl << std::endl;

			repeat = true;
		} else {

			repeat = false;

		}

		//repeats until a valid end month was entered
	} while (repeat);
}

//takes the name of the person making the order
void Interface::TakeName() {

	//shows currently entered values
	std::cout << "Entered depth: " << order.depth << std::endl;
	std::cout << "Entered length: " << order.length << std::endl;
	std::cout << "Start month: " << order.timeings.start << std::endl;
	std::cout << "Start month: " << order.timeings.end << std::endl << std::endl;

	std::string input;

	std::cout << "Enter your name (first and last): ";

	std::cin >> input;
	std::cout << std::endl;

	order.name = input;
}

//calculates the cost using 10*length*months
void Interface::CalculateCosts() {

	order.cost = 10 * order.length * (order.timeings.end - order.timeings.start);
}

//outputs all the given inputs and asks for confirmation
void Interface::ConfirmEntries() {

	bool repeat = false;

	do {

		std::cout << "Below are your entries. Are they correct? (y/n)" << std::endl;

		//shows currently entered values
		std::cout << "Entered depth: " << order.depth << std::endl;
		std::cout << "Entered length: " << order.length << std::endl;
		std::cout << "Start month: " << order.timeings.start << std::endl;
		std::cout << "End month: " << order.timeings.end << std::endl;
		std::cout << "Name: " << order.name << std::endl;
		std::cout << "Cost: " << order.cost << std::endl << std::endl;

		std::string input;
		std::cin >> input;

		if (input == "y" || input == "Y") {

			repeat = false;

			//puts the current order into the list of all orders
			allOrders.push_back(order);

			system("CLS");
			std::cout << "Payment registered, order added to system" << std::endl;

		} else if (input == "n" || input == "N") {

			repeat = false;

			system("CLS");
			std::cout << "Transaction cancelling" << std::endl;

		} else {
			repeat = true;

			system("CLS");
			std::cout << "Please enter either y or n" << std::endl;
		}
	} while (repeat);
}

//allows the user to delete a user
void Interface::DeleteOrder() {

}

//simulation sequence
void Interface::Simulation() {

}

//the exit sequence
bool Interface::Exit() {

	do {

		//asks if the user really wants to exit
		std::cout << "Are you sure you want to exit? (y/n)" << std::endl;

		//gets the input
		std::string input;
		std::cin >> input;

		//checks for yes
		if (input == "y" || input == "Y")
			return true;

		//checks for no
		else if (input == "n" || input == "N")
			return false;


		system("CLS");

		std::cout << "Please enter either Y or N" << std::endl;

	} while (true);
}