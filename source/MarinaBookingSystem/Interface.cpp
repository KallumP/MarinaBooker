#include "Interface.h"
#include "Order.h"
#include "Environment.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

//Constructor
Interface::Interface() {

	SetupTimeTable(24);

	LoadOrders();

	MainMenu();
}

//Desctructor
Interface::~Interface() {


}

//checks is the last input was numerical (true = numerical input)
bool Interface::NumericalInput() {

	//checks to see if the input was not a number
	if (std::cin.fail()) {

		//lets the use know to enter a number
		system("CLS");
		std::cout << "Please enter a number." << std::endl << std::endl << std::endl;

		//clears the cin cache
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		return false;

	} else {

		return true;
	}

	//REFERENCE https://stackoverflow.com/questions/5655142/how-to-check-if-input-is-numeric-in-c
}

//turns an input date into 
int Interface::DateToIndex(std::string date) {

	//sets the default index to -1
	int index = -1;

	//loops through each month in the timetable
	for (int i = 0; i < timeTable.size(); i++) {

		//checks to see if the input date matches the current month's date
		if (timeTable[i].GetDate() == date) {

			//saves what month was entered
			index = i;

			//stops searching
			break;
		}
	}

	return  index;
}

//registers an order that was made programmatically
void Interface::RegisterOrder(Order newOrder) {

	//puts the current order into the list of all orders
	allOrders.push_back(newOrder);

	//goes through each month that was ordered for
	for (int i = newOrder.timings.start; i <= newOrder.timings.end; i++)

		//adjusts the timetable to now account for the new boat length for the current month in the loop
		timeTable[i].AdjustLength(newOrder.length);
}

//writes an order to the file
void Interface::WriteToFile(Order order) {

	std::ofstream toWrite;

	toWrite.open(filePath, std::ios_base::app);

	//writes "next" to signify that there is another order
	toWrite << "next" << std::endl;

	toWrite << order.depth << std::endl;
	toWrite << order.length << std::endl;
	toWrite << timeTable[order.timings.start].GetDate() << std::endl;
	toWrite << timeTable[order.timings.end].GetDate() << std::endl;
	toWrite << order.name << std::endl;
	toWrite << order.boatName << std::endl;
	toWrite << order.type << std::endl;

	toWrite.close();
}

//creates a programmatic order using the input number
void Interface::CreateProgrammaticOrder(int val) {

	Order autoGenOrder;

	autoGenOrder.depth = (float)val;
	autoGenOrder.length = (float)val;
	autoGenOrder.boatName = "Boat " + std::to_string(val);
	autoGenOrder.name = "Name " + std::to_string(val);

	autoGenOrder.timings.start = val;
	autoGenOrder.timings.end = val;
	autoGenOrder.type = "Narrow";

	RegisterOrder(autoGenOrder);
	WriteToFile(autoGenOrder);
}

//sets up the timetable to reach a certain number of months from the next month from today
void Interface::SetupTimeTable(int noOfMonths) {

	time_t* now = new time_t();
	*now = time(NULL);

	tm* ltm = new tm();
	localtime_s(ltm, now);

	//gets the current year (since 1900)
	int year = ltm->tm_year + 1900;

	//gets the current month (normalised to 1 based)
	int month = ltm->tm_mon + 1;

	for (int i = 0; i < noOfMonths; i++) {

		//increases the date of the next timestamp to create
		month++;

		if (month > 12) {
			month = 1;
			year++;
		}

		//creates a text value of the date for the timestamp to create
		std::string date = std::to_string(month) + "/" + std::to_string(year);

		timeTable.push_back(TimeStamp(date));
	}
}

