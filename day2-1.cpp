#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

#define ALPHABET_SIZE 26

using namespace std;

void check_repetition(string line, int *letters);

int main()
{
    fstream file;
    string line;
    int num_2 = 0, num_3 = 0, i;
    int letters[ALPHABET_SIZE] = {0};
    bool found_2, found_3;

    file.open("day2.in");

    if (!file.is_open()) 
    {
        cout << "Error opening file. Exiting..." << endl;
        return -1;
    }

    while (getline(file, line))
    {
        check_repetition(line, letters);

        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            if (letters[i] == 2 && !found_2) {
                num_2++;
                found_2 = true;
            }
            if (letters[i] == 3 && !found_3) {
                num_3++;
                found_3 = true;
            }
        }

        // Set letters count to 0
        memset(letters, 0, ALPHABET_SIZE * sizeof(int));

        found_2 = found_3 = false;   
    }

    cout << "Result: " << num_2 << " * " << num_3 << " = " << num_2 * num_3 << endl;

}

void check_repetition(string line, int *letters) 
{
    int c_count = 0;

    while (c_count < line.size()) 
    {
        char temp = line[c_count++];
        int alphabet_position = temp - 97;

        if (alphabet_position >= 0 && alphabet_position <= 25) {
            letters[alphabet_position]++;
        }
    }
}