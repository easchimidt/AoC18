#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

int main()
{
    fstream file;
    string line;
    tm _tm = {};
    
    file.open("day4.in");

    if (!file.is_open())
    {
        cout << "Error opening file. Exiting..." << endl;
        return -1;
    }

    getline(file, line);
    stringstream ss(line.substr(1, 16));

    cout << ss.str() << endl;

    ss >> get_time(&_tm, "%Y-%m-%d %H:%M");

    if (ss.fail()) {
        cout << "Parse failed!" << endl;
    }
    else {
        //std::cout << std::put_time(&_tm, "%c") << '\n';
        cout << _tm.tm_mday << "/" << _tm.tm_mon << "/" << (_tm.tm_year < 0 ? _tm.tm_year + 1900 : _tm.tm_year) << " " << _tm.tm_min << ":" << _tm.tm_hour << endl;
    }


    //[1518-08-29 00:24] falls asleep
    return 0;
}
