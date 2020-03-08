#pragma once
#include "Boat.h"
#include "Marina.h"
#include "Order.h"
#include "LinkedList.h"

#include <iostream>
#include <vector>

class Environment {

public:

	Environment();
	Environment(std::vector<Order> allOrders, int simLength);
	~Environment();

private:
	void SetupBoatEntryOrder(std::vector<Order> allOrders);
	void Loop();
	void Proccess();
	void Draw();

	void TestAllDeletes();

	LinkedList spawnOrder;
	Marina marina;

	int currentMonth;
	int maxMonth;

	bool run;
};

