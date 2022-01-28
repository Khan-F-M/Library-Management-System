/*
Final Project Milestone 4
Module: Date
Filename: Date.cpp
Author	Muhammad F. Khan
StudentID: 113-524-201
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <ctime>
#include "Date.h"
using namespace std;

namespace sdds {
    //Add the following global variable
    bool sdds_test = false;
    int sdds_year = 2021;
    int sdds_mon = 12;
    int sdds_day = 25;

   bool Date::validate() {
      errCode(NO_ERROR);
      if (m_year < MIN_YEAR || m_year > m_CUR_YEAR + 1) {
         errCode(YEAR_ERROR);
      }
      else if (m_mon < 1 || m_mon > 12) {
         errCode(MON_ERROR);
      }
      else if (m_day < 1 || m_day > mdays()) {
         errCode(DAY_ERROR);
      }
      return !bad();
   }
   int Date::mdays()const {
      int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
      int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
      mon--;
      return days[mon] + int((mon == 1) * ((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
   }
   int Date::systemYear()const {
       int theYear = sdds_year;
       if (!sdds_test) {
           time_t t = time(NULL);
           tm lt = *localtime(&t);
           theYear = lt.tm_year + 1900;
       }
       return theYear;
   }
   void Date::setToToday() {
       if (sdds_test) {
           m_day = sdds_day;
           m_mon = sdds_mon;
           m_year = sdds_year;
       }
       else {
           time_t t = time(NULL);
           tm lt = *localtime(&t);
           m_day = lt.tm_mday;
           m_mon = lt.tm_mon + 1;
           m_year = lt.tm_year + 1900;
       }
       errCode(NO_ERROR);
   }
   int Date::daysSince0001_1_1()const { // Rata Die day since 0001/01/01 
      int ty = m_year;
      int tm = m_mon;
      if (tm < 3) {
         ty--;
         tm += 12;
      }
      return 365 * ty + ty / 4 - ty / 100 + ty / 400 + (153 * tm - 457) / 5 + m_day - 306;
   }
   Date::Date() :m_CUR_YEAR(systemYear()) {
      setToToday();
   }
   Date::Date(int year, int mon, int day) : m_CUR_YEAR(systemYear()) {
      m_year = year;
      m_mon = mon;
      m_day = day;
      validate();
   }
   const char* Date::dateStatus()const {
      return DATE_ERROR[errCode()];
   }
   int Date::currentYear()const {
      return m_CUR_YEAR;
   }
   void Date::errCode(int readErrorCode) {
      m_ErrorCode = readErrorCode;
   }
   int Date::errCode()const {
      return m_ErrorCode;
   }
   bool Date::bad()const {
      return m_ErrorCode != 0;
   }
  
   ostream& operator<<(ostream& os, const Date& RO) {
      return RO.write(os);
   }
   istream& operator>>(istream& is, Date& RO) {
      return RO.read(is);
   }

   std::istream& Date::read(std::istream& is) {
       errCode(NO_ERROR);
       is >> m_year;
       is.ignore(); 

       is >> m_mon;
       is.ignore();

       is >> m_day;

       if (is.fail()) { 
           errCode(CIN_FAILED);
           is.ignore(2000, '\n');
           is.clear();
       }
       else {
           validate();
       }
       return is;
   }

   ostream& Date::write(std::ostream& os)const {
       if (m_ErrorCode != 0) {
          os << dateStatus();
       }
       else
       {
           os << m_year << "/";

           if (m_mon < 10) {
            os.fill('0');
            os.width(2);
            os << m_mon;
           }
           else {
               os << m_mon;
           }

           os << "/";

           if (m_day < 10) {
               os.fill('0');
               os.width(2);
               os << m_day;
          
           }
           else {
               os << m_day;
           }
       }
       return os;
   }


   bool Date::operator==(const Date& c1)const {
       return ((this->m_year == c1.m_year) && (this->m_mon == c1.m_mon ) && (this->m_day == c1.m_day));
   }

   bool Date::operator!=(const Date& c2)const {
       return !(*this == c2);
   }

   bool Date::operator>=(const Date& c3)const {
       return *this > c3 || *this == c3;
   }

   bool Date::operator<=(const Date& c4)const {
       return *this < c4 || *this == c4;
   }
   
   bool Date::operator<(const Date& c5)const {
       return((this->m_year < c5.m_year) || (this->m_mon < c5.m_mon) || (m_day < c5.m_day));
   }

   bool Date::operator>(const Date& c6)const {
       return((this->m_year > c6.m_year) || (this->m_mon > c6.m_mon) || (m_day > c6.m_day));
   }

   int Date::operator-(const Date d1)const { 
       int Fir = ((m_year * 365) + (m_mon * 30) + m_day);
       int Sec = ((d1.m_year * 365) + (d1.m_mon * 30) + d1.m_day);

       return Fir - Sec;
   }

   Date::operator bool()const {
       return m_ErrorCode == NO_ERROR;
   }
}
