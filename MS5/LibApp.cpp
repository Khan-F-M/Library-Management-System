/*
Final Project Milestone 5
Module: LibApp
Filename: LibApp.cpp
Version 1.0
Author: Muhammad F. Khan
Revision History
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Menu.h"
#include "LibApp.h"
#include "Publication.h"
#include "Book.h"
#include "PublicationSelector.h"

using namespace std;

namespace sdds {

    LibApp::LibApp(const char* file) : m_changed(false),
        m_mainMenu("Seneca Library Application"),
        m_exitMenu("Changes have been made to the data, what would you like to do?"),
        typePub("Choose the type of publication:")
    {
        strcpy(filename, file);
        m_mainMenu << "Add New Publication"
            << "Remove Publication"
            << "Checkout publication from library"
            << "Return publication to library";

        typePub << "Book" 
            << "Publication";

        m_exitMenu << "Save changes and exit"
            << "Cancel and go back to the main menu";

        load();
    }

    void LibApp::run() {
        int choice, pick, decide;
        bool temtemp= true;

        while (temtemp== true)
        {
            choice = m_mainMenu.run();

            if (choice == 1) {
                newPublication();
                cout << endl;
            }
            else if (choice == 2) {
                removePublication();
                cout << endl;
            }
            else if (choice == 3) {
                checkOutPub();
                cout << endl;
            }
            else if (choice == 4) {
                returnPub();
                cout << endl;
            }
            else {
                if (m_changed == false) {
                    temtemp= false;
                }
                else if (m_changed == true) {
                    pick = m_exitMenu.run();
                    if (pick == 1) {
                        save();
                        temtemp= false;
                    }
                    else if (pick == 2) {
                        temtemp= true;
                        cout << endl;
                    }
                    else {
                        decide = confirm("This will discard all the changes are you sure?");
                        if (decide == 1) {
                            temtemp= false;
                        }
                        else {
                            temtemp= true;
                        }
                    }
                }
            }
        }
        cout << "\n-------------------------------------------" << endl;
        cout << "Thanks for using Seneca Library Application" << endl;
     

    }

    bool LibApp::confirm(const char* message)
    {
        Menu temp(message);
        temp << "Yes";

        int pck = temp.run();

        if (pck == 1) {
            return true;
        }
        else {
            return false;
        }
    }

    void LibApp::load() {

        cout << "Loading Data" << endl;
        ifstream infile(filename);
        char type{};

        for (int i = 0; infile; i++) {
            infile >> type;
            infile.ignore();

            if (infile) {

                if (type == 'P') {
                    records[i] = new Publication;
                }
                else if (type == 'B') {
                    records[i] = new Book;
                }
              
                if (records[i]) {
                    infile >> *records[i];
                    m_lastLib = records[i]->getRef();
                    m_noOfPub++;
                }
            }
        }
    }

    void LibApp::save() {
        cout << "Saving Data" << endl;
        ofstream outfile(filename);

        for (int i = 0; i < m_noOfPub; i++) {

            if (records[i]->getRef() != 0) {
                outfile << *records[i] << endl;
            }
        }
    }

    int LibApp::search(int membership) {

        PublicationSelector temp("Select one of the following found matches:");
        char title[256];
        char type{};
        int typ;

        typ = typePub.run();

        if (typ == 1) {
            type = 'B';
        }
        else {
            type = 'P';
        }

        cout << "Publication Title: ";
        cin.getline(title, 256);

        if (membership == 5)
        {
            for (int i = 0; i < m_noOfPub; i++) {
                if (records[i]->getRef() != 0
                    && type == records[i]->type()
                    && strstr(*records[i], title)
                    && records[i]->onLoan()) {

                    temp << records[i];
                }
            }
        }
        else if (membership == 0)
        {
            for (int i = 0; i < m_noOfPub; i++) {
                if (records[i]->getRef() != 0
                    && type == records[i]->type()
                    && strstr(*records[i], title)
                    && !records[i]->onLoan()) {

                    temp << records[i];
                }
            }
        }
        else if (membership == 1) {
            for (int i = 0; i < m_noOfPub; i++) {
                if (records[i]->getRef() != 0
                    && type == records[i]->type()
                    && strstr(*records[i], title)) {

                    temp << records[i];
                }
            }
        }

        int ref = 0;
        if (temp) {
            temp.sort();
            ref = temp.run();
            if (ref) {
                prnPub(records, m_noOfPub, ref);
            }
            else {
                cout << "Aborted!" << endl;
            }
        }
        else {
            cout << "No matches found!" << endl;
        }

        return ref;
    }

    void LibApp::returnPub() {
        cout << "Return publication to the library" << endl;
        int libRef = search(5);
        int days;
        double cost;
        int overdue;
        Date current;

        if (libRef != 0 && confirm("Return Publication?")) {

            days = current - getPub(libRef)->checkoutDate();
            overdue = days - 15;

            if (overdue > 0) {      
                cost = overdue * 0.5;
                cout << "Please pay $";
                cout << fixed << setprecision(2) << cost;
                cout << " penalty for being " << overdue << " days late!" << endl;
            }
            getPub(libRef)->set(0);
            m_changed = true;
            cout << "Publication returned" << endl;
        }
    }

    void LibApp::newPublication() {

        if (m_noOfPub == SDDS_LIBRARY_CAPACITY)
        {
            cout << "Library is at its maximum capacity!" << endl;
        }
        else {
            cout << "Adding new publication to the library" << endl;

            int typ = typePub.run();
            Publication* temp{};

            if (typ == 1)
            {
                temp = new Book;
                cin >> *temp;

            }
            else if (typ == 2)
            {
                temp = new Publication;
                cin >> *temp;
            }
            else {
                cout << "Aborted!" << endl;
                return;
            }

            if (cin.fail())
            {
                cout << "Aborted!" << endl;
                return;
            }
            else {
                if (confirm("Add this publication to the library?")) {
                    if (temp) {
                        
                        m_lastLib++;
                        temp->setRef(m_lastLib);

                        records[m_noOfPub] = temp;
                        m_noOfPub++;

                        m_changed = true;
                        cout << "Publication added" << endl;
                    }
                }
                else {
                    cout << "Aborted!" << endl;
                    return;
                }
            }

            if (!temp)
            {
                cout << "Failed to add publication!" << endl;
                delete temp;
            }

        }
    }

    void LibApp::removePublication()
    {

        cout << "Removing publication from the library" << endl;

        int libRef = search();

        if (libRef != 0 && confirm("Remove this publication from the library?"))
        {
            m_changed = true;
            getPub(libRef)->setRef(0);
            cout << "Publication removed" << endl;
        }

    }

    void LibApp::checkOutPub() {
        cout << "Checkout publication from the library" << endl;
        int libRef = search(0);

        int digit;
        if (libRef != 0) {
            if (confirm("Check out publication?")) {

                cout << "Enter Membership number: ";
                cin >> digit;

                if (digit < 10000 || digit > 99999) {
                    cout << "Invalid membership number, try again: ";
                    cin >> digit;
                }

                getPub(libRef)->set(digit);
                m_changed = true;
                cout << "Publication checked out" << endl;
            }
        }
    }
    

    Publication* LibApp::getPub(int libRef) {
        for (int i = 0; i < m_noOfPub; i++)
        {
            if (libRef == records[i]->getRef()) {
                return records[i];
            }
        }
        return nullptr;
    }

    void LibApp::prnPub(Publication* p[], int size, int ref) {
        int i;
        for (i = 0; i < size; i++) {
            if (ref == p[i]->getRef()) {
                cout << *p[i] << endl;
                i = size; 
            }
        }
    }

    LibApp::~LibApp()
    {
        for (int i = 0; i < m_noOfPub; i++) {
            delete records[i];
        }
    }
}
