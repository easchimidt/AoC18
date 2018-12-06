#include <iostream>
#include <fstream>
#include <string>
#include <stack>

#define ALPHABET_SIZE 26

using namespace std;

int main()
{
    int counter = 0;;
    string line;
    stack<char> final_result;
    int best_result = 0xffff;

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

    for (int i = 0 ; i < ALPHABET_SIZE; i++) 
    {
        char to_remove = i + 65;
        counter = 0;

        while (counter < line.length()) 
        {
            char aux = line[counter++];

            if (aux == to_remove || (aux ^ to_remove) == 32) {
                continue;
            }

            if (final_result.empty() || ((final_result.top() ^ aux) != 32)) {
                final_result.push(aux);
            }
            else {
                final_result.pop();                
            }
        }

        if (final_result.size() < best_result) {
            best_result = final_result.size();
        }

        final_result = stack<char>();
    }
    
    cout << "The shortest polymer size was " << best_result << endl;
    
    return 0;
}