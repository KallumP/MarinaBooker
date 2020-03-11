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
	if (comeBack) {

		std::cin.get();

		//makes the front most boat enter the hold
		holdingBoats.push_back(marinaBoats[0]);

		//removes the front most boat from the hold
		marinaBoats.erase(marinaBoats.begin());

	} else {

		std::cin.get();

		//removes the front most boat from the hold
		marinaBoats.erase(marinaBoats.begin());
	}

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

	Boat normalized = toSpawn;

	//checks to see if the name is bigger than 8 characters
	if (toSpawn.GetName().size() > 8)

		//only takes the first 8 characters
		normalized.SetName(toSpawn.GetName().substr(0, 8));

	marinaBoats.push_back(normalized);

	Draw();
}

//draws out the status of the marina
void Marina::Draw() {

	system("CLS");

	int drawLine = 0;
	bool drawAgain = true;

	std::cout << "The current month is: " << currentMonth << std::endl;


	int lengthLeft = 150;

	//goes through each boat
	for (int i = 0; i < marinaBoats.size(); i++)

		//registers how much length the boat takes up
		lengthLeft -= marinaBoats[i].GetLength();

	//outputs the length left
	std::cout << "Length left: " << lengthLeft << "m" << std::endl << std::endl;


	int consoleMoveHold = 40;
	int consoleMoveMarina = 0;

	MoveCursor(consoleMoveMarina, 2);
	std::cout << "Marina";

	MoveCursor(consoleMoveHold, 2);
	std::cout << "Hold" << std::endl;

	//keeps looping while there are more boats to draw
	while (drawAgain) {

		//checks to see if there was another line to draw in the marinas
		if (marinaBoats.size() > drawLine) {

			//draws to the left most side of the console
			MoveCursor(consoleMoveMarina, drawLine + 3);

			//draws out the marina boat
			std::cout << "Boat: " << marinaBoats[drawLine].GetName() << " leaves at: " << marinaBoats[drawLine].GetLeave() << "   ";
		}

		//checks to see if there was another line to draw in the marinas
		if (holdingBoats.size() > drawLine) {

			//moves accross in the console by 20 pixels
			MoveCursor(consoleMoveHold, drawLine + 3);

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

	//REFERENCE https://docs.microsoft.com/en-us/windows/console/setconsolecursorposition
}

//returns if the marina is empty
bool Marina::Empty() {

	//checks to see if there were any boats in the marina or hold
	if (marinaBoats.size() == 0 && holdingBoats.size() == 0)
		return true;

	return false;
}