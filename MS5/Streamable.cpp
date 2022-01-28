/*
Final Project Milestone 4
Module: Streamable
Filename: Streamable.cpp
Author	Muhammad F. Khan
StudentID: 113-524-201
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#include <iostream>
#include "Streamable.h"

namespace sdds
{
    std::ostream& operator<<(std::ostream& ostr, const Streamable& left)
    {
        if (left) {
            left.write(ostr);
        }
        return ostr;
    }

    std::istream& operator>>(std::istream& istr, Streamable& right)
    {
        
        right.read(istr);
        return istr;
    }

    Streamable::~Streamable() {}
}