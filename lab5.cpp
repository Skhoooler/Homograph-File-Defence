/******************************************************************************
 * Lab 5 - Homographs
 * 
 * By David Doria
 * 2/2/22
 * 
 * The program will receive two filenames as inputs, and will determine if they
 * are homographs of each other
 * ****************************************************************************/

#include <iostream>
#include <string>
#include <list>
#include <sstream>

#include "testbed.h"

using namespace std;

bool determineHomograph(string path1, string path2);
list<string> canonicalize(string path);
void removeRedundancies(list<string>* path);

int main() {
    // string path1;
    // string path2;

    // // Get the first filename from the user
    // cout << "Specify the first filename: ";
    // cin >> path1;

    // // Get the second filename from the user
    // cout << "Specify the second filename: ";
    // cin >> path2;

    // bool homograph = determineHomograph(path1, path2);

    // Send the determineHomograph to the testbed class for it to run tests on
    Testbed testbed(&determineHomograph);
    testbed.runTests();

    // This is only here to stop the window from closing immediately
    cin.get();

    return 0;
}

/******************************************************************************
 * determineHolograph
 * Determines whether two strings are homographs or not. Returns true if they
 * are, false if they are not.
 * ***************************************************************************/
bool determineHomograph(string rawPath1, string rawPath2) {
    // Return Value
    boolean result = true;

    // Retrieve lists from canonicalize()
    list<string> path1 = canonicalize(rawPath1);
    list<string> path2 = canonicalize(rawPath2);

    list<string>::iterator it1 = path1.begin();
    list<string>::iterator it2 = path2.begin();

    // While both path1 AND path2 are not empty
    cout << "###########################" << endl;
    do {
        cout << *it1 << " - " << *it2 << endl;
        // Compare Elements of Path 1 and Path 2
        if (*it1 == *it2) {
            // They are the same          
            it1++;
            it2++;
        }
        else {
            // They are not the same
            // It is not a homograph
            result = false;
            break;
        }
    } while (it1 != path1.end() && it2 != path2.end());

    return result;
}

/*****************************************************************************
 * canonicalize
 * Canonizes a path so that they can be compared by determineHolograph. Returns
 * the same path as a canonized string
 * 
 * The Canonization function splits each element of the path and puts it a stack,
 * so the lowest file is on top.
 * ***************************************************************************/
list<string> canonicalize(string path) {
    list<string> tokens;

    // Puts together elements within the path in the loop
    stringstream ss;

    // One iterator (it) iterates through the string, the second (itMarkElement)
    // Marks the location of the beginning of the next element to add to the stack
    string::iterator it;
    string::iterator itMarkElement = path.begin();

    // An end-of-list entry, used in logic in determineHomograph
    // tokens.push_front("~END~");

    // Iterate through the path and push elements onto the end of the stack
    for (it = path.begin(); it != path.end(); it++) {
        // If the character is == "/"
        if (*it == '/') {
            // Iterate from the last "/" (itMarkElement) to the current one (it)
            // and add it to the stringstream
            for (itMarkElement; itMarkElement != it; itMarkElement++){
                // Make sure the '/' isn't included
                if (*itMarkElement != '/')
                    ss << *itMarkElement;
            }
            // Add that element to the back of the stack
            tokens.push_front(ss.str());

            // Clear the stringstream
            // https://stackoverflow.com/questions/20731/how-do-you-clear-a-stringstream-variable
            ss.str(string());
            ss.clear();
        }
    }

    // The loop above will miss the final element, so I will add it here
    for (itMarkElement; itMarkElement != path.end(); itMarkElement++) {
        // Make sure the '/' isn't included
        if (*itMarkElement != '/')
            ss << *itMarkElement;
    }
    tokens.push_front(ss.str());

    ss.str(string());
    ss.clear();

    removeRedundancies(&tokens);

    return tokens;
}

/******************************************************************************
 * removeRedundancies
 * Iterates through a list which contains the elements of a path. Removes
 * redundancies within that list to produce the most condensed path
 * 
 * Ex:
 * /Confidential/Secret/../Secret/./test.txt becomes
 * /Confidential/Secret/test.txt
 * ***************************************************************************/
void removeRedundancies(list<string>* path) {
    list<string>::iterator it = path->begin();

    for (it; it != path->end(); it++) {
        // Check for /. and /..
        if (*it == "." || *it == "..") {
            // cout << "Removing " << *it << endl;
            // Remove the /. or /..
            path->erase(it);
        }
        // Check to see if the current element is the same as the previous one
        else if (*it == *prev(it)) {
            // cout << "Removing " << *it << endl;
            path->erase(it);
        }
    }

    // Prints the list, for debugging
    // it = path->begin();
    // for(it; it != path->end(); it++) {
    //     cout << *it << endl;
    // }
}
/*********************
 * Example Homograph
 * C:\\Users\David\Confidential\.\Secret\..\Secret\test.txt
 * 
 * Order thats stored in the list: 
 * \test.txt
 * \Secret
 * \..
 * \Secret
 * \.
 * \Confidential
 * \David
 * \Users
 * 
 * 
/********************
 * Algorithm
 * 
 * Assumes the path is a homograph by default (returns true if the comparisons (step 3) are all the same)
 * 
 * 1. Remove Redundancies
 *      - Check for ./.. (They function the same)
 *          - If found
 *              - pathx.erase(itx)
 *              - It++
 *      - Check if the next directory is the same as the previous
 *          - If found
 *              - path.erase(it)
 *              - it++
 * 2. Compare Elements
 *      - If Same, then to next element
 *          - If the loop ends (One of the lists runs out), it will return default (true)
 *      - else (If different), return false 
 * ******************/