// COMSC-210 | Lab 38 | Mika Aquino
// IDE used: Visual Studio 2022

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
using namespace std;

// Function to generate a hash index for a string.
int gen_hash_index(const string& str);

// Functions for menu choices.
int getMenuChoice();
void printFirstHundred(const map<int, list<string>>& hash_table);
void searchForKey(const map<int, list<string>>& hash_table);
void addKey(map<int, list<string>>& hash_table);
void removeKey(map<int, list<string>>& hash_table);
void modifyKey(map<int, list<string>>& hash_table);

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

    // Prompt the user with a menu, allowing them to choose what to do with the hash table.
    int choice;
    do {
        choice = getMenuChoice();
        cin.ignore();
        if (choice == 1) {                      // [1] Print the first 100 entries.
            printFirstHundred(hash_table);
        }
        else if (choice == 2) {                 // [2] Search for a key.
            searchForKey(hash_table);
        }
        else if (choice == 3) {                 // [3] Add a key.
            addKey(hash_table);
        }
        else if (choice == 4) {                 // [4] Remove a key.
            removeKey(hash_table);
        }
        else if (choice == 5) {                 // [5] Update a key.
            modifyKey(hash_table);
        }
        cout << "\n";
    } while (choice != 0);                      // [0] Quit.

    return 0;
}

// Function to receive a single string and return the sum of that string's characters' ASCII values.
int gen_hash_index(const string& str) {
    int sum = 0;
    for (char c : str) {    // Go through each character.
        sum += (int)c;      // Add each character's ASCII value to the sum.
    }
    return sum;
}

// Function to display a menu to the user and return the choice they pick (an int).
int getMenuChoice() {
    int choice;

    cout << "MENU:\n";
    cout << "[1] Print the first 100 entries\n";
    cout << "[2] Search for a key\n";
    cout << "[3] Add a key\n";
    cout << "[4] Remove a key\n";
    cout << "[5] Modify a key\n";
    cout << "[0] Exit\n";
    
    // Validate the user's choice.
    do {
        cout << "Choice --> ";
        cin >> choice;
        if (choice < 0 || choice > 5) {
            cout << "ERROR: Inavlid choice. Please enter a number from 0 to 5.\n";
        }
    } while (choice < 0 || choice > 5);

    return choice;
}

// Function to display the first 100 map entries.
void printFirstHundred(const map<int, list<string>>& hash_table) {
    int i = 0;
    const int NUM_ENTRIES = 100;

    // Iterate through each pair in the map.
    for (const auto& pair : hash_table) {
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

        // Print extra spaces for neater output.
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

// Function to search for a key in the hash table.
void searchForKey(const map<int, list<string>>& hash_table) {
    // Prompt the user to enter a key.
    string key;
    cout << "Enter a key to search for --> ";
    getline(cin, key);

    // Get the key's hash index.
    int hashIndex = gen_hash_index(key);

    // Go to the correct "bucket" in the hash table, according to the hash index.
    auto it = hash_table.find(hashIndex);
    if (it != hash_table.end()) {               // If the "bucket" was located,
        for (const string& s : it->second) {    // attempt to search for the key.
            if (s == key) {
                cout << "Key successfully found at hash index " << hashIndex << ".\n";
                return;
            }
        }
    }
    // The key was not found if either:
        // The "bucket" was not in the hash table
        // OR the key was not found in the "bucket."
    cout << "Key not found.\n";
}

// Function to add a key to the hash table.
void addKey(map<int, list<string>>& hash_table) {
    // Prompt the user to enter a key.
    string key;
    cout << "Enter a key to add --> ";
    getline(cin, key);

    int hashIndex = gen_hash_index(key);    // Get the key's hash index.
    hash_table[hashIndex].push_back(key);   // Insert the key into the list using push_back().

    cout << "Key successfully added at hash index " << hashIndex << ".\n";
}

// Function to remove a key from the hash table.
void removeKey(map<int, list<string>>& hash_table) {
    // Prompt the user to enter a key.
    string key;
    cout << "Enter a key to remove --> ";
    getline(cin, key);

    // Get the key's hash index.
    int hashIndex = gen_hash_index(key);

    // Go to the correct "bucket" in the hash table, according to the hash index.
    auto it = hash_table.find(hashIndex);
    if (it != hash_table.end()) {   // If the "bucket" was located,
        // attempt to search for the key by iterating through the list.
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            if (*it2 == key) {
                it->second.erase(it2);  // If the key was found, remove it.
                cout << "Key successfully removed.\n";
                return;
            }
        }
    }
    // The key is not found if either:
        // The "bucket" was not in the hash table
        // OR the key was not found in the "bucket."
    cout << "Key not found.\n";
}

// Function to modify a key in the hash table.
void modifyKey(map<int, list<string>>& hash_table) {
    // Prompt the user to enter a key to update.
    string oldKey;
    cout << "Enter a key to update --> ";
    getline(cin, oldKey);
    
    // Try to remove the old key.
    int oldHashIndex = gen_hash_index(oldKey);

    bool successfulRemoval = false;
    auto it = hash_table.find(oldHashIndex);
    if (it != hash_table.end()) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            if (*it2 == oldKey) {
                it->second.erase(it2);
                successfulRemoval = true;
                break;
            }
        }
    }
    if (!successfulRemoval) {
        cout << "Key not found. Nothing updated.\n";
        return;
    }

    // Prompt the user for a new key.
    string newKey;
    cout << "Enter the new key --> ";
    getline(cin, newKey);

    // Add the new key.
    int newHashIndex = gen_hash_index(newKey);    // Get the key's hash index.
    hash_table[newHashIndex].push_back(newKey);   // Insert the key into the list using push_back().

    cout << "Key successfully updated.\n";
}