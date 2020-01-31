#pragma once

#include "TimeStamp.h"
#include "BoatOrder.h"

#include <iostream>
#include <vector>



struct FoundTime {
	FoundTime(int _start, int _end) {
		start = _start;
		end = _end;
	}
	FoundTime() {
		start = 0;
		end = 0;
	}
	int start;
	int end;
};

struct CurrentOrder {
	float depth;
	float width;
	float length;
	std::string name;
	FoundTime timeings;
};

class Interface {

public:
	Interface();
	~Interface();

private:
	void LoadOrders();
	void MainMenu();
	void TakeOrder();
	void DeleteOrder();
	void Simulation();
	bool Exit();
	FoundTime GetStartAndEnd(float length);

	void ConfirmEntries();

	std::vector<TimeStamp> timeTable;
	BoatOrder allOrders;
	CurrentOrder order;
};

