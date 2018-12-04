#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>

#define ALPHABET_SIZE 26

using namespace std;

int compare_strings(string line1, string line2);

int main()
{
    fstream file;
    string line;
    int num_2 = 0, num_3 = 0;
    int min_diff = 500, min_idx1 = -1, min_idx2 = -1;
    int letters[ALPHABET_SIZE] = {0};
    vector<string> lines;
    bool found_2, found_3;

    file.open("day2.in");

    if (!file.is_open()) 
    {
        cout << "Error opening file. Exiting..." << endl;
        return -1;
    }

    while (getline(file, line))
    {
        lines.push_back(line);
    }

    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = i+1; j < lines.size(); j++)
        {
            int diff = compare_strings(lines[i], lines[j]);

            if (diff < min_diff) {
                min_diff = diff;
                min_idx1 = i;
                min_idx2 = j;
            }
        }
    }

    string result = "";
    for (int i = 0; i < lines[min_idx1].length(); i++)
    {
        if (lines[min_idx1][i] == lines[min_idx2][i]) {
            result += lines[min_idx1][i];
        }
    }
    
    cout << result << endl;
}

int compare_strings(string line1, string line2) 
{
    int diff = 0;

    if (line1.length() != line2.length()) {
        cout << "error: lines have different lenghts! " << line1.length() << ", " << line2.length() << endl;
        return -1;
    }

    for (int i = 0; i < line1.length(); i++)
    {
        if (line1[i] != line2[i]) {
            diff++;
        }
    }
    return diff;
}