//Loads up previous orders
void Interface::LoadOrders() {

	//opens the file to read from
	std::ifstream toRead;
	toRead.open(filePath);

	//stores the next line from the text file
	std::string line;

	//stores whether the read sequence should repeat
	bool repeat = true;

	//load orders from a retrieved data
	while (repeat) {

		Order newOrder;

		std::getline(toRead, line);

		//checks to see if there was anything left to do in the file
		if (line == "next") {

			//sets the depth
			std::getline(toRead, line);
			newOrder.depth = std::stoi(line);

			//sets the length
			std::getline(toRead, line);
			newOrder.length = std::stoi(line);

			//sets the start date
			std::getline(toRead, line);
			std::string start = line;

			//calcluates the start index
			int startIndex = DateToIndex(start);


			//sets the end date
			std::getline(toRead, line);
			std::string end = line;

			//calculates the end index
			int endIndex = DateToIndex(end);

			//checks to see if the order end is still within the current timetable
			if (endIndex != -1) {

				//sets the end date index
				newOrder.timings.end = endIndex;

				//checks to see if the order start was still within the timetable
				if (startIndex != -1) {

					//sets the start date index
					newOrder.timings.start = startIndex;
				} else {

					//sets the start to the first month of the timetable
					newOrder.timings.start = 0;
				}

			} else {

				//moves onto the next order
				continue;
			}

			//sets the name of
			std::getline(toRead, line);
			newOrder.name = line;

			//sets the boat name
			std::getline(toRead, line);
			newOrder.boatName = line;

			//sets the boat type
			std::getline(toRead, line);
			newOrder.type = line;

			//registers the order into the program (does not rewrite it to the file)
			RegisterOrder(newOrder);

		} else {

			//stops the file search if there was no more lines left
			repeat = false;

		}
	}

	//CreateProgrammaticOrder(4);
	//CreateProgrammaticOrder(3);
	//CreateProgrammaticOrder(6);
	//CreateProgrammaticOrder(8);
	//CreateProgrammaticOrder(4);
	//CreateProgrammaticOrder(1);
	//CreateProgrammaticOrder(2);
}

