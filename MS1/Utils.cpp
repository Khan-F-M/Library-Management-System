/*
Final Project Milestone 1
Module: Menu
Filename: Menu.cpp
Author	Muhammad F. Khan
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#include <iostream>
#include <string>
#include "Menu.h"
#include "Utils.h"

using namespace std;
namespace sdds {

	int GetInput(int count) {

		bool temp = false;
		int choice = 0;
		char pick[20];

		do {
			cin >> pick;
			cin.ignore(2000, '\n');
			choice = atoi(pick);

			if (cin.fail()) {
				cout << "Invalid Selection, try again: ";
				temp = true;
			}
			else {
				if (choice < 0 || choice > count) {
					cout << "Invalid Selection, try again: ";
					temp = true;
				}
				else {
					return choice;
				}
			}
		} while (temp);
                return choice;
	}
}
