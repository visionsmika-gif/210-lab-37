// COMSC-210 | Lab 38 | Mika Aquino
// IDE used: Visual Studio 2022

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
using namespace std;

int gen_hash_index(const string& str);

int getMenuChoice();
void printFirstHundred(const map<int, list<string>>& hash_table);

int main() {
    // Open the file.
    const string FILE_NAME = "data.txt";
    ifstream dataFile;
    dataFile.open(FILE_NAME);
    if (!dataFile) {
        cout << "ERROR: Could not open the file " << FILE_NAME << ".\n";
        return 1;
    }

    // Declare a map for the hash table.
    map<int, list<string>> hash_table;      // The map's key is the hash index.
                                            // The map's value is a list of all the strings that map to that hash index.

    // Read strings from the file.
    string str;
    int hashIndex;
    while (getline(dataFile, str)) {
        hashIndex = gen_hash_index(str);        // Get the string's ASCII sum, which will serve as its hash index.
        hash_table[hashIndex].push_back(str);   // Insert the string into the list using push_back().
    }

    int choice;
    do {
        choice = getMenuChoice();

        if (choice == 1) {                      // [1] Print the first 100 entries
            printFirstHundred(hash_table);
        }
        else if (choice == 2) {                 // [2]

        }
        else if (choice == 3) {

        }

        cout << "\n";
    } while (choice != 0);

    // Display the first 100 map entries.
    

    return 0;
}

// Function to receive a single string and return the sum of that string's characters' ASCII values.
int gen_hash_index(const string& str) {
    int sum = 0;
    for (char c : str) {    // Go through each character.
        sum += (int)c;      // Get each character's ASCII value, adding it to the sum.
    }
    return sum;
}

int getMenuChoice() {
    int choice;

    cout << "MENU:\n";
    cout << "[1] Print the first 100 entries\n";
    cout << "[2] Search for a key\n";
    cout << "[3] Modify a key\n";
    cout << "[0] Exit\n";

    do {
        cout << "Choice --> ";
        cin >> choice;
        if (choice < 0 || choice > 3) {
            cout << "ERROR: Inavlid choice. Please enter a number from 0 to 3.\n";
        }
    } while (choice < 0 || choice > 3);

    return choice;
}

void printFirstHundred(const map<int, list<string>>& hash_table) {
    int i = 0;
    const int NUM_ENTRIES = 100;
    for (const auto& pair : hash_table) {       // Iterate through each pair in the map.
        if (i == NUM_ENTRIES) {
            break;
        }

        // Output the first part of the pair: the hash index.
        cout << "Hash index " << pair.first << " - ";

        // Output the second part of the pair: the strings corresponding with that hash index.
        int j = 0;
        const int NUM_PRINT = 3;    // Only output a few strings to prevent huge output.
        for (const string& s : pair.second) {
            if (j == NUM_PRINT) {
                break;
            }
            cout << s << " ";
            ++j;
        }

        // Print extra spaces for neatly aligned output.
        const int STRING_SIZE = 12;
        if (pair.second.size() < NUM_PRINT) {
            for (int i = 0; i < NUM_PRINT - pair.second.size(); ++i) {
                cout << string(STRING_SIZE + 1, ' ');
            }
        }

        // Since there are too many strings to print all of them, print the total number of strings instead.
        cout << "... ";
        cout << pair.second.size() << " total string(s)\n";
        ++i;
    }
}