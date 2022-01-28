/*
Final Project Milestone 4
Module: Book
Filename: Book.cpp
Author	Muhammad F. Khan
StudentID: 113-524-201
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Publication.h"
#include "Lib.h"
#include "Streamable.h"
#include "Utils.h"
#include "Book.h"

using namespace std;

namespace sdds {
	Book::Book() {}

	Book::Book(const Book& RightOperand) : Publication(RightOperand) {
		operator=(RightOperand);
	}

	Book& Book::operator=(const Book& RightOperand) {
		if (this != &RightOperand && RightOperand) {
			Publication::operator=(RightOperand);

			delete[] m_authorName;
			m_authorName = nullptr;

			m_authorName = new char[strlen(RightOperand.m_authorName) + 1];
			strcpy(m_authorName, RightOperand.m_authorName);
		}

		return *this;
	}

	char Book::type()const {
		return 'B';
	}
	
	ostream& Book::write(ostream& ostr) const {

		Publication::write(ostr);

		if (Publication::conIO(ostr)) {
			ostr << " ";

			if (strlen(m_authorName) < SDDS_AUTHOR_WIDTH) {
				ostr << m_authorName;
				ostr.width(SDDS_AUTHOR_WIDTH - strlen(m_authorName));
				ostr.fill(' ');
				ostr << " ";
			}
			else if (strlen(m_authorName) == SDDS_AUTHOR_WIDTH) {
				ostr << m_authorName;
			}
			else if (strlen(m_authorName) > SDDS_AUTHOR_WIDTH) {
				for (int i = 0; i < 15; i++) {
					ostr << m_authorName[i];
				}
			}
			ostr << " |";
		}
		else {
			ostr << "\t" << m_authorName << endl;
		}

		return ostr;
	}

	std::istream& Book::read(std::istream& istr) {
		
		Publication::read(istr);
		
		delete[] m_authorName;
		m_authorName = nullptr;

		char authorName[256 + 1];

		if (Publication::conIO(istr)) {
			istr.ignore(1000, '\n');
			cout << "Author: ";
			istr.getline(authorName, 256 + 1);
		}
		else {
			istr.ignore(1000, '\t');
			istr.get(authorName, 256 + 1);
		}

		if (!istr.fail()) { 
				m_authorName = new char[strlen(authorName) + 1];
				strcpy(m_authorName, authorName);
		}

		return istr;
	}

	void Book::set(int memberid) {
		Publication::set(memberid);
		Publication::resetDate();
	}

	Book::operator bool() const {
		return (m_authorName != nullptr && m_authorName[0] != '\0' && Publication::operator bool() == true);
	}

	Book::~Book() {
		delete[] m_authorName;
	}
}