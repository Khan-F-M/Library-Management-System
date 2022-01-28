/*
Final Project Milestone 3
Module: Streamable
Filename: Streamable.h
Author	Muhammad F. Khan
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_STREAMABLE_H__
#define SDDS_STREAMABLE_H__
#include <iostream>

namespace sdds {
	class Streamable {
	public:
		virtual std::ostream& write(std::ostream& ostr) const = 0;
		virtual std::istream& read(std::istream& istr) = 0;
		virtual	bool conIO(std::ios& io)const = 0; 
		virtual operator bool()const = 0;
		virtual ~Streamable();
	};

	std::ostream& operator<<(std::ostream& ostr, const Streamable& left);
	std::istream& operator>>(std::istream& istr, Streamable& right);
}
#endif