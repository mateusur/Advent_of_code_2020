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
					//num2 = 0;
				}
			}
			else {
				op = tmp[0];
			}
		}
		return num1;
	}
public:
	Operations() {
		ifstream file("day18_input.txt");
		if(file.is_open()) {
			string line;
			while (getline(file,line)) {
				lines_.emplace_back(line);
			}
		}
		file.close();
	}

	unsigned long long part01() {
		unsigned long long anwser_sum = 0;
		regex r(R"(\(\d+(\s.\s\d+)+\))");
		for(string& line : lines_) {
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
};


int calculate(const string& str, const bool& erase = true) {
	string cp = str;
	if (erase) {
		cp.erase(cp.begin());
		cp.erase(cp.end() - 1);
	}
	string tmp;
	stringstream ss(cp);
	int num1 = 0, num2 = 0;
	char op;
	while (ss >> tmp) {
		if (isdigit(tmp[0])) {
			if (num1 == 0) {
				num1 = stoi(tmp);
			}
			else {
				num2 = stoi(tmp);
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
				//num2 = 0;
			}
		}
		else {
			op = tmp[0];
		}
	}
	return num1;
}
int main() {
	//std::regex r(R"(\(\d+(\s.\s\d+)+\))"); 
	//std::string s = "9 + 5 * 9 * ((2 + 3 + 3 + 6 + 5) + 8) + 2 + (3 + (9 * 9) + 2 * (5 + 8 + 8 + 7) * (8 + 7 + 5 + 5 * 7 * 7) * (9 + 5 * 8 * 5 * 8 + 2))";
	//auto words_begin = std::sregex_iterator(s.begin(), s.end(), r);
	//auto words_end = std::sregex_iterator();
	//while(words_begin != words_end) {
	//	smatch m = *words_begin;
	//	string found = m[0].str();
	//	int sum = calculate(m[0].str());
	//	s.replace(s.find(found), found.size(), to_string(sum));
	//	words_begin = std::sregex_iterator(s.begin(), s.end(), r);
	//}
	//cout << calculate(s,false) << endl;
	Operations operations;
	cout << operations.part01() << endl;
	return 0;
}