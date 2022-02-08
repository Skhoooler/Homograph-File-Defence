/******************************************************************************
* Testbed for Lab 5
* 
* By David Doria
* 2/2/22
* 
* Performs a set of tests on lab 5
******************************************************************************/
#include <iostream>
#include <string>
#include <windows.h>

#include "testbed.h"

Testbed::Testbed(bool (*f)(string, string)) {
    testFunction = f;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

/******************************************************************************
 * runTests
 * Runs the suite of tests available
******************************************************************************/
void Testbed::runTests() {
    testNonHomographs();
    testHomographs();
}


// Tests for Non-Homographs


/******************************************************************************
 * testNonHomographs
 * Tests for Non-Homographs. Since the function in question should return false
 * for these, if it returns true, it fails.
******************************************************************************/
void Testbed::testNonHomographs() {
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
    cout << "Testing for Non-Homographs: " << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    
    // Test 1
    string test1_1 = "/test.txt";
    string test1_2 = "/test.cpp";
    displayTest(test1_1, test1_2);
    performNonHomographTest(test1_1, test1_2);

    // Test 2
    string test2_1 = "/confidential/secret/please_dont/test.txt";
    string test2_2 = "/not_confidential/not_secret/please_do/test.txt";
    displayTest(test2_1, test2_2);
    performNonHomographTest(test2_1, test2_2);

    // Test 3
    string test3_1 = "../secret.txt";
    string test3_2 = "./secret.txt";
    displayTest(test3_1, test3_2);
    performNonHomographTest(test3_1, test3_2);

    // Test 4
    string test4_1 = "/confidential/secret/test.txt";
    string test4_2 = "/confidential/not_secret/test.txt";
    displayTest(test4_1, test4_2);
    performNonHomographTest(test4_1, test4_2);
}

/******************************************************************************
 * performNonHomographTest
 * Performs the test for cases where it is not a homograph. If it fails, it calls
 * failed(). If it succeeded, it calls success()
******************************************************************************/
void Testbed::performNonHomographTest(string param1, string param2) {
    if (testFunction(param1, param2)) {
        failed();
    } else {
        success();
    }
}


// Tests for Homographs


/******************************************************************************
 * testHomographs
 * Tests for Homographs. Since the function in question should return true
 * for these, if it returns false, it fails.
******************************************************************************/
void Testbed::testHomographs() {
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
    cout << "Testing for Homographs: " << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    
    // Test 1
    string test1_1 = "/secret.txt";
    string test1_2 = "/secret.txt";
    displayTest(test1_1, test1_2);
    performHomographTest(test1_1, test1_2);

    // Test 2
    string test2_1 = "/confidential/secret/plese_dont/test.txt";
    string test2_2 = "/confidential/secret/plese_dont/test.txt";
    displayTest(test2_1, test2_2);
    performHomographTest(test2_1, test2_2);

    // Test 3
    string test3_1 = "/../secret/test.txt";
    string test3_2 = "/secret/test.txt";
    displayTest(test3_1, test3_2);
    performHomographTest(test3_1, test3_2);

    // Test 4
    string test4_1 = "/test.txt";
    string test4_2 = "/confidential/secret/test.txt";
    displayTest(test4_1, test4_2);
    performHomographTest(test4_1, test4_2);

    // Test 5
    string test5_1 = "test.txt";
    string test5_2 = "/test.txt";
    displayTest(test5_1, test5_2);
    performHomographTest(test5_1, test5_2);

    // Test 6
    string test6_1 = "/not-secret/../secret/test.txt";
    string test6_2 = "/secret/test.txt";
    displayTest(test6_1, test6_2);
    performHomographTest(test6_1, test6_2);

    // Test 7
    string test7_1 = "/not-secret/../secret/../secret/test.txt";
    string test7_2 = "/not-secret/./../not-secret/secret/test.txt";
    displayTest(test7_1, test7_2);
    performHomographTest(test7_1, test7_2);

    // Test 8
    string test8_1 = "./../test.txt";
    string test8_2 = "/secret/test.txt";
    displayTest(test8_1, test8_2);
    performHomographTest(test8_1, test8_2);
}

/******************************************************************************
 * performHomographTest
 * Performs the test for cases where it is not a homograph. If it fails, it calls
 * failed(). If it succeeded, it calls success()
******************************************************************************/
void Testbed::performHomographTest(string param1, string param2) {
    if (testFunction(param1, param2)) {
        success();
    } else {
        failed();
    }
}


// Helper Functions


/******************************************************************************
 * failed
 * Displays "Failed" in red if it is called
******************************************************************************/
void Testbed::failed() {
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    cout << "Failed" << endl << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

/******************************************************************************
 * success
 * Displays "Success" in green if it is called
******************************************************************************/
void Testbed::success() {
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    cout << "Success" << endl << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

}

/******************************************************************************
 * displayTest
 * Displays what the test is
******************************************************************************/
void Testbed::displayTest(string param1, string param2) {
        cout << param1 << endl << param2 << endl;
}