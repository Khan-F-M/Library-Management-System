/*
Final Project Milestone 1
Module: Menu
Filename: Menu.h
Author	Muhammad F. Khan
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__
#include <iostream>

namespace sdds {
	const int MAX_MENU_ITEMS = 20;
	class Menu;

	class MenuItem {
		char* m_str;
		MenuItem();
		MenuItem(const char* str);

		MenuItem(const MenuItem& nope) = delete;
		MenuItem& operator=(const MenuItem& nope) = delete;

		~MenuItem();
		operator bool()const;
		operator const char* ()const;

		std::ostream& display(std::ostream& ostr) const; 
		friend class Menu;
	};

	class Menu {
		MenuItem mT_str;
		MenuItem* arr[MAX_MENU_ITEMS]{};
		int counter = 0;
	public:
		Menu();
		Menu(const char* Tstr); 

		Menu(const Menu& nope) = delete;
		Menu& operator=(const Menu& nope) = delete;

		~Menu();
		std::ostream& displayTitle(std::ostream& ostr = std::cout)const;
		std::ostream& displayMenuItems(std::ostream& ostr = std::cout)const;
		unsigned int run()const;
		Menu& operator<<(const char* menuitemConent);
		operator int()const;
		operator unsigned int()const;
		operator bool()const;
	    const char* operator[](int index)const;
	};
    int operator~(const Menu& left);
	std::ostream& operator<<(std::ostream& ostr, const Menu& left);
}
#endif