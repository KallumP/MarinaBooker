#pragma once

#include "TimeStamp.h"

#include <iostream>
#include <vector>



struct Timeings {
	Timeings(int _start, int _end) {
		start = _start;
		end = _end;
	}
	Timeings() {
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
	Timeings timeings;
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
	void TakeInterval(std::vector<Timeings> foundTimes);
	void TakeStartMonth(Timeings chosenInterval);
	void TakeEndMonth();
	void TakeName();
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

