#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>
using namespace std;

class XMAS
{
	vector<int> code;
public:
	XMAS() {
		ifstream file("day09_input.txt");
		int tmp_number;
		while (file) {
			file >> tmp_number;
			code.emplace_back(tmp_number);
		}
	}

	int part01() const {
		bool found = true;
		const int preambule_length = 25;
		size_t position = preambule_length+1;
		int sum_to_find;
		bool breakout = false;
		while (found) {
			sum_to_find = code.at(position);
			for (size_t i = position - preambule_length - 1; i < position; ++i) {
				for (size_t j = position - preambule_length; j < position; ++j) {
					int sum2 = code.at(i) + code.at(j);
					if (sum2 == sum_to_find) {
						breakout = true;
						break;
					}
				}
				if (breakout == true) {
					breakout = false;
					break;
				}
				else if (breakout == false && i == position - 1) {
					found = false;
					break;
				}
			}
			++position;
		}
		return sum_to_find;
	}

	int part02() const{
		int invalid_sum = part01();
		bool found = false;
		size_t starting_position = 0;
		size_t inside_loop_position = starting_position+1;
		vector<int> contigious_numbers;
		int anwser = 0;
		while (found == false) {
			contigious_numbers.clear();
			contigious_numbers.emplace_back(code.at(starting_position));
			while(accumulate(contigious_numbers.begin(),contigious_numbers.end(),0) <= invalid_sum) {
				contigious_numbers.emplace_back(code.at(inside_loop_position));
				if(accumulate(contigious_numbers.begin(), contigious_numbers.end(), 0) == invalid_sum) {
					found = true;
					anwser = *min_element(contigious_numbers.begin(), contigious_numbers.end()) + *max_element(contigious_numbers.begin(), contigious_numbers.end());
					break;
				}
				++inside_loop_position;
			}
			++starting_position;
			inside_loop_position = starting_position + 1;
		}
		return anwser;
	}
};

int main() {
	XMAS xmas;
	cout << xmas.part01() << endl;
	cout << xmas.part02() << endl;
	return 0;
}
