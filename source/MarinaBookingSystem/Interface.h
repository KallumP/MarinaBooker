#pragma once

#include "TimeStamp.h"

#include <iostream>
#include <vector>



struct TimeStampIndexes {
	TimeStampIndexes(int _start, int _end) {
		start = _start;
		end = _end;
	}
	TimeStampIndexes() {
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
	std::string boatName;
	TimeStampIndexes timeings;
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
	void TakeInterval(std::vector<TimeStampIndexes> foundTimes);
	void TakeStartMonth(TimeStampIndexes chosenInterval);
	void TakeEndMonth();
	void TakeUserFirstName();
	void TakeUserLastName();
	void TakeBoatName();
	void CalculateCosts();
	void ConfirmEntries();

	void ShowAllOrders();
	void DeleteOrder();
	void Simulation();
	bool Exit();
	void Help();

	std::vector<TimeStamp> timeTable;
	std::vector<Order> allOrders;
	Order order;
};

