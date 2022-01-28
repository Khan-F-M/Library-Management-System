/*
Final Project Milestone 3
Module: Streamable
Filename: Streamable.cpp
Author	Muhammad F. Khan
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
/*
Issues: conIO, 
        setting m_shelfId to an empty string, 
        ostream file opening up with "Exception thrown at 0x00D03BE1 in ms3.exe: 0xC0000005: Access violation reading location 0xCCCCCCD0."
*/

#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include "Publication.h"
#include "Lib.h"
#include "Streamable.h"
#include "Utils.h"

using namespace std;

namespace sdds {

	Publication::Publication() {}

	Publication::Publication(const Publication& right) {
		operator=(right);
	}

	Publication& Publication::operator=(const Publication& right) {
		if (this != &right && right) {
			allocateAndCopy(m_title, right.m_title);
			strcpy(m_shelfId, right.m_shelfId);
			set(right.m_membership);
			setRef(right.m_libRef);
			m_date = right.m_date;
		}
		return *this;
	}

	Publication::operator bool() const {
		return (m_title && m_title[0] && m_shelfId && m_shelfId[0]);
	}

	void Publication::set(int member_id) {
		m_membership = member_id;
	}

	void Publication::setRef(int value) {
		m_libRef = value;
	}

	void Publication::resetDate() {
		m_date.setToToday(); 
	}

	char Publication::type()const {
		return 'P';
	}

	bool Publication::onLoan()const {
		return m_membership != 0;
	}

	Date Publication::checkoutDate()const {
		return m_date;
	}

	bool Publication::operator==(const char* title)const {
		return ((strstr(m_title, title)) != nullptr);
	}

	Publication::operator const char* ()const {
		return m_title;
	}

	int Publication::getRef()const {
		return m_libRef;
	}

	bool Publication::conIO(ios& io)const {
		return (&io == &cin || &io == &cout);
	}

    ostream& Publication::write(ostream& ostr) const {
		if (conIO(ostr)) { //add the condition
			ostr << "| ";
			ostr << m_shelfId;
			ostr << " | ";
			ostr << m_title;
			ostr.width(14);
			ostr.fill('.');
			ostr << ".";
			ostr << " | ";
			ostr << m_membership;
			ostr << " | ";
			m_date.write(ostr);
			ostr << " |";
		}
		else {
			ostr << type() << "    " << m_libRef << "    " << m_shelfId;
			ostr << "    " << m_title << "    " << m_membership << "    ";
			m_date.write(ostr);
		}
		return ostr;
	}

    std::istream& Publication::read(std::istream& istr) {
		
		delete[] m_title;
		delete[] m_shelfId;
		m_membership = 0;
		m_libRef = -1;
		m_date.setToToday();

		//Local Vars
	    //char title[255];
		//char shelf[4];
		string title{};
		string shelf{};
		int membership = 0, libref = -1;
		Date date;

		if (conIO(istr)) {
			cout << "Shelf No: ";
			getline(istr, shelf);
			
			if (strlen(shelf.c_str()) != 4) {
				istr.setstate(ios::failbit);
			}

			cout << "Title: ";
			getline(istr, title);

			cout << "Date: ";
		}
		else {
			istr >> libref;
			istr.ignore('\t');

			getline(istr, shelf);
			istr.ignore('\t');

			getline(istr, title);
			istr.ignore('\t');

			istr >> membership;
			istr.ignore('\t');
		}

		date.read(istr);
		if (!date) istr.setstate(ios::failbit);

		if (istr) {
		    m_title = new char[strlen(title.c_str()) + 1];
			strcpy(m_title, title.c_str());

		   /* m_title = new char[strlen(title) + 1];
			strcpy(m_title, title);*/

			strcpy(m_shelfId, shelf.c_str());
			set(membership);
			setRef(libref);
			m_date = date;
		}

		return istr;
	}

	Publication::~Publication() {
		delete[] m_title; 
		delete[] m_shelfId;
	}
}