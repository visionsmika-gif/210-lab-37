#include <iostream>
using namespace std;

int sum_ascii(const string& str);

int main() {

    cout << sum_ascii("Hello"); // 72 + 101 + 108 + 108 + 111 = 500

    /*
    char a = 'A';
    cout << a << endl;
    cout << (int)a << endl;
    int b = 66;
    cout << b << endl;
    cout << (char)b << endl;
    */


    return 0;
}


// The function receives a single string and returns the sum of that string's character's ASCII values.
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