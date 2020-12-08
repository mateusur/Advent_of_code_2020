#include <iostream>
#include <fstream>
#include <tuple>
#include <string>
#include <vector>
using namespace std;

class Code
{
	using Operation = tuple<string, int, bool>;
	vector<Operation> operations;

	size_t find_next_to_change(size_t current_position) const {
		string operation;
		size_t searched_position = -1;
		for (size_t i = current_position + 1; i < operations.size(); ++i) {
			operation = get<0>(operations[i]);
			if (operation == "nop" || operation == "jmp") {
				searched_position = i;
				break;
			}
		}
		return searched_position;
	}

	void set_false_for_operations() {
		for (auto& operation : operations) {
			get<2>(operation) = false;
		}
	}

public:
	Code() {
		ifstream file("day08_input.txt");
		string tmp_operation;
		int tmp_argumet;
		while (file) {
			file >> tmp_operation >> tmp_argumet;
			operations.emplace_back(make_tuple(tmp_operation, tmp_argumet, false));
		}
	}

	int part01() {
		size_t current_position = 0;
		int accumulator = 0;
		string operation;
		while (get<2>(operations[current_position]) == false) {
			operation = get<0>(operations[current_position]);
			get<2>(operations[current_position]) = true;
			if (operation == "acc") {
				accumulator += get<1>(operations[current_position]);
				current_position++;
			}
			else if (operation == "jmp") {
				current_position += get<1>(operations[current_position]);
			}
			else if (operation == "nop") {
				current_position++; // = get<1>(operations[current_position]);
			}
		}
		set_false_for_operations();
		return accumulator;
	}

	int part02() {
		size_t current_position = 0;
		size_t changed_position = 0;
		size_t last_position = operations.size() - 1;
		int accumulator = 0;
		bool found = false;
		vector<Operation> copy;
		while (found == false) {
			accumulator = 0;
			current_position = 0;
			copy.clear();
			copy = operations;
			changed_position = find_next_to_change(changed_position);
			string what_to_change = get<0>(copy[changed_position]);
			if (what_to_change == "nop") {
				get<0>(copy[changed_position]) = "jmp";
			}
			else {
				get<0>(copy[changed_position]) = "nop";
			}
			string operation;
			while (get<2>(copy[current_position]) == false) {
				operation = get<0>(copy[current_position]);
				get<2>(copy[current_position]) = true;
				if (operation == "acc") {
					accumulator += get<1>(copy[current_position]);
					current_position++;
				}
				else if (operation == "jmp") {
					current_position += get<1>(copy[current_position]);
				}
				else if (operation == "nop") {
					current_position++;
				}
				if (current_position == last_position) {
					found = true;
					break;
				}
			}
		}
		return accumulator;
	}
};

int main() {
	Code code;
	cout << code.part01() << endl;
	cout << code.part02() << endl;
	return 0;
}
