#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

#define FABRIC_INCHES 1000

typedef struct s_fabric_data {
	uint16_t id;
	uint16_t left_offset;
	uint16_t top_offset;
	uint8_t width;
	uint8_t height;
} fabric_data;

void print_fabric_data(vector<fabric_data *> f_data);
fabric_data* extract_fabric_data(string data);
void paint_fabric(uint16_t fabric_map[][FABRIC_INCHES], fabric_data *new_fabric_data, vector<uint8_t> &unique_ids);

int main()
{
	uint16_t id = 1;
	uint16_t fabric_map[FABRIC_INCHES][FABRIC_INCHES] = {0};
	fstream file;
	string line;
	vector<uint8_t> unique_id;

	file.open("day3.in");

	if (!file.is_open()) {
		cout << "Error opening file! Exiting..." << endl;
		return -1;
	}

	unique_id.push_back(0); // Insert first element to fill position 0

	while (getline(file, line)) {
		fabric_data *new_fabric_data = extract_fabric_data(line);
		new_fabric_data->id = id++;		
		unique_id.push_back(1);

		paint_fabric(fabric_map, new_fabric_data, unique_id);
		// print_fabric_data(new_fabric_data);

		free(new_fabric_data);
	}	

	for (int i = 1 ; i < unique_id.size(); i++)
	{
		if (unique_id[i] == 1) {
			cout << "unique_id: " << i << endl;
		}
	}

	return 0;
}

fabric_data* extract_fabric_data(string data)
{
	fabric_data *new_fabric_data = (fabric_data*) malloc(sizeof(fabric_data));

	auto pos_at = data.find("@");
	auto substring = data.substr(pos_at + 1, data.npos); // "xxx,yyy: aaxbb"
	auto pos_comma = substring.find(",");
	auto l_offset = substring.substr(0, pos_comma); // "xxx"
	auto pos_colon = substring.find(":");
	auto t_offset = substring.substr(pos_comma+1, pos_colon); // "yyy"
	auto size = substring.substr(pos_colon+2, substring.npos);
	auto x_pos = size.find("x");
	auto width = size.substr(0, x_pos); //"aa"
	auto height = size.substr(x_pos+1, size.npos); // "bb"

	new_fabric_data->left_offset = (uint16_t)stoi(l_offset);
	new_fabric_data->top_offset = (uint16_t)stoi(t_offset);
	new_fabric_data->width = (uint8_t)stoi(width);
	new_fabric_data->height = (uint8_t)stoi(height);

	return new_fabric_data;
}

void paint_fabric(uint16_t fabric_map[][FABRIC_INCHES], fabric_data *new_fabric_data, vector<uint8_t> &unique_id)
{
	for (uint16_t i = new_fabric_data->top_offset; i < (new_fabric_data->top_offset + new_fabric_data->height); i++)
	{
		for (uint16_t j = new_fabric_data->left_offset; j < (new_fabric_data->left_offset + new_fabric_data->width); j++)
		{
			if (fabric_map[i][j] != 0) {
				unique_id[fabric_map[i][j]] = 0;
				unique_id[new_fabric_data->id] = 0;
			}
			fabric_map[i][j] = new_fabric_data->id;
		}
	}
}

void print_fabric_data(vector<fabric_data *> f_data)
{
	for (int i = 0 ; i < f_data.size(); i++)
	{
		cout << "ID: " << f_data[i]->id;
		cout << " | left offset: " << f_data[i]->left_offset;
		cout << " | top offset: " << f_data[i]->top_offset;
		cout << " | width: " << unsigned(f_data[i]->width);
		cout << " | height: " << unsigned(f_data[i]->height);
		cout << endl;
	}
}