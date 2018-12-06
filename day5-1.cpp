#include <iostream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;

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

        if (final_result.empty() || ((final_result.top() ^ aux) != 32)) {
            final_result.push(aux);
        }
        else {
            final_result.pop();                
        }
    }

    cout << "The number of units remaining is " << final_result.size() << endl;
    
    return 0;
}