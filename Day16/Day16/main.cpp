#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
using namespace std;

class Tickets
{
	using range = tuple<int, int, int, int>;
	unordered_map<string, range> fields_;
	vector<vector<int>> nearby_tickets_;
	vector<int> your_ticekt_;

	bool is_valid_field(const int& number) const {
		bool anwser = false;
		for (const auto& field : fields_) {
			if (number >= get<0>(field.second) && number <= get<1>(field.second) || number >= get<2>(field.second) &&
				number <= get<3>(field.second)) {
				anwser = true;
				break;
			}
		}
		return anwser;
	}

public:
	Tickets() {
		ifstream file("day16_input.txt");
		string first, second, tmp;
		int low_left, hight_left, low_right, high_right;
		char chr;
		for (int i = 0; i < 10; ++i) {
			file >> first >> second >> low_left >> chr >> hight_left >> tmp >> low_right >> chr >> high_right;
			fields_.insert(make_pair(first + " " + second, make_tuple(low_left, hight_left, low_right, high_right)));
		}
		for (int i = 0; i < 10; ++i) {
			file >> first >> low_left >> chr >> hight_left >> tmp >> low_right >> chr >> high_right;
			fields_.insert(make_pair(first, make_tuple(low_left, hight_left, low_right, high_right)));
		}
		getline(file, first);
		getline(file, first);
		getline(file, first);
		getline(file, first);
		first = regex_replace(first, regex(","), " ");
		stringstream ss(first);

		while (ss >> second) {
			your_ticekt_.emplace_back(stoi(second));
		}
		getline(file, first);
		getline(file, first);
		while (file) {
			getline(file, first);
			first = regex_replace(first, regex(","), " ");
			stringstream ss(first);
			vector<int> tmp_vec;
			while (ss >> second) {
				tmp_vec.emplace_back(stoi(second));
			}
			if (!tmp_vec.empty()) {
				nearby_tickets_.emplace_back(tmp_vec);
			}
		}
	}

	int part01() const {
		int invalid_sum = 0;
		for (const auto& vec : nearby_tickets_) {
			for (const int& number : vec) {
				if (!is_valid_field(number)) {
					invalid_sum += number;
				}
			}
		}
		return invalid_sum;
	}

	unsigned long long part02() {
		vector<size_t> positions_in_your_ticket;
		unsigned long long sum = 1;
		for (int i = 0; i < nearby_tickets_.size(); ++i) {
			for (int j = 0; j < nearby_tickets_.at(i).size(); ++j) {
				if (!is_valid_field(nearby_tickets_[i][j])) {
					nearby_tickets_.erase(nearby_tickets_.begin() + i);
					--i;
					break;
				}
			}
		}
		unordered_map<string, size_t> anwser;
		auto field = fields_.begin();
		while (!fields_.empty()) {
			vector<size_t> possible_combinations;
			size_t row_size = nearby_tickets_.size();
			size_t column_size = nearby_tickets_[0].size();
			size_t column = 0;
			for (; column < column_size; ++column) {
				for (size_t row = 0; row < row_size; ++row) {
					int number = nearby_tickets_[row][column];
					if (number >= get<0>(field->second) && number <= get<1>(field->second) || number >= get<2
					>(field->second) && number <= get<3>(field->second)) {
						if (row == row_size - 1) {
							possible_combinations.emplace_back(column);
						}
					}
					else {
						break;
					}
				}
			}
			if (possible_combinations.size() == 1) {

				column = possible_combinations[0];
				string str2("departure");
				if (field->first.find(str2) != string::npos) {
					positions_in_your_ticket.emplace_back(column);
				}
				anwser.insert(make_pair(field->first, column));
				fields_.erase(fields_.find(field->first));
				std::for_each(nearby_tickets_.begin(), nearby_tickets_.end(), [&column](std::vector<int>& row)
				{
					row[column] = -1;
				});


				field = fields_.begin();
			}
			else {
				++field;
			}
		}
		for (auto pos : positions_in_your_ticket) {
			sum *= your_ticekt_[pos];
		}
		return sum;
	}
};

int main() {
	Tickets tickets;
	cout << tickets.part01() << endl;
	cout << tickets.part02() << endl;
	return 0;
}
