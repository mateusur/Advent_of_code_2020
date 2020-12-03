#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
#include <sstream>
#include <vector>
using namespace std;
void read_from_file(const string& filename, stringstream& buffer) {
    ifstream file(filename);
    if (file) {
        buffer << file.rdbuf();
        file.close();
    }
}
int part01() {
    stringstream buffer;
    read_from_file("day02_input.txt", buffer);
    int lower_bound, upper_bound, valid_passwords{ 0 };
	size_t occurrences{0};
    char delim, colon,character;
    string password;
    while (buffer) {
        buffer >> lower_bound >> delim >>upper_bound >> character  >> colon>> password;
        occurrences = count(password.begin(), password.end(),character);
    	if(occurrences >= lower_bound && occurrences <= upper_bound) {
            ++valid_passwords;
    	}
    }
    cout << valid_passwords << endl;
    return valid_passwords;
}

int part02() {
    stringstream buffer;
    read_from_file("day02_input.txt", buffer);
    size_t position1, position2;
	int valid_passwords{0};
    char delim,colon, character;
    string password;
    while (buffer) {
        buffer >> position1 >> delim >> position2 >> character >> colon >>password;
		if((password.at(position1-1)==character && password.at(position2 - 1) != character) || 
           (password.at(position2 - 1) == character && password.at(position1 - 1) != character)) {
       		valid_passwords++;
		}
    }
    cout << valid_passwords << endl;
    return valid_passwords;
}

int main() {
    part01();
    part02();
    return 0;
}