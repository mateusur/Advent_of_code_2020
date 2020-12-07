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

class Bags
{
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
			//vector<pair<size_t, size_t>> positions_diffrent_colors;
			size_t tmp_pos = 0;
			string color = mapped_words[position.first][tmp_pos] + ' ' + mapped_words[position.first][tmp_pos + 1];
			if (final_colors.find(color) == final_colors.end()) {
				final_colors.insert(color);
				get_color_positions(mapped_words[position.first][tmp_pos], mapped_words[position.first][tmp_pos + 1]);
			}

		}
	}

	void get_all_bags_for_that_color(const string& adjective, const string& color) {
		
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
				//size_t column = 0;
				//bool shinny = false;
				while (words >> word) {
					line_of_words.emplace_back(word);
					//if (word == color[0]) {
					//	shinny = true;
					//}
					//else if (word == color[1] && shinny) {
					//	if (column != 1) {
					//		positions_shiny_gold.emplace_back(make_pair(row, column - 1));
					//	}
					//	shinny = false;
					//}
					//column++;
				}
				mapped_words.emplace_back(line_of_words);
				//row++;
			}
		}
	}

	int part01() {
		get_color_positions(color[0], color[1]);
		return final_colors.size() - 1; //-1 because we remove "shiny gold"
	}
	int part02() {
		
	}
};


int main() {
	Bags bags;
	cout <<  bags.part01();
	return 0;
}


/*pair<size_t,size_t> get_color(pair<size_t,size_t> color) {
	if(color.second==5) {
		string color_name = mapped_words[color.first][color.second] + ' ' + mapped_words[color.first][color.second + 1];
		if(final_colors.find(color_name) == final_colors.end()) {
			final_colors.insert(color_name);
		}
	}
	return { 0,0 };
}*/

//void get_previous_colors(const vector<pair<size_t, size_t>>& colors_positions) {
//	for (const auto& position : colors_positions) {
//		vector<pair<size_t, size_t>> positions_diffrent_colors;
//		size_t tmp_pos = position.second;
//		while (tmp_pos > 5) {
//			tmp_pos -= 4;
//			positions_diffrent_colors.emplace_back(make_pair(position.first, tmp_pos));
//
//			string color = mapped_words[position.first][tmp_pos] + ' ' + mapped_words[position.first][tmp_pos + 1];
//			if (final_colors.find(color) == final_colors.end()) {
//				final_colors.insert(color);
//				get_color_positions(mapped_words[position.first][tmp_pos], mapped_words[position.first][tmp_pos + 1]);
//			}
//		}
//		if (tmp_pos == 5) {
//			tmp_pos -= 5;
//			positions_diffrent_colors.emplace_back(make_pair(position.first, 0));
//			string color = mapped_words[position.first][tmp_pos] + ' ' + mapped_words[position.first][tmp_pos + 1];
//			if (final_colors.find(color) == final_colors.end()) {
//				final_colors.insert(color);
//				get_color_positions(mapped_words[position.first][tmp_pos], mapped_words[position.first][tmp_pos + 1]);
//			}
//		}
//		/*cout << mapped_words[position.first][position.second] << ' ' << mapped_words[position.first][position.second + 1] << " position: " << position.second << " size " << mapped_words[position.first].size() << endl;;
//		string color = mapped_words[position.first][position.second] + ' ' + mapped_words[position.first][position.second + 1];
//		if (final_colors.find(color) == final_colors.end()) {
//			final_colors.insert(color);
//		}*/
//	}
//}
