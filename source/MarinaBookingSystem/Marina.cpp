#include "Marina.h"

Marina::Marina() {
}

Marina::~Marina() {
}

//spawns in a new boat
void Marina::SpawnBoat(Boat toSpawn) {

	marinaBoats.push_back(toSpawn);
}

//removes from the marina
void Marina::RemoveBoat(Boat toRemove) {


}

//returns all boats in the hold to the marina
void Marina::ReturnAllHoldBoats() {

	//loops while there are boats in the hold
	while (holdingBoats.size != 0) {

		

	}
}

//does all the processing for the next month
void Marina::NextMonth(int newMonth) {

	//loops through each of the boats in the marina
	for (int i = 0; i < marinaBoats.size(); i++) {

		//checks to see if the current boat needs to leave
		if (marinaBoats[i].GetLeave() > newMonth) {


			RemoveBoat(marinaBoats[i]);
		}



	}
}