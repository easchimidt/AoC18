#include <iostream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;

inline char invertCase(char c);

int main()
{
    int counter = 0;;
    string line;
    stack<char> final_result;

    fstream file;
    file.open("day5.in");

    if (!file.is_open())
    {
        cout << "Error opening file! Exiting..." << endl;
        return -1;
    }

    // There's only one BIIIG line
    getline(file, line);
    file.close();

    while (counter < line.length()) {
        char aux = line[counter++];

        if (final_result.empty() || (final_result.top() - invertCase(aux) != 0)) {
            final_result.push(aux);
        }
        else {
            final_result.pop();                
        }
    }

    cout << "The number of units remaining is " << final_result.size() << endl;
    
    return 0;
}

inline char invertCase(char c)
{
    // lower case char has ascii value >= 97 and <= 122
    if (c >= 65 && c <= 90) {
        return c + 32;
    }
    else if (c >= 97 && c <= 122) {
        return c - 32;
    }
}