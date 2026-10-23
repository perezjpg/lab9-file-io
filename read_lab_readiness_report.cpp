/*
 * Course: COEN 2210 - Introduction to Programming
 * Name: Johnatanel Perez Lopez
 * Lab: 9 - File I/O
 * Description: Opens the existing lab_readiness_report.txt, validates that it
 *              opened, and displays every line of the report in the terminal.
 * Due Date: October 23, 2026
 */

#include <fstream>                                       // Provides ifstream for file input
#include <iostream>                                      // Provides cout and endl
#include <string>                                        // Provides the string data type
using namespace std;                                     // Allows standard-library names without the std:: prefix

int main() {                                             // Starts the program
    ifstream inputFile("lab_readiness_report.txt");     // Prepares the existing report for input
    string line;                                         // Stores one complete line read from the file

    if (!inputFile) {                                    // Tests whether the report opened successfully
        cout << "Error: Could not open lab_readiness_report.txt." << endl; // Reports the opening failure in English
        return 1;                                        // Ends the program with an error status
    }                                                    // Ends the input-file validation

    cout << "===== Contents of lab_readiness_report.txt =====" << endl; // Displays the terminal heading once

    while (getline(inputFile, line)) {                   // Reads one line at a time until the end of the file
        cout << line << endl;                            // Displays the line that was just read
    }                                                    // Ends the reading loop

    inputFile.close();                                   // Closes the input stream after all lines are processed

    return 0;                                            // Ends the program successfully
}                                                        // Ends the main function

/*
 * Analysis:
 * 1. This program only needs to read the report, so it uses ifstream. Opening
 *    the same file with ofstream would truncate it and erase the report that
 *    the first program created.
 * 2. getline(inputFile, line) returns the stream itself, which evaluates to
 *    false once a read fails. When the end of the file is reached there are no
 *    more lines to read, the read fails, and the while loop stops.
 * 3. If the file does not exist or cannot be opened, every read would fail and
 *    the program would show nothing without explaining why. Testing the stream
 *    first lets the program report a clear error and exit with a non-zero
 *    status instead of trying to process data that is not there.
 */
