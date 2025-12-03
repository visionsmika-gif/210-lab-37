#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
using namespace std;

int gen_hash_index(const string& str);

int main() {

    // Open the file.
    const string FILE_NAME = "data.txt";
    ifstream dataFile;
    dataFile.open(FILE_NAME);
    if (!dataFile) {
        cout << "ERROR: Could not open the file " << FILE_NAME << ".\n";
        return 1;
    }

    // Declare a hash table.
    map<int, list<string>> hash_table;      // The map's key is the hash index.
                                            // The map's value is a list of all the strings that map to that hash index.

    // Read strings from the file.
    string str;
    int hashIndex;
    while (getline(dataFile, str)) {
        hashIndex = gen_hash_index(str);        // Get a string's ASCII sum, which will serve as its hash index.
        hash_table[hashIndex].push_back(str);   // Insert the string into the list using push_back().
    }

    // Display the first 100 map entries.
    int i = 0;
    for (const auto& pair : hash_table) {       // Iterate through each pair in the map.
        if (i == 100) {
            break;
        }
        cout << "Hash index: " << pair.first << " - ";      // Output the hash index.
        for (const string& s : pair.second) {               // Output all the strings corresponding with that hash index.
            cout << s << ", ";
        }
        cout << "\n\n\n";
        ++i;
    }

    return 0;
}


// Function to receive a single string and return the sum of that string's character's ASCII values.
int gen_hash_index(const string& str) {
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