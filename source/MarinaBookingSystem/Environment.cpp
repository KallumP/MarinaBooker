#include "Environment.h"
#include "ListItem.h"

Environment::Environment() {
}

Environment::Environment(std::vector<Order> allOrders, int simLength) {

	marina = Marina();
	currentMonth = 0;
	maxMonth = simLength;
	SetupBoatEntryOrder(allOrders);
	Loop();
}

Environment::~Environment() {

}

void Environment::SetupBoatEntryOrder(std::vector<Order> allOrders) {

	//instantiates the linked list
	spawnOrder = LinkedList(allOrders.size());

	//loops through each of the orders
	for (size_t i = 0; i < allOrders.size(); i++)

		//adds a list item to the linked list
		spawnOrder.AddItem(ListItem(Boat(
			allOrders[i].length,
			allOrders[i].depth,
			allOrders[i].timeings.start,
			allOrders[i].timeings.end,
			allOrders[i].boatName)));

	//allows the loop to start working
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
		while (spawnOrder.start != nullptr && spawnOrder.start->GetBoat().GetEnter() == currentMonth) {

			//spawns the first boat from the linked list into the marina
			marina.SpawnBoat(spawnOrder.start->GetBoat());

			//removes the boat that just entered the marina, from the linked list
			spawnOrder.DeleteItem(spawnOrder.start);
		}

		//lets the user proceed into the next month on their own time
		std::cout << std::endl << "Press any button to enter the next month" <<std::endl;
		std::cin.get();
		system("CLS");

		currentMonth++;

		//checks to see if the simulation should stop
		if (currentMonth >= maxMonth)
			run = false;

		else if (spawnOrder.start == nullptr) {
			run = false;
			std::cout << "There are no more boats in the simulation" << std::endl;
		}
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
	spawnOrder.DeleteItem(spawnOrder.start);
	spawnOrder.OutputBoats(true);
	std::cin.get();

	//deletes a center item from the list
	spawnOrder.DeleteItem(&spawnOrder.boatSpawnOrder[2]);
	spawnOrder.OutputBoats(true);
	std::cin.get();

	//deletes the last item in the list
	spawnOrder.DeleteItem(spawnOrder.end);
	spawnOrder.OutputBoats(true);
	std::cin.get();

	//delets the only item in the list
	spawnOrder.DeleteItem(spawnOrder.end);
	spawnOrder.OutputBoats(true);
	std::cin.get();

}