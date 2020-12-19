#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
using namespace std;

class Operations
{
	vector<string> lines_;

	unsigned long long calculate(const string& str, const bool& erase = true) {
		string cp = str;
		if (erase) {
			cp.erase(cp.begin());
			cp.erase(cp.end() - 1);
		}
		string tmp;
		stringstream ss(cp);
		unsigned long long num1 = 0, num2 = 0;
		char op;
		while (ss >> tmp) {
			if (isdigit(tmp[0])) {
				if (num1 == 0) {
					num1 = stoll(tmp);
				}
				else {
					num2 = stoll(tmp);
					switch (op) {
					case '+':
						num1 += num2;
						break;
					case '-':
						num1 -= num2;
						break;
					case '*':
						num1 *= num2;
						break;
					}
				}
			}
			else {
				op = tmp[0];
			}
		}
		return num1;
	}

	unsigned long long calculate2(const string& str, const bool& erase = true) {
		vector<string> operations;
		string cp = str;
		if (erase) {
			cp.erase(cp.begin());
			cp.erase(cp.end() - 1);
		}
		string tmp;
		stringstream ss(cp);
		unsigned long long num1 = 0, num2 = 0;
		char op;
		while (ss >> tmp) {
			operations.emplace_back(tmp);
		}
		auto itr = find(operations.begin(), operations.end(), "+");
		while (itr != operations.end()) {
			*(itr - 1) = to_string(stoll(*(itr - 1)) + stoll(*(itr + 1)));
			operations.erase(itr, itr + 2);
			itr = find(operations.begin(), operations.end(), "+");
		}
		itr = find(operations.begin(), operations.end(), "*");
		while (itr != operations.end()) {
			*(itr - 1) = to_string(stoll(*(itr - 1)) * stoll(*(itr + 1)));
			operations.erase(itr, itr + 2);
			itr = find(operations.begin(), operations.end(), "*");
		}
		num1 = stoll(operations.at(0));

		return num1;
	}

public:
	Operations() {
		ifstream file("day18_input.txt");
		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				lines_.emplace_back(line);
			}
		}
		file.close();
	}

	unsigned long long part01() {
		unsigned long long anwser_sum = 0;
		regex r(R"(\(\d+(\s.\s\d+)+\))");
		for (string& line : lines_) {
			auto words_begin = sregex_iterator(line.begin(), line.end(), r);
			auto words_end = sregex_iterator();
			while (words_begin != words_end) {
				smatch m = *words_begin;
				string found = m[0].str();
				unsigned long long sum = calculate(m[0].str());
				line.replace(line.find(found), found.size(), to_string(sum));
				words_begin = sregex_iterator(line.begin(), line.end(), r);
			}
			anwser_sum += calculate(line, false);
		}
		return anwser_sum;
	}

	unsigned long long part02() {
		unsigned long long anwser_sum = 0;
		regex r(R"(\(\d+(\s.\s\d+)+\))");
		for (string& line : lines_) {
			auto words_begin = sregex_iterator(line.begin(), line.end(), r);
			auto words_end = sregex_iterator();
			while (words_begin != words_end) {
				smatch m = *words_begin;
				string found = m[0].str();
				unsigned long long sum = calculate2(m[0].str());
				line.replace(line.find(found), found.size(), to_string(sum));
				words_begin = sregex_iterator(line.begin(), line.end(), r);
			}
			anwser_sum += calculate2(line, false);
		}
		return anwser_sum;
	}
};


int main() {

	Operations operations;
	cout << operations.part01() << endl;
	Operations operations2;
	cout << operations2.part02() << endl;
	return 0;
}
