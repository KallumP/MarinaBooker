#include "Environment.h"
#include "ListItem.h"

Environment::Environment() {
}

Environment::Environment(std::vector<Order> allOrders) {

	marina = Marina();
	SetupBoatEntryOrder(allOrders);
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

	//outputs the linked list
	spawnOrder.OutputBoats(true);
	spawnOrder.OutputBoats(false);

	std::cout << "Press enter to continue" << std::endl;
	std::cin.ignore(); 
	std::cin.get();

	system("CLS");
}

void Environment::Loop() {

	while (running) {

	}
}

void Environment::Proccess() {

}

void Environment::Draw() {

}