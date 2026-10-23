/*
 * Course: COEN 2210 - Introduction to Programming
 * Name: Johnatanel Perez Lopez
 * Lab: 9 - File I/O
 * Description: Saves motor current readings to motor_current_readings.txt,
 *              reads them back to count and total them, and reports whether
 *              the average current meets the allowed maximum.
 * Due Date: October 23, 2026
 */

#include <fstream>                                       // Provides ifstream and ofstream for file access
#include <iomanip>                                       // Provides fixed and setprecision
#include <iostream>                                      // Provides cin, cout, and endl
using namespace std;                                     // Allows standard-library names without the std:: prefix

double calculateAverageCurrent(double totalCurrent, int samplesRead); // Declares a function that returns the average
bool isWithinLimit(double averageCurrent, double maximumCurrent); // Declares a function that returns the limit decision

int main() {                                             // Starts the program
    int requestedSamples;                                // Stores the number of readings requested by the user
    int samplesRead = 0;                                 // Counts readings successfully read from the file
    double maximumCurrent;                               // Stores the allowed average-current limit
    double currentReading;                               // Stores one current reading at a time
    double totalCurrent = 0.0;                           // Accumulates the readings obtained from the file
    double averageCurrent;                               // Stores the average returned by a function

    cout << "Enter the number of samples: ";            // Prompts for the number of readings
    cin >> requestedSamples;                             // Reads the requested sample count
    if (requestedSamples <= 0) {                         // Rejects zero or negative sample counts
        cout << "Error: The number of samples must be positive." << endl; // Explains why the program stops
        return 1;                                        // Ends before creating a file or calculating an average
    }                                                    // Ends the sample-count validation

    cout << "Enter the maximum allowed average current (A): "; // Prompts for the current limit
    cin >> maximumCurrent;                               // Reads the maximum allowed average

    ofstream outputFile("motor_current_readings.txt");  // Opens the readings file for output
    if (!outputFile) {                                   // Tests whether the output file opened successfully
        cout << "Error: Could not create motor_current_readings.txt." << endl; // Reports the opening failure
        return 1;                                        // Ends the program with an error status
    }                                                    // Ends the output-file validation

    outputFile << fixed << setprecision(2);              // Writes every reading with two decimal places
    for (int sample = 1; sample <= requestedSamples; sample++) { // Repeats once for each requested sample
        cout << "Enter current reading #" << sample << " (A): "; // Prompts for one reading
        cin >> currentReading;                           // Reads one reading from the user
        outputFile << currentReading << endl;            // Saves the reading on its own line
    }                                                    // Ends the writing loop

    outputFile.close();                                  // Closes the output stream before reading the same file

    ifstream inputFile("motor_current_readings.txt");   // Opens the same file for input
    if (!inputFile) {                                    // Tests whether the input file opened successfully
        cout << "Error: Could not open motor_current_readings.txt." << endl; // Reports the opening failure
        return 1;                                        // Ends the program with an error status
    }                                                    // Ends the input-file validation

    while (inputFile >> currentReading) {                // Repeats while a double is read successfully
        samplesRead++;                                   // Counts the reading that was just read
        totalCurrent += currentReading;                  // Adds the reading to the accumulator
    }                                                    // Ends the reading loop

    inputFile.close();                                   // Closes the input stream after processing the file

    cout << fixed << setprecision(2);                    // Displays all results with two decimal places
    cout << "Readings read from file: " << samplesRead << endl; // Reports the readings actually read

    if (samplesRead > 0) {                               // Calculates only when at least one reading exists
        averageCurrent = calculateAverageCurrent(totalCurrent, samplesRead); // Stores the returned average
        cout << "Average current: " << averageCurrent << " A" << endl; // Displays the average

        if (isWithinLimit(averageCurrent, maximumCurrent)) { // Uses the returned Boolean value
            cout << "Result: Average current is within the limit of " << maximumCurrent << " A." << endl; // Reports a pass
        } else {                                         // Handles an average above the limit
            cout << "Result: Average current exceeds the limit of " << maximumCurrent << " A." << endl; // Reports a failure
        }                                                // Ends the limit decision
    } else {                                             // Handles a file with no valid readings
        cout << "No readings were found, so no average can be calculated." << endl; // Explains the missing average
    }                                                    // Ends the sample check

    return 0;                                            // Ends the program successfully
}                                                        // Ends the main function

double calculateAverageCurrent(double totalCurrent, int samplesRead) { // Defines the average calculation
    return totalCurrent / samplesRead;                   // Returns the average as a double
}                                                        // Ends the average function

bool isWithinLimit(double averageCurrent, double maximumCurrent) { // Defines the limit decision
    return averageCurrent <= maximumCurrent;             // Returns true when the average does not exceed the maximum
}                                                        // Ends the Boolean function

/*
 * Analysis:
 * 1. Current readings have decimal parts (for example 1.50 A), and their average
 *    can too. Returning int would truncate the fractional part, so 2.25 would
 *    become 2. Returning double keeps the exact average.
 * 2. isWithinLimit returns true when averageCurrent <= maximumCurrent, so an
 *    average exactly equal to the maximum still meets the limit.
 * 3. requestedSamples is only what the user planned to enter. samplesRead counts
 *    the values the while loop actually read from the file, so the average is
 *    based on real data. If the file had fewer valid numbers, dividing by
 *    requestedSamples would give a wrong average.
 * 4. Data written with ofstream may still be in a buffer. Closing it flushes
 *    every reading to the disk; if the input stream opened first, it could read
 *    an empty or incomplete file and count fewer samples.
 */
