#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    int i = 0, j = 0, temp = 0;
    long int sum = 0, aux;
    string current;
    vector<long int> occurrences, input;
    bool found_double_occurrence = false;
    fstream file;
    file.open("day1-1.in");

    if (!file.is_open())
    {
        cout << "Error opening file! Exiting..." << endl;
        return -1;
    }

    while (getline(file, current))
    {
        input.push_back(stoi(current));
    }

    while (!found_double_occurrence)
    {
        if (i >= input.size()) {
            i = 0;
            temp++;
        }        

        sum += input[i++];

        j = 0;

        while (j < occurrences.size()) {

            if (sum == occurrences[j++]) {
                found_double_occurrence = true;
            }
        }   

        if (!found_double_occurrence) {
            occurrences.push_back(sum);
        }         
    }

    cout << sum << endl;

    file.close();
    return 0;
}