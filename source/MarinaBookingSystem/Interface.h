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

	bool NumericalInput();
	int DateToIndex(std::string);
	void RegisterOrder(Order);
	void WriteToFile(Order);
	void CreateProgrammaticOrder(int);

	void SetupTimeTable(int);
	void LoadOrders();

	void MainMenu();

	void TakeOrder();
	void TakeDepth(int);
	void TakeLength(int);
	void FindTimeIntervals();
	void TakeInterval(std::vector<TimeStampIndexes>);
	void TakeStartMonth(TimeStampIndexes);
	void TakeEndMonth();
	void TakeUserName();
	void TakeBoatName();
	void TakeBoatType();
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

	std::string filePath = "order.txt";
};

