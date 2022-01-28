/*
Final Project Milestone 4
Module: Publication
Filename: Publication.h
Author	Muhammad F. Khan
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_BOOK_H__
#define SDDS_BOOK_H__
#include <iostream>

#include "Publication.h"

namespace sdds {
	class Book : public Publication {
		char* m_authorName{};
	public:
		Book();
		Book(const Book& RightOperand);
		Book& operator=(const Book& RightOperand);

		virtual char type()const;
		std::ostream& write(std::ostream& ostr) const;
		std::istream& read(std::istream& istr);
		virtual void set(int memberid);
		virtual operator bool() const;
		virtual ~Book();
	};
}

#endif