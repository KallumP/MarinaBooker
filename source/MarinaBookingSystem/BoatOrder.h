#pragma once
#include <iostream>

class BoatOrder {

public:

	BoatOrder();
	~BoatOrder();


private:

	float height, width, length;
	
	int orderNumberTracker;
	int orderNumber;
	//_TIMESTAMP_ startTime
	//_TIMESTAMP_ endTime

	std::string customerName;
};

