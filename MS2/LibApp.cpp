/*
Final Project Milestone 2
Module: LibApp
Filename: LibApp.cpp
Author	Muhammad F. Khan
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#include <iostream>
#include "Menu.h"
#include "LibApp.h"
using namespace std;

namespace sdds {

	LibApp::LibApp() : m_changed(false),
		m_mainMenu("Seneca Library Application"),
		m_exitMenu("Changes have been made to the data, what would you like to do?")
	{

		m_mainMenu << "Add New Publication"
			<< "Remove Publication"
			<< "Checkout publication from library"
			<< "Return publication to library";

		m_exitMenu << "Save changes and exit"
			<< "Cancel and go back to the main menu";

		load();
	}

	void LibApp::run() {
		int choice, pick, decide;
		bool temp = true;

		while (temp == true)
		{
			choice = m_mainMenu.run();

			if (choice == 1) { 
				newPublication();
				cout << endl;
			}
			else if (choice == 2) {
				removePublication();
				cout << endl;
			}
			else if (choice == 3) {
				checkOutPub();
				cout << endl;
			}
			else if (choice == 4) {
				returnPub();
				cout << endl;
			}
			else {
			if (m_changed == false) {
					temp = false;
				}
				else if(m_changed == true) {
					pick = m_exitMenu.run();
					if (pick == 1) {
						save();
						temp = false;
					}
					else if (pick == 2) {
						temp = true;
						cout << endl;
					}
					else {
						decide = confirm("This will discard all the changes are you sure?");
						if (decide == 1) {
							temp = false;
						}
						else {
							temp = true;
						}
					}
				}
			}
		}

		cout << "\n-------------------------------------------" << endl;
		cout << "Thanks for using Seneca Library Application" << endl;
	}

	bool LibApp::confirm(const char* message) {
		Menu temp(message);
		temp << "Yes";

		int pck = temp.run();
		if (pck == 1) {
			return true;
		}
		else {
			return false; 
		}
	}

	void LibApp::load() {
		cout << "Loading Data" << endl;
	}

	void LibApp::save() {
		cout << "Saving Data" << endl;
	}

	void LibApp::search() {
		cout << "Searching for publication" << endl;
	}

	void LibApp::returnPub() {
		search();
		cout << "Returning publication" << endl;
		cout << "Publication returned" << endl;
		m_changed = true;
	}

	void LibApp::newPublication() { 
		cout << "Adding new publication to library" << endl;

		int Answer = confirm("Add this publication to library?");
		if (Answer == 1) {
			m_changed = true;
			cout << "Publication added" << endl;
		}
	}

	void LibApp::removePublication() {
		cout << "Removing publication from library" << endl;

		search();
		int Answer = confirm("Remove this publication from the library?");
		if (Answer == 1) {
			m_changed = true;
			cout << "Publication removed" << endl;
		}
	}

	void LibApp::checkOutPub() {


		search();
		int Answer = confirm("Check out publication?");
		if (Answer == 1) {
			m_changed = true;
			cout << "Publication checked out" << endl;
		}
	}

}
