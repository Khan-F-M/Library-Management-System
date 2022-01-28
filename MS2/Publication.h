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
		int m_libRef{ -1 };
		Date m_date; 
	public:

		Publication();

		Publication(const Publication& right);
		Publication& operator=(const Publication& right);

		virtual void set(int member_id);
		// Sets the membership attribute to either zero or a five-digit integer.
		void setRef(int value);
		// Sets the **libRef** attribute value
		void resetDate();
		// Sets the date to the current date of the system.

		//-----------------QUERIES-------------------------------
		virtual char type()const;
		//Returns the character 'P' to identify this object as a "Publication object"
		bool onLoan()const;
		//Returns true is the publication is checkout (membership is non-zero)
		Date checkoutDate()const;
		//Returns the date attribute
		bool operator==(const char* title)const;
		//Returns true if the argument title appears anywhere in the title of the 
		//publication. Otherwise, it returns false; (use strstr() function in <cstring>)
		operator const char* ()const;
		//Returns the title attribute
		int getRef()const;
		//Returns the libRef attirbute. 
		//-----------------QUERIES-------------------------------

		bool conIO(std::ios& io)const;
		virtual std::ostream& write(std::ostream& ostr) const;
		virtual std::istream& read(std::istream& istr);
		virtual operator bool() const;

		~Publication();
	};

	
}
#endif