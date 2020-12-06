#include <string>
#include <algorithm>
#include <iosfwd>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <chrono>
#include <regex>
#include <set>

using namespace std;

class CustomCustoms
{
	ifstream file;
	set<char> anwsers;
	int line_counter = 0;

	void update(const string& line) {
		for (const char& c : line) {
			if (anwsers.find(c) == anwsers.end()) {
				anwsers.insert(c);
			}
		}
	}

	void update2(const vector<string>& lines) {
		set<char> tmp;
		for (size_t i = 0; i < lines.size(); ++i) {
			tmp.clear();
			for (const char& c : lines[i]) {
				if (tmp.find(c) == tmp.end()) {
					tmp.insert(c);
				}
			}
			if (i == 0) {
				anwsers = tmp;
			}
			set<char> tmp2 = anwsers;
			anwsers.clear();
			set_intersection(tmp2.begin(), tmp2.end(), tmp.begin(), tmp.end(), inserter(anwsers, anwsers.begin()));
		}
	}

public:
	CustomCustoms() {
		file.open("day06_input.txt");
	}

	int part01() {
		string line;
		int count_yes = 0;
		file.clear();
		file.seekg(0, std::ios_base::beg);
		if (file) {
			while (std::getline(file, line)) {
				if (line.empty()) {
					count_yes += static_cast<int>(anwsers.size());
					anwsers.clear();
				}
				else {
					update(line);
				}
			}
		}
		count_yes += static_cast<int>(anwsers.size());
		return count_yes;
	}

	int part02() {
		string line;
		int count_yes = 0;
		vector<string> lines;
		file.clear();
		file.seekg(0, std::ios_base::beg);
		if (file) {
			while (std::getline(file, line)) {
				if (line.empty()) {
					update2(lines);
					count_yes += static_cast<int>(anwsers.size());
					anwsers.clear();
					lines.clear();
				}
				else {
					lines.emplace_back(line);
				}
			}
		}
		update2(lines);
		count_yes += static_cast<int>(anwsers.size());
		anwsers.clear();
		return count_yes;
	}

	~CustomCustoms() { file.close(); }
};


int main() {
	CustomCustoms custom_customs;
	cout << custom_customs.part01() << endl;
	cout << custom_customs.part02() << endl;
}
