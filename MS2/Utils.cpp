/*
Final Project Milestone 1
Module: Menu
Filename: Util.cpp
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

	bool CheckInput(const char* pick) {
		bool temp = true;

		for (int i = 0; pick[i] != '\0' && temp == true; i++) {

			if (!isdigit(pick[i])) {
				temp = false;
			}
		}
		return temp;
	}

	int GetInput(int count) {

		bool temp = false;
		int choice = 0;
		char pick[20];

		do {
			cin >> pick;
			cin.ignore(2000, '\n');
			choice = atoi(pick);

			if (!CheckInput(pick)) {
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
