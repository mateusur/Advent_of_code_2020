#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <set>
using namespace std;

void read_from_file(const std::string& filename, std::stringstream& buffer) {
	std::ifstream file(filename);
	if (file) {
		buffer << file.rdbuf();
		file.close();
	}
}

class Plane
{
	const pair<unsigned, unsigned> rows{0, 127};
	const pair<unsigned, unsigned> columns{0, 7};
	stringstream buffer;
	unsigned row, column, highest_ID;
	int calculate(const string& line) {

		pair<unsigned, unsigned> number;
		
		char current = line.at(0);
		if (current == 'F') {
			number.first = rows.first;
			number.second = rows.second / 2;
		}
		else if (current == 'B') {
			number.first = (rows.second / 2) + 1;
			number.second = rows.second;
		}
		for (size_t i = 1; i < line.size() - 3; ++i) {
			current = line.at(i);
			unsigned diffrence = (number.second - number.first) % 2 == 0
				? (number.second - number.first) / 2
				: (number.second - number.first) / 2 + 1;
			if (current == 'F') {
				//number.first += diffrence;
				number.second -= diffrence;
			}
			else {
				number.first += diffrence;
				//number.second -= diffrence;
			}
		}
		unsigned row_fun = number.first;
		current = line.at(line.size() - 3);
		if (current == 'L') {
			number.first = columns.first;
			number.second = columns.second / 2;
		}
		else if (current == 'R') {
			number.first = (columns.second / 2) + 1;
			number.second = columns.second;
		}
		for (size_t i = line.size() - 2; i < line.size(); ++i) {
			current = line.at(i);
			unsigned diffrence = (number.second - number.first) % 2 == 0
				? (number.second - number.first) / 2
				: (number.second - number.first) / 2 + 1;
			if (current == 'L') {
				//number.first += diffrence;
				number.second -= diffrence;
			}
			else {
				number.first += diffrence;
				//number.second -= diffrence;
			}
		}
		unsigned column_fun = number.first;

		return seatID(row_fun, column_fun);
	}
	int your_ID(const set<int>& IDs) {
		int previous, next;
		int missing;
		auto itr = IDs.begin();
		previous = *itr;
		itr++;
		for (itr ; itr != IDs.end(); ++itr) {
			next = *(itr);
			if(next - previous == 2 ) {
				missing = next-1;
			}
			previous = next;
		}
		return missing;
	}
public:
	Plane(const string& filename): row(0), column(0),highest_ID(0) {
		std::ifstream file(filename);
		if (file) {
			buffer << file.rdbuf();
			file.close();
		}
	}

	int seatID(const int& row, const int& column) const { return 8 * row + column; }
	int part01() {
		string line;
		int ID;
		while (buffer >> line) {
			ID = calculate(line);
			if(ID > highest_ID) {
				highest_ID = ID;
			}
		}
		return highest_ID;
	}
	int part02() {
		string line;
		set<int> IDs;
		int ID;
		while (buffer >> line) {
			ID = calculate(line);
			IDs.insert(ID);
		}
		
		return your_ID(IDs);
	}
};

int main() {
	Plane plane("day05_input.txt");
	//cout << plane.part01();
	cout << plane.part02();
	return 0;
}
