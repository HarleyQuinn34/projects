#include <iostream>
#include <string>
#include <ctime>
#include <Windows.h>
#include <cstdlib>
#include <time.h>
using namespace std;
void monster();
void convert(string& input);
string array[4];

int main() {
	int room = 1;
	string items[10];
	string input = "a";
	srand(time(NULL));
	cout << "You are alone" << endl;
	while (input != "quit") {
		switch (room) {
		case 1:
			cout << "YOU'RE IN ROOM 1." << endl;
			cout << "You are at the bottom of the ship." << endl;
			cout << "You can go (north) and (west). " << endl;

			getline(cin, input);
			if (input.compare("north") == 0)
				room = 4;
			else if (input.compare("west") == 0)
				room = 2;
			else if (input.compare("items") == 0) {
				cout << "Your items in your inventory" << endl;
				for (int i = 0; i<10; i++)
					cout << items[i] << endl;
			}
			else
				cout << "not an option unless you are quiting" << endl;
			break;
		case 2:
			cout << "YOU'RE IN ROOM 2." << endl;
			cout << "Room 2 is a directory and you see a map with all the rooms in the ship.Someone drew somthing on room 10, it says nest." << endl;
			cout << "You can go (north), (west), and (east). " << endl;

			getline(cin, input);
			if (input.compare("north") == 0)
				room = 5;
			else if (input.compare("west") == 0)
				room = 3;
			else if (input.compare("east") == 0)
				room = 1;
			else if (input.compare("items") == 0) {
				cout << "Your items in your inventory" << endl;
				for (int i = 0; i<10; i++)
					cout << items[i] << endl;
			}
			else
				cout << "not an option" << endl;
			break;
		case 3:
			cout << "YOU'RE IN ROOM 3." << endl;
			cout << "You look around and relize you are in a computer room.There is desk with a broken computer,phone and other tech ." << endl;
			cout << "There are pamplets about the lab that was used to be here.Type (read) if you want to read about the ship." << endl;
			cout << "You can go (north), and (east). " << endl;
			monster();
			getline(cin, input);
			if (input.compare("north") == 0)
				room = 6;
			else if (input.compare("east") == 0)
				room = 2;
			else if (input.compare("read") == 0)
				room = 11;
			else if (input.compare("items") == 0) {
				cout << "Your items in your inventory" << endl;
				for (int i = 0; i<10; i++)
					cout << items[i] << endl;
			}

			else
				cout << "not an option" << endl;

			break;
		case 4:
			cout << "YOU'RE IN ROOM 4" << endl;
			cout << "You look around and see medical aid objects and aid kits,there is a sink in the corner of the room." << endl;
			cout << "You can go (north), (west), and (south). " << endl;
			getline(cin, input);

			if (input.compare("north") == 0)
				room = 7;
			else if (input.compare("west") == 0)
				room = 5;
			else if (input.compare("south") == 0)
				room = 1;
			else if (input.compare("items") == 0) {
				cout << "Your items in your inventory" << endl;
				for (int i = 0; i<10; i++)
					cout << items[i] << endl;
			}
			if (items[9].compare("gas") != 0) {
				cout << "You find a gas canister left over from on old mission, you need thes for the flame thrower." << endl;
				cout << "type (gas) to pick it up." << endl;
			}

			getline(cin, input);
			if (input.compare("pdown") == 0)
				room = 3;
			else if (input.compare("key") == 0) {
				items[9] = "key";
				cout << "You got the key" << endl;
			}
			else
				cout << "not an option" << endl;
			break;
		case 5:
			cout << "YOU'RE IN ROOM 5." << endl;
			cout << "There is nothing in here.It is a completely empty room." << endl;
			cout << "You can go (north), (west), (south), and (east). " << endl;
			getline(cin, input);
			if (input.compare("west") == 0)
				room = 6;
			else if (input.compare("east") == 0)
				room = 4;
			else if (input.compare("items") == 0) {
				cout << "Your items in your inventory" << endl;
				for (int i = 0; i<10; i++)
					cout << items[i] << endl;
			}
			else if (input.compare("south") == 0)
				room = 2;
			else if (input.compare("north") == 0)
				if (items[9].compare("key") == 0) {
					cout << "unlocked door" << endl;
					room = 8;
				}
				else
					cout << "locked" << endl;
			break;
		case 6:
			cout << "YOU'RE 6." << endl;
			cout << "Seems like it is a storage closet." << endl;
			cout << "The is a bunch of empty flask,test tubes,hot plate burners and other things you will see in a science lab environment." << endl;
			cout << "You can go (north), (south), and (east). " << endl;
			getline(cin, input);
			monster();
			if (input.compare("north") == 0)
				room = 9;
			else if (input.compare("east") == 0)
				room = 5;
			else if (input.compare("south") == 0)
				room = 3;
			else if (input.compare("items") == 0) {
				cout << "Your items in your inventory" << endl;
				for (int i = 0; i<10; i++)
					cout << items[i] << endl;
			}
			else
				cout << "not an option" << endl;
			break;
		case 7:
			cout << "YOU'RE IN ROOM 7." << endl;
			cout << "Room 7 is the place where they did experiments.It has cages,emergency cleanup,and lab equipment that seems broken and burned." << endl;
			cout << "You can go (west), and (south). " << endl;
			getline(cin, input);
			monster();
			if (input.compare("south") == 0)
				room = 4;
			else if (input.compare("items") == 0) {
				cout << "Your items in your inventory" << endl;
				for (int i = 0; i<10; i++)
					cout << items[i] << endl;
			}

			if (input.compare("west") == 0)
				if (items[9].compare("key") == 0) {
					cout << "unlocked door" << endl;
					room = 8;
				}
				else
					cout << "locked" << endl;
			else
				cout << "not an option" << endl;
			break;
		case 8:
			cout << "YOU'RE IN ROOM 8." << endl;
			cout << "Room 8 is a locker rooom.Some of the lockers are open and some of the lockers are still locked." << endl;
			cout << "You can go (north), (south), (west), and (east). " << endl;
			getline(cin, input);
			monster();
			if (input.compare("north") == 0)
				room = 10;
			else if (input.compare("west") == 0)
				room = 9;
			else if (input.compare("south") == 0)
				room = 5;
			else if (input.compare("east") == 0)
				room = 7;
			else if (input.compare("items") == 0) {
				cout << "Your items in your inventory" << endl;
				for (int i = 0; i<10; i++)
					cout << items[i] << endl;
			}
			else
				cout << "not an option" << endl;
			break;
		case 9:
			cout << "YOU'RE IN ROOM 9." << endl;
			cout << "Room 9 is a caferteria.It has circle tables and chairs with refrigerators lined up with drinks still in them.The kitchen is  in the right corner of the room." << endl;
			cout << "You can go (south), and (east). " << endl;
			getline(cin, input);
			monster();
			if (input.compare("south") == 0)
				room = 6;
			else if (input.compare("items") == 0) {
				cout << "Your items in your inventory" << endl;
				for (int i = 0; i<10; i++)
					cout << items[i] << endl;
			}
			if (input.compare("east") == 0)
				if (items[9].compare("key") == 0) {
					cout << "unlocked door" << endl;
					room = 8;
				}
				else
					cout << "locked" << endl;
			else
				cout << "not an option" << endl;
			break;
		case 10:
			cout << "YOU'RE IN ROOM 10." << endl;
			cout << "Room 10 has big equipment and it looks like big experiments were performed in this room." << endl;
			cout << "It has larger cleanup stations.Larger machines and larger cages." << endl;
			cout << "THERE IS A KEYPAD ON THE WALL WITH LETTERS,NUMBERS,AND SYMBOLS." << endl;
			cout << "You can go (south). " << endl;
			getline(cin, input);
			monster();
			if (input.compare("south") == 0)
				room = 8;

			if (input.compare("go to keypad") == 0)
				room = 0;
			else
				cout << "not an option" << endl;
			if (items[1].compare("gas") == 0) {
				if (items[2].compare("barrel") == 0)
					cout << "you win! you teleport out of there" << endl;
				return 0;
			}

			cout << "You forgot the conducter or the stabilizer. You blow up because the teleporter was unstable" << endl;
			break;
		case 11:
			cout << "description (reading the book)" << endl;
			cout << "to stop reading type (pdown)." << endl;

			if (items[9].compare("key") != 0) {
				cout << "There is a key on a the ground. Type (key) to to pick it up." << endl;
			}

			getline(cin, input);
			if (input.compare("pdown") == 0)
				room = 3;
			else if (input.compare("key") == 0) {
				items[9] = "key";
				cout << "You got the key" << endl;
			}
			else
				cout << "not a option" << endl;


		}//switch
	}//while loop
}//ends main


void monster() {
	int number = rand() % 150 + 1;
	if (number <= 50)
		cout << "A wild alien popped upp holy sh******t" << endl;
	else if (number>50 && number <= 100)
		cout << "Oh no a robot hide!" << endl;
	else if (number>100 && number <= 150)
		cout << "Nothing is here" << endl;
	else
		cout << "Nothing" << endl;
}

void convert(string& input) {//toupper fucntion


	for (int i = 0; i < input.length(); i++) {
		input[i] = toupper(input[i]);
	}
}

