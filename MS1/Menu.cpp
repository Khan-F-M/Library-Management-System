/*
Final Project Milestone 1
Module: Menu
Filename: Menu.cpp
Author	Muhammad F. Khan
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring> 
#include "Menu.h"
#include "Utils.h"
using namespace std;

namespace sdds {
	MenuItem::MenuItem() { 
		m_str = nullptr;
	}

	MenuItem::MenuItem(const char* str) { 
		if (str != nullptr && str[0]) {
			m_str = new char[strlen(str) + 1];
			strcpy(m_str, str);
		}
		else {
			m_str = nullptr;
		}
	}

	MenuItem::operator bool()const { 
		return m_str[0] != '\0';
	}

	MenuItem::operator const char* ()const {
		return m_str;
	}

	ostream& MenuItem::display(std::ostream& ostr)const { 
		if (m_str != nullptr && m_str[0]) {
			ostr << m_str << endl;
		}

		return ostr;
	}

	MenuItem::~MenuItem() {
		delete[] m_str;
	}

	Menu::Menu() {
		mT_str.m_str = nullptr;
	}

	Menu::Menu(const char* Tstr) {
		if (Tstr != nullptr && Tstr[0] != '\0') {
			mT_str.m_str = new char[strlen(Tstr) + 1];
			strcpy(mT_str.m_str, Tstr);
		}
		else {
			mT_str.m_str = nullptr;

		}
	}

	ostream& Menu::displayTitle(std::ostream& ostr)const {
		if (mT_str.m_str != nullptr && mT_str.m_str[0] != '\0') {
			ostr << mT_str.m_str;
		}

		return ostr;
	}

	ostream& Menu::displayMenuItems(std::ostream& ostr)const {

		if (mT_str.m_str != nullptr && mT_str.m_str[0] != '\0') {
			ostr << mT_str.m_str << ":" << endl;
		}

		for (int i = 0; i < counter; i++) {
			cout << " " << i + 1 << "- ";
			arr[i]->display(ostr);
		}
		ostr << " 0- Exit\n" << "> ";

		return ostr;
	}

	unsigned int Menu::run()const {
		displayMenuItems();
		return GetInput(counter);
	}

	Menu& Menu::operator<<(const char* menuitemConent) {
		if (counter < MAX_MENU_ITEMS) {
			if (menuitemConent != nullptr && menuitemConent[0] != '\0') {
				arr[counter] = new MenuItem(menuitemConent);
				counter++;
			}
		}
		return *this;
	}


	Menu::operator int()const {
		return counter;
	}

	Menu::operator unsigned int()const {
		return counter;
	}

	Menu::operator bool()const {
		return counter >= 1;
	}

	const char* Menu::operator[](int index)const { 
		if (index % counter == 0) {
			index = 0;
		}
		return *this->arr[index];
	}

	Menu::~Menu() {
		for (int i = 0; i < counter; i++) {
			delete arr[i];
		}
	}

	int operator~(const Menu& left) {
		return left.run();
	}

	ostream& operator<<(std::ostream& ostr, const Menu& left) {
		return left.displayTitle(ostr);
	}
}
