#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <list>
#include <map>

using namespace std;

/* structures  */
typedef struct raw_data_t
{
	uint32_t id;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t status; // 0 -> begins shift ; 1 -> fall sleep; 2 -> wakes up
} raw_data;

typedef struct guard_data_t {
    uint32_t id;
	uint32_t total_slept;
	uint8_t sum_minutes_slept[60];	
} guard_data;

/* forward declarations */
void parse_data(list<raw_data> &database, string line);
list<raw_data>::iterator find_insert_position(list<raw_data> &database, raw_data &new_entry);
void calculate_time_slept(list<raw_data> &database);
void print_list(list<raw_data> &database);
void print_single_entry(raw_data &entry);

int main()
{
    fstream file;
    string line;
	list<raw_data> database;

    file.open("day4.in");

    if (!file.is_open())
    {
        std::cout << "Error opening file. Exiting..." << endl;
        return -1;
    }
    while (getline(file, line))
	{
		parse_data(database, line);
	}
    //print_list(database);

    calculate_time_slept(database);

    return 0;
}

void parse_data(list<raw_data> &database, string line)
{
	tm _tm = {};
	stringstream ss(line.substr(1, 16));

    ss >> get_time(&_tm, "%Y-%m-%d %H:%M");

    if (ss.fail()) {
    	cout << "Parse failed!" << endl;
	}
	else {
		raw_data new_entry;
		new_entry.id = 0;
		new_entry.month = (uint8_t)_tm.tm_mon + 1;
		new_entry.day = (uint8_t)_tm.tm_mday;
		new_entry.hour = (uint8_t)_tm.tm_hour;
		new_entry.minute = (uint8_t)_tm.tm_min;
		
        size_t pos = line.find('#', 18);
        if (pos != string::npos) {
            new_entry.status = 0;
            string aux = line.substr(pos+1);
            new_entry.id = stoi(aux.substr(0, aux.find(' ')));
        }
        else if (line.find("falls", 18) != string::npos) 
        {
            new_entry.status = 1; // state falls asleep
        } 
        else 
        { 
            new_entry.status = 2; // state wakes up
        }        

        auto position = find_insert_position(database, new_entry);
        
        database.insert(position, new_entry);
	}
}

list<raw_data>::iterator find_insert_position(list<raw_data> &database, raw_data &new_entry)
{
    auto it = database.begin();
	
    while (it != database.end())
    {
        if (new_entry.month < (*it).month) {
            break;
        }
        else if (new_entry.month == (*it).month) {
            // Same month. Find day
            if (new_entry.day < (*it).day) {
                break;
            }
            else if (new_entry.day == (*it).day) {
                // Same day, find hour
                if (new_entry.hour < (*it).hour)
                {
                    break;
                }
                else if (new_entry.hour == (*it).hour)
                {
                    // Same hour, find minute
                    if (new_entry.minute < (*it).minute) {
                        break;
                    }
                }
            }
        }

        ++it;            
    }
	
    return it;
}

void calculate_time_slept(list<raw_data> &database)
{    
    uint32_t curr_id = 0;
    uint8_t min_slept = 0, min_woke_up = 0;
    guard_data *current_guard = nullptr;
    map<uint32_t, guard_data*> guards;
    uint32_t max_slept = 0, min_max_slept = 0, id_max_slept = 0;

    auto it = database.begin();

    while (it != database.end())
    {
        // Get or create guard
        if ((*it).status == 0 && (*it).id > 0) {
            auto it_guard = guards.find((*it).id);
            if (it_guard != guards.end()) {
                current_guard = it_guard->second;
            }
            else {
                guard_data* new_guard = (guard_data *) malloc (sizeof(guard_data));
                new_guard->id = (*it).id;
                guards.insert(std::pair<uint32_t, guard_data*>(new_guard->id, new_guard));

                current_guard = new_guard;

            }
            advance(it, 1);
        }

        // Get time slept
        if ((*it).status == 1) {
            min_slept = (*it).minute;
            advance(it, 1);
        }

        // Get time awake
        if ((*it).status == 2) {
            min_woke_up = (*it).minute;
            advance(it, 1);
        }
        
        current_guard->total_slept += min_woke_up  - min_slept;

        for (uint8_t i = min_slept; i < min_woke_up; i++)
        {
            current_guard->sum_minutes_slept[i]++;

            if (current_guard->sum_minutes_slept[i] > max_slept)
            {
                max_slept = current_guard->sum_minutes_slept[i];
                min_max_slept = i;
                id_max_slept = current_guard->id;
            }
        }
    }
    
    cout << id_max_slept << " sleept most, at minute " << min_max_slept << " for " << max_slept << endl;
    cout << "Result: " << id_max_slept*min_max_slept << "." << endl;

    // free guards
    for (auto it = guards.begin(); it != guards.end(); ++it)
    {
        free(it->second);
    }
}

void print_list(list<raw_data> &database)
{    
    for (auto it = database.begin(); it != database.end(); ++it)
    {
        print_single_entry(*it);
    }
}

void print_single_entry(raw_data &entry)
{
    cout << "id: " << entry.id << ", status: " << (unsigned)entry.status << ", ";
    cout << unsigned(entry.day) << "/" << unsigned(entry.month) << ", ";
    cout << unsigned(entry.hour) << ":" << unsigned(entry.minute) << endl;
}