#include "Marina.h"

#include <conio.h>
#include <Windows.h>

Marina::Marina() {
}

Marina::~Marina() {
}

//does all the processing for the next month
void Marina::NextMonth(int newMonth) {

	currentMonth = newMonth;

	Draw();

	bool boatsToReturn = false;

	//loops through each of the boats in the marina (from the start to the end)
	for (int i = 0; i < marinaBoats.size(); i++) {

		//checks to see if the current boat needs to leave
		if (marinaBoats[i].GetLeave() < currentMonth) {

			//makes the boat leave the marina
			RemoveBoat(i, false);

			//sets the iterator back to 0
			i = -1;

			boatsToReturn = true;
		}
	}

	//checks to see if there are any boats to return
	if (boatsToReturn)

		//makes all hold boats go back into the marina
		ReturnAllHoldBoats();
}

//removes from the marina
void Marina::RemoveBoat(int removeIndex, bool comeBack) {

	//checks to see if there were boats infront (this is not the front most boat)
	if (removeIndex != 0)

		//recursivley tells the next boat to leave to the hold
		RemoveBoat(removeIndex - 1, true);

	//once the recursive is done, the boat being handled with will ALWAYS be index 0

	//checks if the boat should go to the hold
	if (comeBack)

		//makes the front most boat enter the hold
		holdingBoats.push_back(marinaBoats[0]);

	std::cin.get();

	//removes the front most boat from the hold
	marinaBoats.erase(marinaBoats.begin());

	Draw();
}

//returns all boats in the hold to the marina
void Marina::ReturnAllHoldBoats() {

	//loops while there are boats in the hold
	while (holdingBoats.size() != 0) {

		std::cin.get();

		//adds the last boat in the hold, back to the start of the marina
		marinaBoats.insert(marinaBoats.begin(), holdingBoats[holdingBoats.size() - 1]);

		//removes the last boat in the hold
		holdingBoats.erase(holdingBoats.begin() + holdingBoats.size() - 1);

		Draw();
	}
}

//spawns in a new boat
void Marina::SpawnBoat(Boat toSpawn) {

	std::cin.get();

	marinaBoats.push_back(toSpawn);

	Draw();
}

//draws out the status of the marina
void Marina::Draw() {

	system("CLS");

	int drawLine = 0;
	bool drawAgain = true;

	std::cout << "The current month is: " << currentMonth << std::endl << std::endl;
	std::cout << "Marina";

	MoveCursor(35, 2);
	std::cout << "Hold" << std::endl;

	//keeps looping while there are more boats to draw
	while (drawAgain) {

		//checks to see if there was another line to draw in the marinas
		if (marinaBoats.size() > drawLine) {

			//draws to the left most side of the console
			MoveCursor(0, drawLine + 3);

			//draws out the marina boat
			std::cout << "Boat: " << marinaBoats[drawLine].GetName() << " leaves at: " << marinaBoats[drawLine].GetLeave() << "   ";
		}

		//checks to see if there was another line to draw in the marinas
		if (holdingBoats.size() > drawLine) {

			//moves accross in the console by 20 pixels
			MoveCursor(35, drawLine + 3);

			//draws out the holding boat
			std::cout << "Boat: " << holdingBoats[drawLine].GetName() << " leaves at: " << holdingBoats[drawLine].GetLeave() << "   ";
		}

		std::cout << std::endl;

		//increments what line to draw
		drawLine++;

		//checks to see if there was nothing more to draw
		if (marinaBoats.size() <= drawLine && holdingBoats.size() <= drawLine)

			//registers that the draw sequence should stop
			drawAgain = false;
	}
}

//moves the cursor of the console to the entered x and y
void Marina::MoveCursor(int x, int y) {

	//the buffer to write to
	HANDLE output_handle;

	//a coordiante structure used to hold the position to write to
	COORD pos;

	//sets the coordinates
	pos.X = x;
	pos.Y = y;

	//sets the buffer
	output_handle = GetStdHandle(STD_OUTPUT_HANDLE);

	//moves the cursor
	SetConsoleCursorPosition(output_handle, pos);
}