//The main menu that the user is presented with
void Interface::MainMenu() {

	int input;

	//variable used to keep track of when to close the app
	bool exit = false;

	do {

		//tells the user what inputs there are
		std::cout << "Enter what number you want to do below" << std::endl;
		std::cout << "1. Create a new order" << std::endl;
		std::cout << "2. Delete an order" << std::endl;
		std::cout << "3. View all orders in a marina simulation" << std::endl;
		std::cout << "4. Show all orders in console" << std::endl;
		std::cout << "5. Exit program" << std::endl;
		std::cout << "6. Help" << std::endl;

		//takes the input
		std::cin >> input;

		//makes sure that the user entered a numerical input
		if (NumericalInput()) {

			//checks what the input was
			switch (input) {

				case 1:
				system("CLS");
				TakeOrder();
				break;


				case 2:
				system("CLS");
				DeleteOrder();
				break;


				case  3:
				system("CLS");
				Simulation();
				break;


				case 4:
				system("CLS");
				ShowAllOrders();

				std::cout << "Press enter to continue" << std::endl;
				std::cin.ignore();
				std::cin.get();

				//REFERENCE https://cboard.cprogramming.com/cplusplus-programming/80399-why-doesnt-cin-get-pause-program.html
				system("CLS");
				break;


				case  5:
				system("CLS");
				exit = Exit();
				break;


				case 6:
				system("CLS");
				Help();
				break;


				default:
				system("CLS");
				std::cout << "Please enter one of the numbers shown above." << std::endl << std::endl << std::endl;
				break;
			}
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

	FindTimeIntervals();

	system("CLS");

	TakeUserName();

	system("CLS");

	TakeBoatName();

	system("CLS");

	TakeBoatType();

	system("CLS");

	CalculateCosts();

	system("CLS");

	ConfirmEntries();
}

//takes the user input for the boat depth
void Interface::TakeDepth(int maxDepth) {

	float input;

	//gets the depth of the boat being ordered for
	do {

		std::cout << "Enter the depth of the boat: ";

		//takes the input
		std::cin >> input;
		std::cout << std::endl;

		//makes sure that the user entered a numerical input
		if (NumericalInput()) {

			//checks to see if the input was within the bounds
			if (input <= maxDepth && input > 0) {
				order.depth = input;
			} else if (input > maxDepth) {
				system("CLS");
				std::cout << "This entry was too big (boat must be less than " << maxDepth << " meters deep" << std::endl;
			} else if (input <= 0) {
				system("CLS");
				std::cout << "A boat cannot be smaller than 0 meters deep!" << std::endl;
			}
		}

	} while (input > maxDepth || input <= 0);
}

//takes the user input for the boat length
void Interface::TakeLength(int maxLength) {

	float input = -1;

	//loops until a valid length was inputted
	do {

		//shows currently entered values
		std::cout << "Entered depth: " << order.depth << std::endl << std::endl;

		std::cout << "Enter the length of the boat: ";

		std::cin >> input;
		std::cout << std::endl;

		//makes sure that the user entered a numerical input
		if (NumericalInput()) {

			//checks to see if the input was within the bounds
			if (input <= maxLength && input > 0) {
				order.length = input;
			} else if (input > maxLength) {
				system("CLS");
				std::cout << "This entry was too big (the boat must be less than " << maxLength << " meteres long" << std::endl;
			} else if (input <= 0) {
				system("CLS");
				std::cout << "A boat cannot be less than 0 meters long!" << std::endl;
			}
		}

	} while (input > maxLength || input <= 0);
}

//outputs all the available times for a given boat length
void Interface::FindTimeIntervals() {

	bool endFound;

	std::vector<TimeStampIndexes> foundTimes;

	//loops through each month on the timetable
	for (int i = 0; i < timeTable.size(); i++) {

		//checks to see if there is enough space in the current start check month's length left
		if (TimeStamp::MAX_LENGTH - timeTable[i].GetLengthUsed() >= order.length) {

			endFound = false;

			//loops past the found start month
			for (int j = i + 1; j < timeTable.size(); j++) {

				//checks to see if the current end check month does not have enough space
				if (TimeStamp::MAX_LENGTH - timeTable[j].GetLengthUsed() < order.length) {

					//registers that there was an end month found
					endFound = true;

					//adds the found time gap to the list of times
					foundTimes.push_back(TimeStampIndexes(i, j - 1));

					//sets i to j so that the next set of available days can be found
					//because the current one is too small (i increments at the end)
					i = j;

					//stops searching for an end (once one was found)
					break;
				}
			}

			//checks to see if an end month was not found (end month search reached the end without finding a month that was too small)
			if (!endFound) {

				//saves that the end month would be the last month
				int foundCount = timeTable.size() - 1;

				//adds on the last month, because it is the final usable date
				foundTimes.push_back(TimeStampIndexes(i, foundCount));

				//stops searching for start months, as end of the list was reached 
				break;
			}
		}
	}

	system("CLS");

	TakeInterval(foundTimes);
}

//gets what interval the user wants to order for
void Interface::TakeInterval(std::vector<TimeStampIndexes> foundTimes) {

	int chosenIndex;

	bool repeat = false;

	TimeStampIndexes chosenInterval;

	if (foundTimes.size() != 0) {

		//loops until a correct input was entered
		do {

			//shows currently entered values
			std::cout << "Entered depth: " << order.depth << std::endl;
			std::cout << "Entered length: " << order.length << std::endl << std::endl;

			std::cout << "Below is a list of all the times that you can book. " << std::endl;

			for (int i = 0; i < foundTimes.size(); i++) {

				//outputs what month was found
				std::cout << i + 1 << ". " << timeTable[foundTimes[i].start].GetDate() << " until ";

				//outputs what end month was found
				std::cout << timeTable[foundTimes[i].end].GetDate() << std::endl;
			}

			std::cout << "Enter the number of the interval you want to book within: ";

			//takes an input
			std::cin >> chosenIndex;

			//makes sure that the user entered a numerical input
			if (NumericalInput()) {

				//sets the normalises the input to be zero based
				chosenIndex--;

				//checks to see if the input was wrong
				if (chosenIndex < 0 || chosenIndex >= foundTimes.size()) {

					system("CLS");

					std::cout << "Please enter the first number from the starting month you want" << std::endl << std::endl;

					//makes the input loop
					repeat = true;

				} else {

					//sets the chosen time to be the start time of the chosenIndex (I will set the end time later)
					chosenInterval = foundTimes[chosenIndex];

					//stops the input from looping
					repeat = false;
				}

			} else {

				//makes the input loop
				repeat = true;
			}

		} while (repeat);

		system("CLS");

		TakeStartMonth(chosenInterval);
	}
}

//gets the starting month from the user
void Interface::TakeStartMonth(TimeStampIndexes chosenInterval) {

	bool repeat = true;

	std::string input;

	int startingIndex = -1;

	do {

		//shows currently entered values
		std::cout << "Entered depth: " << order.depth << std::endl;
		std::cout << "Entered length: " << order.length << std::endl << std::endl;

		std::cout << "Enter the start date you want to order for (mm/yyyy format)" << std::endl;
		std::cout << "You can book from " << timeTable[chosenInterval.start].GetDate() << " until " << timeTable[chosenInterval.end].GetDate() << std::endl;

		std::cin >> input;

		//checks to see if there was more than 2 characters in the input
		if (input.length() > 2) {

			repeat = false;

			//checks to see if the first number was a "0"
			if (input.substr(0, 1) == "0") {

				//sets the input to the input without the first 0
				input = input.substr(1, input.length() - 1);
			}

		} else {

			//registers that the input was bad
			repeat = true;
		}

		//checks to see if there was a bad input (too short to be in a date format)
		if (!repeat) {

			//turns the input date into a time table index
			startingIndex = DateToIndex(input);

			//checks to see if the input was valid
			if (startingIndex == -1) {

				//registers that a good date was entered
				repeat = true;

			} else {

				//registers that a good date was entered
				repeat = false;
			}
		}

		system("CLS");

		//checks to see if there was a bad input
		if (repeat)

			//tells the user that there was a bad input
			std::cout << "Please enter a valid date" << std::endl << std::endl;

	} while (repeat);

	//saves where what index of timestamps the chosen date was from
	order.timings.start = startingIndex;
	order.timings.end = chosenInterval.end;

	system("CLS");

	TakeEndMonth();
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
		std::cout << "Start: " << timeTable[order.timings.start].GetDate() << std::endl << std::endl;

		//finds out how many months can be booked
		int availableMonths = order.timings.end - order.timings.start;

		//asks how many months were wanted
		std::cout << "You can book for:  " << availableMonths << " months." << std::endl;
		std::cout << "How many months do you want to book for (you must book for atleast one month)" << std::endl;

		//gets the input
		std::cin >> input;

		//makes sure that the user entered a numerical input
		if (NumericalInput()) {

			//checks to see if a correct number was inputed (bigger than 0 and within the available months)
			if (input > 0 && input <= availableMonths) {

				//sets the end date
				order.timings.end = order.timings.start + input;

				//stops the input from looping
				repeat = false;

			} else {

				//clears the screen
				system("CLS");

				//lets the user know that their input was invalid
				std::cout << "Please enter a valid number of months" << std::endl << std::endl;

				//makes the input loop
				repeat = true;
			}

		} else {

			//makes the input loop
			repeat = true;
		}

		//repeats until a valid end month was entered
	} while (repeat);
}

//takes the first name of the person making the order
void Interface::TakeUserName() {

	//shows currently entered values
	std::cout << "Entered depth: " << order.depth << std::endl;
	std::cout << "Entered length: " << order.length << std::endl;
	std::cout << "Start: " << timeTable[order.timings.start].GetDate() << std::endl;
	std::cout << "End: " << timeTable[order.timings.end].GetDate() << std::endl << std::endl;

	std::cout << "Enter your name: ";
	std::cin.ignore();
	std::getline(std::cin, order.name);
}

//takes the name of the boat
void Interface::TakeBoatName() {

	//shows currently entered values
	std::cout << "Entered depth: " << order.depth << std::endl;
	std::cout << "Entered length: " << order.length << std::endl;
	std::cout << "Start: " << timeTable[order.timings.start].GetDate() << std::endl;
	std::cout << "End: " << timeTable[order.timings.end].GetDate() << std::endl;
	std::cout << "Name: " << order.name << std::endl << std::endl;

	std::cout << "Enter your boats name: ";

	//std::cin.ignore();
	std::getline(std::cin, order.boatName);
}

//takes the type of the boat
void Interface::TakeBoatType() {

	std::string input;
	bool repeat = false;

	//loops until a correct end time was entered
	do {

		//shows currently entered values
		std::cout << "Entered depth: " << order.depth << std::endl;
		std::cout << "Entered length: " << order.length << std::endl;
		std::cout << "Start: " << timeTable[order.timings.start].GetDate() << std::endl;
		std::cout << "End: " << timeTable[order.timings.end].GetDate() << std::endl;
		std::cout << "Name: " << order.name << std::endl;
		std::cout << "Boat name: " << order.boatName << std::endl << std::endl;


		//asks the user what type their boat is
		std::cout << "What is your boat type?" << std::endl;
		std::cout << "Please enter one of the letters presented below" << std::endl;
		std::cout << "(N): Narrow" << std::endl;
		std::cout << "(S): Sail" << std::endl;
		std::cout << "(M): Motor" << std::endl;

		//gets the input
		std::cin >> input;

		//turns the input to upper case
		std::transform(input.begin(), input.end(), input.begin(), ::toupper);

		//checks if the input was valid
		if (input == "N") {

			//sets the boat type
			order.type = "Narrow";
			repeat = false;

		} else if (input == "S") {

			//sets the boat type
			order.type = "Sail";
			repeat = false;

		} else if (input == "M") {

			//sets the boat type
			order.type = "Motor";
			repeat = false;

		} else {

			//lets the user know to enter a correct value
			system("CLS");
			std::cout << "Please enter one of the available letters" << std::endl << std::endl;
			repeat = true;
		}

		//repeats until a valid type was entered
	} while (repeat);
}

//calculates the cost using 10*length*months
void Interface::CalculateCosts() {

	order.cost = 10 * order.length * (order.timings.end - order.timings.start);
}

//outputs all the given inputs and asks for confirmation
void Interface::ConfirmEntries() {

	bool repeat = false;

	do {

		std::cout << "Below are your entries. Are they correct?" << std::endl << std::endl;

		//shows currently entered values
		std::cout << "Entered depth: " << order.depth << std::endl;
		std::cout << "Entered length: " << order.length << std::endl;
		std::cout << "Start: " << timeTable[order.timings.start].GetDate() << std::endl;
		std::cout << "End: " << timeTable[order.timings.end].GetDate() << std::endl;
		std::cout << "Name: " << order.name << std::endl;
		std::cout << "Boat name: " << order.boatName << std::endl;
		std::cout << "Boat type: " << order.type << std::endl;
		std::cout << "Cost: " << order.cost << " pounds" << std::endl << std::endl;

		std::cout << "Enter (y or n): ";
		std::string input;
		std::cin >> input;

		if (input == "y" || input == "Y") {

			repeat = false;

			RegisterOrder(order);

			WriteToFile(order);

			system("CLS");
			std::cout << "Payment registered, order added to system" << std::endl << std::endl;

		} else if (input == "n" || input == "N") {

			repeat = false;

			system("CLS");
			std::cout << "Transaction cancelled" << std::endl << std::endl;

		} else {
			repeat = true;

			system("CLS");
			std::cout << "Please enter either y or n" << std::endl << std::endl;
		}
	} while (repeat);
}

//outputs all the orders
void Interface::ShowAllOrders() {

	//makes sure that there are orders to output
	if (allOrders.size() != 0)

		//loops through each order
		for (int i = 0; i < allOrders.size(); i++) {

			//outputs the vital info about each order
			std::cout << allOrders[i].name << std::endl;
			std::cout << "Boat: " << allOrders[i].boatName << std::endl;
			std::cout << "Length: " << allOrders[i].length << "m" << std::endl;
			std::cout << "Type: " << allOrders[i].type << std::endl;
			std::cout << "Start: " << timeTable[allOrders[i].timings.start].GetDate() << std::endl;
			std::cout << "End: " << timeTable[allOrders[i].timings.end].GetDate() << std::endl << std::endl;
		}

	else

		std::cout << "There are no orders yet" << std::endl;
}

//allows the user to delete a user
void Interface::DeleteOrder() {

	std::string boatName;
	std::string startDate;
	int dateIndex = -1;


	std::cout << "Enter your boat name: " << std::endl;
	std::cin.ignore();
	std::getline(std::cin, boatName);

	std::cout << "Enter your order start date (no leading 0s): " << std::endl;
	std::cin >> startDate;

	//loops through the timetable
	for (int i = 0; i < timeTable.size(); i++) {

		//checks to see if the date was the same as the input
		if (timeTable[i].GetDate() == startDate) {

			//saves the index
			dateIndex = i;

			//stops searching
			break;
		}
	}

	//checks to see if the date was valid
	if (dateIndex != -1) {

		int orderIndex = -1;

		//loops through the orders
		for (int i = 0; i < allOrders.size(); i++) {

			//checks to see if the input details were correct
			if (allOrders[i].boatName == boatName && allOrders[i].timings.start == dateIndex) {

				//saves the index of the order
				orderIndex = i;

				break;
			}
		}

		//checks to see if an order was found
		if (orderIndex != -1) {

			system("CLS");

			std::cout << "Boat name: " << boatName << std::endl;

			std::string input;

			std::cout << "Are you sure you want to delete this (y/n)" << std::endl;

			std::cin >> input;

			if (input == "y" || input == "Y") {

				allOrders.erase(allOrders.begin() + orderIndex);

				system("CLS");
				std::cout << "Order has been erased" << std::endl;

			} else {
				system("CLS");
				std::cout << "Deletion cancelled" << std::endl;
			}

		} else {
			system("CLS");
			std::cout << "That order was not found" << std::endl;
		}

	} else {
		system("CLS");
		std::cout << "That date was not valid" << std::endl;
	}
}

//simulation sequence
void Interface::Simulation() {

	//makes the environement for the simulation
	Environment e = Environment(allOrders, timeTable);
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

//shows help/advice about the program
void Interface::Help() {

	std::cout << "Once a booking has been made" << std::endl;
	std::cout << "You can arrive at the start of your start month" << std::endl;
	std::cout << "You must leave at the end of your end month" << std::endl << std::endl << std::endl;

	std::cout << "Showing all orders in the console is in the order that the orders came in" << std::endl;
	std::cout << "To see a chronological order, enter the simulation" << std::endl << std::endl << std::endl;

	std::cout << "Loading an order from the text file will remove any order \nthat is out of date (an order that ends before the current date)" << std::endl << std::endl << std::endl;

	std::cout << "Once in the simulation, you will be told what month the simulation is currently in" << std::endl;
	std::cout << "The name of a boat will be constrained to 8 letters long (for formattings sake)" << std::endl;
	std::cout << "To progress the simulation, press enter. You have to press enter after each action" << std::endl;
	std::cout << "An action is: moving a boat to hold, removing a boat, moving a boat back from hold, adding a new boat" << std::endl;
	std::cout << "The simulation will end if: the last month is reached or if there are no more boats left to add" << std::endl << std::endl << std::endl;

	std::cout << "Press enter to continue" << std::endl;
	std::cin.ignore();
	std::cin.get();

	system("CLS");
}