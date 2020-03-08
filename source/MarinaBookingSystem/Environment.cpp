#include "Environment.h"
#include "ListItem.h"

Environment::Environment() {
}

Environment::Environment(std::vector<Order> allOrders, int simLength) {

	marina = Marina();
	currentMonth = 0;
	maxMonth = simLength;
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

	//TestAllDeletes();

	//std::cout << "Press enter to continue" << std::endl;
	//std::cin.ignore(); 
	//std::cin.get();

	//system("CLS");
}

void Environment::Loop() {

	//clears the screen
	system("CLS");

	while (run) {

		//loops if the first boat in the linked list needs to enter the marina
		while (spawnOrder.start->GetBoat().GetEnter() == currentMonth) {

			//spawns the first boat from the linked list into the marina
			marina.SpawnBoat(spawnOrder.start->GetBoat());

			//removes the boat that just entered the marina, from the linked list
			spawnOrder.DeleteItem(spawnOrder.start);
		}



		std::cin.get();

		currentMonth++;

		//checks to see if the simulation should stop
		if (currentMonth >= maxMonth)
			run = false;

	}

	std::cin.get();
}

void Environment::Proccess() {

}

void Environment::Draw() {

	/*
	
	current month

	//keep track of the draw line (start at 0)

	draw out the spawnOrder[drawLine]

	draw out the marina[drawLine]
	
	draw out the hold[drawLine]

	end line 




	length Left in current month



	drawLine += 1;

	
	from the 

	


	
	*/




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