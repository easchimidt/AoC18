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
	uint32_t short_dist;
	uint16_t index_short_dist;
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
	
	for (int i = 0; i < biggest_row; i++) 
	{
        for (int j = 0; j < biggest_col; j++) 
		{
			struct distance_t *aux = &distances_grid[i * biggest_row + j];
			bool repeated = false;
			for (int index = 0; index < grid_data.size(); index++)
			{
				auto distance = abs(i - grid_data[index].row) + abs(j - grid_data[index].col);
				
				if (index == 0 || distance < aux->short_dist) {
					aux->short_dist = (uint32_t) distance;
					aux->index_short_dist = index;
					repeated = false;
				}
				else if (distance == aux->short_dist) {
					repeated = true;
				}
			}
			auto it = area.find(aux->index_short_dist);

			if (!repeated) {
				if (it == area.end()) {
					area.insert(std::pair<uint32_t, uint32_t> (aux->index_short_dist, 1));
				}
				else {
					it->second++; // increment sum of ocurrences of index
				}
			}
        }
    }

	// Remove areas from borders
	for (int j = 0; j < biggest_col; j++) 
	{
		// First row
		struct distance_t *aux = &distances_grid[j];
		auto it = area.find(aux->index_short_dist);
		
		if (it != area.end()) {
			area.erase(it);
		}

		// Last row
		aux = &distances_grid[(biggest_row - 1) * biggest_row + j];
		it = area.find(aux->index_short_dist);
		
		if (it != area.end()) {
			area.erase(it);
		}
	}

	for (int j = 0; j < biggest_row; j++) 
	{
		// First column
		struct distance_t *aux = &distances_grid[j * biggest_row];
		auto it = area.find(aux->index_short_dist);
		
		if (it != area.end()) {
			area.erase(it);
		}

		// Last Column
		aux = &distances_grid[j * biggest_row - 1];
		it = area.find(aux->index_short_dist);
		
		if (it != area.end()) {
			area.erase(it);
		}
	}

	uint32_t biggest_area = 0, index = 0;
	for (auto it = area.begin(); it != area.end(); ++it)
    {
        if (it->second > biggest_area) {
			biggest_area = it->second;
			index = it->first;
		}
    }

	cout << "The biggest area is " << biggest_area << " from position " << index << endl;

	free(distances_grid);

    return 0;
}