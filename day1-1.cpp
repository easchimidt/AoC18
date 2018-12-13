#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    long int sum = 0, aux;
    string current;
    
    fstream file;
    file.open("day1.in");

    if (!file.is_open())
    {
        cout << "Error opening file! Exiting..." << endl;
        return -1;
    }

    while (getline(file, current))
    {
        aux = stoi(current);
        sum += aux;
    }

    cout << sum << endl;

    file.close();
    return 0;
}