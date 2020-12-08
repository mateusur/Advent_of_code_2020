#include <string>
#include <iosfwd>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <tuple>
using namespace std;

class Bags
{
	using bag = tuple<int, string, string>;
	ifstream file;
	const array<string, 2> color = {"shiny", "gold"};
	vector<vector<string>> mapped_words;
	set<string> final_colors;

	void get_color_positions(const string& adjective, const string& color) {
		vector<pair<size_t, size_t>> anwser;
		for (size_t row = 0; row < mapped_words.size(); ++row) {
			for (size_t column = 0; column < mapped_words[row].size() - 1; ++column) {
				if (mapped_words[row][column] == adjective && mapped_words[row][column + 1] == color) {
					anwser.emplace_back(make_pair(row, column));
				}
			}
		}
		get_previous_colors(anwser);
	}

	void get_previous_colors(const vector<pair<size_t, size_t>>& colors_positions) {
		for (const auto& position : colors_positions) {
			size_t tmp_pos = 0;
			string color = mapped_words[position.first][tmp_pos] + ' ' + mapped_words[position.first][tmp_pos + 1];
			if (final_colors.find(color) == final_colors.end()) {
				final_colors.insert(color);
				get_color_positions(mapped_words[position.first][tmp_pos], mapped_words[position.first][tmp_pos + 1]);
			}

		}
	}

	int get_first_color(const string& adjective, const string& color) {
		pair<size_t, size_t> pos;
		for (size_t row = 0; row < mapped_words.size(); ++row) {
			if (mapped_words[row][0] == adjective && mapped_words[row][1] == color) {
				pos = {row, 0};
				break;
			}
		}
		int sum = get_next_colors(pos);
		return sum;
	}

	int get_next_colors(const pair<size_t, size_t> position) {
		size_t length = mapped_words[position.first].size();
		size_t row = position.first;
		size_t column = position.second;
		vector<bag> bags;
		int sum = 0;
		if (length >= 8) {
			while (column + 4 < length) {
				column += 4;
				bags.emplace_back(make_tuple(stoi(mapped_words[row][column]), mapped_words[row][column + 1],
				                             mapped_words[row][column + 2]));
			}
			for (const auto& single_bag : bags) {
				sum += get<0>(single_bag) + get<0>(single_bag) *
					get_first_color(get<1>(single_bag), get<2>(single_bag));
			}
		}
		return !bags.empty() ? sum : 0;
	}

public:
	Bags() {
		file.open("day07_input.txt");
		string line;
		stringstream words;
		size_t row = 0;
		if (file) {
			while (std::getline(file, line)) {
				stringstream words(line);
				string word;
				vector<string> line_of_words;
				while (words >> word) {
					line_of_words.emplace_back(word);
				}
				mapped_words.emplace_back(line_of_words);
			}
		}
	}

	int part01() {
		get_color_positions(color[0], color[1]);
		return static_cast<int>(final_colors.size() - 1); //-1 because we remove "shiny gold"
	}

	int part02() {
		return get_first_color(color[0], color[1]);
	}
};


int main() {
	Bags bags;
	cout << bags.part01() << endl;
	cout << bags.part02() << endl;
	return 0;
}
