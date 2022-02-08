/******************************************************************************
* Header file for Testbed.cpp
******************************************************************************/
#ifndef TESTBED_H
#define TESTBED_H

#include <string>
#include <windows.h>

using namespace std;

class Testbed {
    public:
        Testbed(bool (*f)(string, string));
        void runTests();

    private:
        // The function to be passed in that determines if its a homograph
        bool (*testFunction)(string, string);

        // This is for changing the color of the test output
        // https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c
        HANDLE hConsole;
        
        // For cases where the test is not a homograph
        void testNonHomographs();
        void performNonHomographTest(string param1, string param2);

        // For cases where the test is a homograph
        void testHomographs();
        void performHomographTest(string param1, string param2);

        // Helper functions
        void displayTest(string param1, string param2);
        void failed();
        void success();
};

#endif 