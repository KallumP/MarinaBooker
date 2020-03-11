#include "Environment.h"
#include "ListItem.h"
#include "Boat.h"

Environment::Environment() {
}

Environment::Environment(std::vector<Order> allOrders, int simLength) {

	marina = Marina();
	currentMonth = 0;
	maxMonth = simLength;
	SetupBoatEntryOrder(allOrders);
	Loop();
	//TestAllDeletes();
}

Environment::~Environment() {

}

void Environment::SetupBoatEntryOrder(std::vector<Order> allOrders) {

	//instantiates the linked list
	spawnOrder = LinkedList();

	//loops through each of the orders
	for (int i = 0; i < allOrders.size(); i++)

		//adds the right type of boat
		if (allOrders[i].type == "Narrow")

			//adds a list item to the linked list
			spawnOrder.AddItem(ListItem(Narrow(
				allOrders[i].length,
				allOrders[i].depth,
				allOrders[i].timings.start,
				allOrders[i].timings.end,
				allOrders[i].boatName)));

		else if (allOrders[i].type == "Sail")

			//adds a list item to the linked list
			spawnOrder.AddItem(ListItem(Sailing(
				allOrders[i].length,
				allOrders[i].depth,
				allOrders[i].timings.start,
				allOrders[i].timings.end,
				allOrders[i].boatName)));

		else if (allOrders[i].type == "Motor")

			//adds a list item to the linked list
			spawnOrder.AddItem(ListItem(Motor(
				allOrders[i].length,
				allOrders[i].depth,
				allOrders[i].timings.start,
				allOrders[i].timings.end,
				allOrders[i].boatName)));

	run = true;
}

void Environment::Loop() {

	//clears the screen
	system("CLS");

	std::cin.ignore();

	while (run) {

		//sends an update with the new month to the marina
		marina.NextMonth(currentMonth);

		//loops if the first boat in the linked list needs to enter the marina
		while (spawnOrder.GetStart() != nullptr && spawnOrder.GetStart()->GetBoat().GetEnter() == currentMonth) {

			//spawns the first boat from the linked list into the marina
			marina.SpawnBoat(spawnOrder.GetStart()->GetBoat());

			//removes the boat that just entered the marina, from the linked list
			spawnOrder.DeleteItem(spawnOrder.GetStart());
		}

		//lets the user proceed into the next month on their own time
		std::cout << std::endl << "Press any button to enter the next month" << std::endl;
		std::cin.get();
		system("CLS");

		currentMonth++;

		//checks to see if the simulation should stop
		if (currentMonth >= maxMonth)
			run = false;

		else if (spawnOrder.GetStart() == nullptr) {
			run = false;
			std::cout << "There are no more boats in the simulation" << std::endl;
		}

		//checks to see if the marina still has boats to work with
		if (!marina.Empty())
			run = true;
	}

	std::cout << "Thats the end of the simulation" << std::endl;
	std::cout << "Press any button to return back to the menu" << std::endl;
	std::cin.get();
	system("CLS");
}

void Environment::TestAllDeletes() {

	//outputs all the boats
	spawnOrder.OutputBoats(true);
	std::cin.ignore();
	std::cin.get();

	//deletes the first item from the list
	spawnOrder.DeleteItem(spawnOrder.GetStart());
	spawnOrder.OutputBoats(true);
	std::cin.get();

	//deletes a center item from the list
	spawnOrder.DeleteItem(spawnOrder.GetStart()->GetNextPointer()->GetNextPointer());
	spawnOrder.OutputBoats(true);
	std::cin.get();

	//deletes the last item in the list
	spawnOrder.DeleteItem(spawnOrder.GetEnd());
	spawnOrder.OutputBoats(true);
	std::cin.get();

	//delets the only item in the list
	spawnOrder.DeleteItem(spawnOrder.GetEnd());
	spawnOrder.OutputBoats(true);
	std::cin.get();

}