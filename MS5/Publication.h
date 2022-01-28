/*
Final Project Milestone 3
Module: Publication
Filename: Publication.h
Author	Muhammad F. Khan
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_PUBLICATION_H__
#define SDDS_PUBLICATION_H__
#include <iostream>

#include "Streamable.h"
#include "Date.h"

namespace sdds {
	class Publication : public Streamable {
		char* m_title{};
		char* m_shelfId{};
		int m_membership{ 0 };
		int m_libRef = -1 ;
		Date m_date; 
	public:

		Publication();

		Publication(const Publication& right);
		Publication& operator=(const Publication& right);

		virtual void set(int member_id);
		void setRef(int value);
		void resetDate();
		virtual char type()const;
		bool onLoan()const;
		Date checkoutDate()const;
		bool operator==(const char* title)const;
		operator const char* ()const;
		int getRef()const;
		bool conIO(std::ios& io)const;

		std::ostream& write(std::ostream& ostr) const;
		std::istream& read(std::istream& istr);
		operator bool() const;

		virtual ~Publication();
	};


	
}
#endif