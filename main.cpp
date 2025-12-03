#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int sum_ascii(const string& str);

int main() {

    // Open the file.
    const string FILE_NAME = "data.txt";
    ifstream dataFile;
    dataFile.open(FILE_NAME);
    if (!dataFile) {
        cout << "ERROR: Could not open the file " << FILE_NAME << ".\n";
        return 1;
    }

    // Read strings from the file.
    string str;
    int grandTotal = 0;
    while (getline(dataFile, str)) {
        grandTotal += sum_ascii(str);   // Add each string's ASCII values into a grand total.
    }

    // Output the grand total.
    cout << grandTotal;

    return 0;
}


// Function to receive a single string and return the sum of that string's character's ASCII values.
int sum_ascii(const string& str) {
    int sum = 0;
    for (char c : str) {    // Go through each character.
        sum += (int)c;      // Get each character's ASCII value, adding it to the sum.
    }
    return sum;
}

/*
These targets are present in the dataset and can be used for testing:
536B9DFC93AF
1DA9D64D02A0
666D109AA22E
E1D2665B21EA
*/