#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>

using namespace std;

struct data_t {
    uint16_t col;
    uint16_t row;
};

struct distance_t {
	uint32_t total_dist;
};

int main()
{
    string line;
    vector<struct data_t> grid_data;
	map<uint32_t, uint32_t> area;
    uint16_t biggest_row = 0, biggest_col = 0;
    
    fstream file;
    file.open("day6.in");

    if (!file.is_open())
    {
        cout << "Error opening file! Exiting..." << endl;
        return -1;
    }

    while (getline(file, line))
    {
        auto pos_comma = line.find(",");
        data_t d;
        d.col = (uint16_t) stoi(line.substr(0,pos_comma));
        d.row = (uint16_t) stoi(line.substr(pos_comma + 2));
        grid_data.push_back(d);

        if (d.col > biggest_col) {
            biggest_col = d.col;
        }

        if (d.row > biggest_row) {
            biggest_row = d.row;
        }
    }

    file.close();

    struct distance_t *distances_grid = (distance_t *) calloc (biggest_col * biggest_row, sizeof(distance_t));	
	int sum = 0; 
	for (int i = 0; i < biggest_row; i++) 
	{
        for (int j = 0; j < biggest_col; j++) 
		{
			struct distance_t *aux = &distances_grid[i * biggest_row + j];
			bool repeated = false;
			for (int index = 0; index < grid_data.size(); index++)
			{
				aux->total_dist += abs(i - grid_data[index].row) + abs(j - grid_data[index].col);				
			}			

			if (aux->total_dist < 10000)
			{
				sum++;
			}
        }
    }

	cout << "The biggest area is " << sum <<  endl;

	free(distances_grid);

    return 0;
}