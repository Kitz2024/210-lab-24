// Kit Pollinger
//  210 - Lab - 24 | Fork with set
#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(set<Goat> trip);
void delete_goat(set<Goat> &trip);
void add_goat(set<Goat> &trip, string[], string[]);
void display_trip(set<Goat> trip);
int main_menu();

int main()
{
    int userChoice = main_menu();

    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++])
        ;
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++])
        ;
    fin1.close();

    set<Goat> trip;
    while (userChoice != 4)
    {
        switch (userChoice)
        {
        case 1:
            add_goat(trip, names, colors);
            break;
        case 2:
            delete_goat(trip);
            break;
        case 3:
            display_trip(trip);
            break;
        }
        cin.ignore();
        userChoice = main_menu();
    }

    return 0;
}

int main_menu()
{
    int userChoice;
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Quit\n";
    cout << "Choice --> ";
    cin >> userChoice;

    while (userChoice < 1 || userChoice > 4)
    {
        cout << "Error, Enter a number between 1 and 4: ";
        cin >> userChoice;
    }

    return userChoice;
}
void add_goat(set<Goat> &trip, string names[], string colors[])
{
    // Check if the names array is empty
    if (names[0].empty()) {
        cout << "Error: No names found in the names.txt file.\n";
        return;
    }
    int nameIndex = rand() % SZ_NAMES;
    while (names[nameIndex].empty()) {
        nameIndex = rand() % SZ_NAMES;
    }
    string name = names[nameIndex];
    string color = colors[rand() % SZ_COLORS];
    int age = rand() % (MAX_AGE + 1);
    Goat newGoat(name, age, color);
    trip.insert(newGoat);
    cout << name << " (" << age << ", " << color << ") has been added to the trip!\n";
}
void delete_goat(set<Goat> &trip)
{
     int index = select_goat(trip);
    if (index != -1) {
        set<Goat>::iterator it = trip.begin();
        advance(it, index - 1);
        trip.erase(it);
        cout << "Goat deleted successfully!\n";
    } else {
        cout << "No goat selected or trip is empty.\n";
    }
}

int select_goat(set<Goat> trip)
{
    if (trip.empty()) {
        cout << "No goats in the trip. \n";
        return -1;
    }
    cout << "\nSelect a goat to delete (corresponding):\n";
    int i = 1;
    for (const Goat& goat : trip) {
        cout << "[" << i++ << "] " << goat.get_name() << " (" << goat.get_age() << ", " << goat.get_color() << ")\n";
    }
    int choice;
    cin >> choice;

    while (choice < 1 || choice > trip.size()) {
        cout << "Error, Enter a number between 1 and " << trip.size() << ": ";
        cin >> choice;
    }
    return choice - 1;
}

void display_trip(set<Goat> trip)
{
    if (trip.empty())
    {
        cout << "No goats in the trip. \n";
        return;
    }
    int i = 1;
    for (const Goat& goat : trip)
    {
        cout << setw(3) <<"[" << i++ <<"]" << setw(5) << goat.get_name() << setw(2) << "(" << goat.get_age() << "," << setw(5) << goat.get_color() << ")" << endl;
    }
}
