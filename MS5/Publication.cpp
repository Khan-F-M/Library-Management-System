/*
Final Project Milestone 4
Module: Publication
Filename: Publication.cpp
Author	Muhammad F. Khan
StudentID: 113-524-201
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
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

            delete[] m_title;
            delete[] m_shelfId;
            m_shelfId = nullptr;
            m_title = nullptr;

            m_title = new char[strlen(right.m_title) + 1];
            strcpy(m_title, right.m_title);

            m_shelfId = new char[strlen(right.m_shelfId) + 1];
            strcpy(m_shelfId, right.m_shelfId);

            set(right.m_membership);
            setRef(right.m_libRef);
            m_date = right.m_date;
        }
        return *this;
    }

    void Publication::set(int member_id)
    {
        m_membership = member_id;
    }


    void Publication::setRef(int value)
    {
        m_libRef = value;
    }

    void Publication::resetDate()
    {
        m_date.setToToday();
    }


    char Publication::type()const
    {
        return 'P';
    }

    bool Publication::onLoan()const
    {
        return m_membership != 0;
    }
    Date Publication::checkoutDate()const
    {
        return m_date;
    }

    bool Publication::operator==(const char* title)const //made simpler
    {
        return (strstr(m_title, title) != NULL);
    }

    Publication::operator const char* ()const
    {
        return m_title;
    }

    int Publication::getRef()const
    {
        return m_libRef;
    }


    bool Publication::conIO(std::ios& io)const
    {
        return &io == &cin || &io == &cout;
    }



    ostream& Publication::write(std::ostream& ostr) const
    {
        if (conIO(ostr))
        {
            ostr << "| " << m_shelfId << " | ";

            if (strlen(m_title) < 30) {
                ostr << m_title;
                ostr.width(SDDS_TITLE_WIDTH - strlen(m_title));
                ostr.fill('.');
                ostr << ".";
            }
            else if (strlen(m_title) == 30)
            {
                ostr << m_title;
            }
            else if (strlen(m_title) > 30){
                for (int i = 0; i < 30; i++) {
                    ostr << m_title[i];
                }
            }

            ostr << " | ";

            if (m_membership == 0)
            {
                ostr << " N/A ";
            }
            else {
                ostr << m_membership;
            }
            ostr << " | " << m_date << " |";
        }
        else
        {
            ostr << type() << "\t" << m_libRef << "\t" << m_shelfId << "\t" << m_title << "\t" << m_membership << "\t" << m_date;
        }

        return ostr;
    }


    std::istream& Publication::read(std::istream& istr)
    {
        delete[] m_title;
        delete[] m_shelfId;
        m_shelfId = nullptr;
        m_title = nullptr;

        m_membership = 0;
        m_libRef = -1;
        char shelf[SDDS_SHELF_ID_LEN + 1];
        char title[255 + 1];

        int membership = 0;
        int libref = -1;
        Date date;

        if (conIO(istr))
        {

            cout << "Shelf No: ";
            istr.getline(shelf, SDDS_SHELF_ID_LEN + 1);

            if (strlen(shelf) != SDDS_SHELF_ID_LEN) {
                istr.setstate(ios::failbit);
            }

            cout << "Title: ";
            istr.getline(title, 255 + 1);

            cout << "Date: ";
        }
        else
        {
            istr >> libref;
            istr.ignore(1000, '\t');

            istr.getline(shelf, SDDS_SHELF_ID_LEN + 1, '\t');

            istr.getline(title, 255 + 1, '\t');

            istr >> membership;
            istr.ignore(1000, '\t');

        }

        date.read(istr);
        if (!date) istr.setstate(ios::failbit);

        if (istr) {
            m_shelfId = new char[strlen(shelf) + 1];
            strcpy(m_shelfId, shelf);

            m_title = new char[strlen(title) + 1];
            strcpy(m_title, title);

            set(membership);
            setRef(libref);
            m_date = date;
        }
        return istr;
    }

    Publication::operator bool() const
    {
        return m_title != nullptr && m_title[0] != '\0' && m_shelfId != nullptr && m_shelfId[0] != '\0';
    }

    Publication::~Publication() {
        delete[] m_title;
        delete[] m_shelfId;
    }
}
