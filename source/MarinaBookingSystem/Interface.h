#pragma once
#include "TimeStamp.h"
#include "Order.h";

#include <iostream>
#include <vector>

class Interface {

public:
	Interface();
	~Interface();

private:
	void SetupTimeTable(int months);
	int DateToIndex(std::string date);

	void CreateProgrammaticOrder(int val);
	void LoadOrders();

	void MainMenu();

	void TakeOrder();
	void TakeDepth(int minDepth);
	void TakeLength(int minDepth);
	void FindTimeIntervals();
	void TakeInterval(std::vector<TimeStampIndexes> foundTimes);
	void TakeStartMonth(TimeStampIndexes chosenInterval);
	void TakeEndMonth();
	void TakeUserName();
	void TakeBoatName();
	void CalculateCosts();
	void ConfirmEntries();
	void RegisterOrder(Order newOrder);
	void WriteToFile(Order order);

	void ShowAllOrders();
	void DeleteOrder();
	void Simulation();
	bool Exit();
	void Help();

	std::vector<TimeStamp> timeTable;
	std::vector<Order> allOrders;
	Order order;

	std::string filePath = "order.txt";
};

