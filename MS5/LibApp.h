/*
Final Project Milestone 5
Module: LibApp
Filename: LibApp.h
Version 1.0
Author: Muhammad F. Khan
Revision History
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H
#include <cstring>
#include "Menu.h"
#include "Publication.h"
#include "Lib.h"
namespace sdds {
    class LibApp {
        bool m_changed;
        Menu m_mainMenu;
        Menu m_exitMenu;

        char filename[256];
        Publication* records[SDDS_LIBRARY_CAPACITY]{}; 
        int m_noOfPub = 0; 
        int m_lastLib = 0; 

        Menu typePub;

        bool confirm(const char* message);
        void load();
        void save();  

        int search(int membership = 1);
        void returnPub();
        void newPublication();
        void removePublication();
        void checkOutPub();
        Publication* getPub(int libRef);

        void prnPub(Publication* p[], int size, int ref);
    public:
        LibApp(char* filename);
        ~LibApp();
        LibApp(const char* filename);
        void run();
    };
}
#endif // !SDDS_LIBAPP_H



