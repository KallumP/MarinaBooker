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

struct Order {
	float depth;
	float width;
	float length;
	std::string name;
	FoundTime timeings;
	float cost;
};

class Interface {

public:
	Interface();
	~Interface();

private:
	void LoadOrders();
	void MainMenu();


	void TakeOrder();
	void TakeDepth(int minDepth);
	void TakeLength(int minDepth);
	void FindTimeIntervals();
	void TakeStartMonth(std::vector<FoundTime> foundTimes);
	void TakeEndMonth();
	void TakeName();
	void CalculateCosts();
	void ConfirmEntries();


	void DeleteOrder();
	void Simulation();
	bool Exit();

	std::vector<TimeStamp> timeTable;
	std::vector<Order> allOrders;
	Order order;
};

