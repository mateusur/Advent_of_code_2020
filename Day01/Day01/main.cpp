#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
void read_from_file(const string& filename, stringstream& buffer) {
    string d = "day01_input.txt";
    ifstream file(filename);
    
    if (file) {
        buffer << file.rdbuf();
        file.close();
    }
}
int part01() {
    std::stringstream buffer;
    read_from_file("day01_input.txt", buffer);
    vector<int> values;
    int value;
    while (buffer >> value) {
        values.emplace_back(value);
    }
    for (int j = 0; j < values.size(); ++j) {
        for (int i = j + 1; i < values.size(); ++i) {
            if (values.at(j) + values.at(i) == 2020) {
                cout << values.at(j) * values.at(i) << endl;
                return values.at(j) * values.at(i);
            }
        }
    }
    return -1;
}
int part02() {
    std::stringstream buffer;
    read_from_file("day01_input.txt", buffer);
    vector<int> values;
    int value;
    while (buffer >> value) {
        values.emplace_back(value);
    }
    for (int j = 0; j < values.size(); ++j) {
        for (int i = j + 1; i < values.size(); ++i) {
            for(int k = i+1; k < values.size(); ++k) {
                if (values.at(j) + values.at(i)+ values.at(k) == 2020) {
                    cout << values.at(j) * values.at(i) * values.at(k) << endl;
                    return values.at(j) * values.at(i) * values.at(k);
                }
            }
        }
    }
    return -1;
}


int main() {
    part01();
    part02();
	return 0;
}