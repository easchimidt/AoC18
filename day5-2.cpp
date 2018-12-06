#include <iostream>
#include <fstream>
#include <string>
#include <stack>

#define ALPHABET_SIZE 26

using namespace std;

inline char invertCase(char c);

int main()
{
    int counter = 0;;
    string line;
    stack<char> final_result;
    int count[ALPHABET_SIZE] = {0}, best_result = 0xffff;

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

    for (int i = 0 ; i < ALPHABET_SIZE; i++) {
        char to_remove = i + 65;
        counter = 0;
        while (counter < line.length()) {
            char aux = line[counter++];

            if (aux == to_remove || aux == invertCase(to_remove)) {
                continue;
            }                

            if (final_result.empty() || (final_result.top() - invertCase(aux) != 0)) {
                final_result.push(aux);
            }
            else {
                final_result.pop();                
            }
        }
        count[i] = final_result.size();

        if (count[i] < best_result) {
            best_result = count[i];
        }
        final_result = stack<char>();
    }
    
    cout << "The shortest polymer size was " << best_result << endl;
    
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