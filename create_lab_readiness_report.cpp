/*
 * Course: COEN 2210 - Introduction to Programming
 * Name: Johnatanel Perez Lopez
 * Lab: 9 - File I/O
 * Description: Calculates the available workstations in a computer lab,
 *              decides whether a workshop can open, and saves the results
 *              to lab_readiness_report.txt.
 * Due Date: October 23, 2026
 */

#include <fstream>                                       // Provides ofstream for file output in Step 3
#include <iostream>                                      // Provides cin, cout, and endl
#include <string>                                        // Provides the string data type
using namespace std;                                     // Allows standard-library names without the std:: prefix

int calculateAvailableWorkstations(int totalWorkstations, int unavailableWorkstations); // Declares a function that returns the available count
bool canOpenWorkshop(int availableWorkstations, int minimumRequired); // Declares a function that returns the opening decision

int main() {                                             // Starts the program
    string labName;                                      // Stores the laboratory name
    int totalWorkstations;                               // Stores the total number of workstations
    int unavailableWorkstations;                         // Stores the number of unavailable workstations
    int minimumRequired;                                 // Stores the minimum number required for the workshop

    cout << "Enter laboratory name: ";                  // Prompts for the laboratory name
    getline(cin, labName);                               // Reads the complete laboratory name
    cout << "Enter total workstations: ";              // Prompts for the total number of workstations
    cin >> totalWorkstations;                            // Reads the total number into main
    cout << "Enter unavailable workstations: ";        // Prompts for the unavailable count
    cin >> unavailableWorkstations;                      // Reads the unavailable count into main
    cout << "Enter minimum workstations required: ";   // Prompts for the workshop requirement
    cin >> minimumRequired;                              // Reads the minimum requirement into main

    int availableWorkstations;                           // Stores the number returned by the availability function
    bool workshopCanOpen;                                // Stores the decision returned by the Boolean function

    availableWorkstations = calculateAvailableWorkstations(totalWorkstations, unavailableWorkstations); // Stores the calculated available count
    workshopCanOpen = canOpenWorkshop(availableWorkstations, minimumRequired); // Stores whether the workshop can open

    cout << "Available workstations: " << availableWorkstations << endl; // Displays the returned available count
    cout << boolalpha << "Workshop can open: " << workshopCanOpen << endl; // Displays the returned Boolean value

    ofstream outputFile("lab_readiness_report.txt");    // Opens the report file for output
    if (!outputFile) {                                  // Tests whether the output file opened successfully
        cout << "Error: Could not create the report file." << endl; // Reports an opening failure in English
        return 1;                                       // Ends the program with an error status
    }                                                    // Ends the output-file validation

    outputFile << "Lab Readiness Report" << endl;      // Writes a fixed report heading
    outputFile << "Laboratory: " << labName << endl;   // Writes the entered laboratory name
    outputFile << "Total workstations: " << totalWorkstations << endl; // Writes the total count
    outputFile << "Unavailable workstations: " << unavailableWorkstations << endl; // Writes the unavailable count
    outputFile << "Minimum required: " << minimumRequired << endl; // Writes the minimum requirement
    outputFile << "Available workstations: " << availableWorkstations << endl; // Writes the returned available count

    if (workshopCanOpen) {                              // Tests the Boolean value returned by the decision function
        outputFile << "Workshop can open." << endl;     // Writes the positive workshop status
    } else {                                             // Handles the case where the minimum is not met
        outputFile << "Workshop cannot open." << endl;  // Writes the negative workshop status
    }                                                    // Ends the workshop-status selection

    outputFile.close();                                 // Flushes and closes the report file

    return 0;                                            // Ends the program successfully
}                                                        // Ends the main function

int calculateAvailableWorkstations(int totalWorkstations, int unavailableWorkstations) { // Defines the availability calculation
    return totalWorkstations - unavailableWorkstations;  // Returns the number of usable workstations
}                                                        // Ends the availability function

bool canOpenWorkshop(int availableWorkstations, int minimumRequired) { // Defines the opening decision
    return availableWorkstations >= minimumRequired;     // Returns true when the minimum is met
}                                                        // Ends the Boolean function

/*
 * Analysis:
 * 1. For the test case (12 total, 3 unavailable), calculateAvailableWorkstations
 *    returns 12 - 3 = 9. main stores that value in availableWorkstations and
 *    reuses it for the decision, the terminal output, and the report file.
 * 2. canOpenWorkshop returns true when availableWorkstations >= minimumRequired.
 *    With 9 available and 8 required, the condition is true, so the report says
 *    "Workshop can open." With 5 unavailable, only 7 remain and it returns false.
 * 3. An ofstream keeps written data in a buffer before sending it to the disk.
 *    Calling close() flushes that buffer so every line is actually saved, and it
 *    releases the file so another program (like the reader in Part 3) can open
 *    it safely.
 */
