#include "Environment.h"
#include "ListItem.h"

Environment::Environment(std::vector<Order> allOrders) {

	marina = Marina();
	SetupBoatEntryOrder(allOrders);
}

Environment::~Environment() {

}


void Environment::SetupBoatEntryOrder(std::vector<Order> allOrders) {

	Boat toAdd;

	//loops through each of the orders
	for (size_t i = 0; i < allOrders.size(); i++) {

		toAdd = Boat(
			allOrders[i].length,
			allOrders[i].depth,
			allOrders[i].timeings.start,
			allOrders[i].timeings.end,
			allOrders[i].boatName);

		spawnOrder.AddItem(ListItem(toAdd));
	}

	spawnOrder.Output();
}

void Environment::Loop() {

	while (running) {

	}
}

void Environment::Proccess() {

}

void Environment::Draw() {

}