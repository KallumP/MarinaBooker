#include "Environment.h"
#include "ListItem.h"

Environment::Environment() {
}

Environment::Environment(std::vector<Order> allOrders) {

	marina = Marina();
	SetupBoatEntryOrder(allOrders);
	//Loop();
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

	TestAllDeletes();

	std::cout << "Press enter to continue" << std::endl;
	std::cin.ignore(); 
	std::cin.get();

	system("CLS");
}

void Environment::Loop() {

	//clears the screen
	system("CLS");

	while (run) {

		std::cin.get();

	}
}

void Environment::Proccess() {

}

void Environment::Draw() {

}

void Environment::TestAllDeletes() {

	spawnOrder.OutputBoats(true);
	std::cin.ignore();
	std::cin.get();

	spawnOrder.DeleteItem(spawnOrder.start);
	spawnOrder.OutputBoats(true);
	std::cin.get();

	spawnOrder.DeleteItem(&spawnOrder.boatSpawnOrder[2]);
	spawnOrder.OutputBoats(true);
	std::cin.get();

	spawnOrder.DeleteItem(spawnOrder.end);
	spawnOrder.OutputBoats(true);
	std::cin.get();

	spawnOrder.DeleteItem(spawnOrder.end);
	spawnOrder.OutputBoats(true);
	std::cin.get();

}