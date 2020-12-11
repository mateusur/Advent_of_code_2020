#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Seats
{
	vector<string> seats_lines;
	size_t columns, rows;

	int count_seats() const {
		int sum = 0;
		for (size_t row = 0; row < rows; ++row) {
			for (size_t column = 0; column < columns; ++column) {
				if (seats_lines.at(row).at(column) == '#') {
					++sum;
				}
			}
		}
		return sum;
	}

	/*int take_seats(const size_t& row, const size_t& column) const {
		int sum = 0;
		sum += count_horizontal(row, column);
		sum += count_vertical(row, column);
		sum += count_diagonal(row, column);
		return sum;
	}*/

	int count_horizontal(const size_t& row, const size_t& column) const {
		int sum = 0;
		if (column == 0) {
			if (seats_lines.at(row).at(column + 1) == '#') {
				++sum;
			}
		}
		else if (column == columns - 1) {
			if (seats_lines.at(row).at(column - 1) == '#') {
				++sum;
			}
		}
		else {
			if (seats_lines.at(row).at(column + 1) == '#') {
				++sum;
			}
			if (seats_lines.at(row).at(column - 1) == '#') {
				++sum;
			}
		}
		return sum;
	}

	int count_vertical(const size_t& row, const size_t& column) const {
		int sum = 0;
		if (row == 0) {
			if (seats_lines.at(row + 1).at(column) == '#') {
				++sum;
			}
		}
		else if (row == rows - 1) {
			if (seats_lines.at(row - 1).at(column) == '#') {
				++sum;
			}
		}
		else {
			if (seats_lines.at(row + 1).at(column) == '#') {
				++sum;
			}
			if (seats_lines.at(row - 1).at(column) == '#') {
				++sum;
			}
		}
		return sum;
	}

	int count_diagonal(const size_t& row, const size_t& column) const {
		int sum = 0;
		if (row == 0 && column == 0) {
			if (seats_lines.at(row + 1).at(column + 1) == '#') {
				++sum;
			}
		}
		else if (row == 0 && column == columns - 1) {
			if (seats_lines.at(row + 1).at(column - 1) == '#') {
				++sum;
			}
		}
		else if (row == rows - 1 && column == 0) {
			if (seats_lines.at(row - 1).at(column + 1) == '#') {
				++sum;
			}
		}
		else if (row == rows - 1 && column == columns - 1) {
			if (seats_lines.at(row - 1).at(column - 1) == '#') {
				++sum;
			}
		}
		else if (row == 0) {
			if (seats_lines.at(row + 1).at(column - 1) == '#') {
				++sum;
			}
			if (seats_lines.at(row + 1).at(column + 1) == '#') {
				++sum;
			}
		}
		else if (row == rows - 1) {
			if (seats_lines.at(row - 1).at(column - 1) == '#') {
				++sum;
			}
			if (seats_lines.at(row - 1).at(column + 1) == '#') {
				++sum;
			}
		}
		else if (column == 0) {
			if (seats_lines.at(row - 1).at(column + 1) == '#') {
				++sum;
			}
			if (seats_lines.at(row + 1).at(column + 1) == '#') {
				++sum;
			}
		}
		else if (column == columns - 1) {
			if (seats_lines.at(row - 1).at(column - 1) == '#') {
				++sum;
			}
			if (seats_lines.at(row + 1).at(column - 1) == '#') {
				++sum;
			}
		}
		else {
			if (seats_lines.at(row - 1).at(column - 1) == '#') {
				++sum;
			}
			if (seats_lines.at(row - 1).at(column + 1) == '#') {
				++sum;
			}
			if (seats_lines.at(row + 1).at(column - 1) == '#') {
				++sum;
			}
			if (seats_lines.at(row + 1).at(column + 1) == '#') {
				++sum;
			}
		}
		return sum;
	}

	int count_seats(const size_t& row, const size_t& column) const {
		int sum = 0;
		sum += count_horizontal(row, column);
		sum += count_vertical(row, column);
		sum += count_diagonal(row, column);
		return sum;
	}

	int count_horizontal2(const size_t& row, const size_t& column) const {
		int sum = 0;
		if (column == 0) {
			for (size_t i = column + 1; i < columns; ++i) {
				if (seats_lines.at(row).at(i) == '#') {
					++sum;
					break;
				}
				else if (seats_lines.at(row).at(i) == 'L') {
					break;
				}
			}
		}
		else if (column == columns - 1) {
			for (size_t i = column; i >= 1; --i) {
				if (seats_lines.at(row).at(i - 1) == '#') {
					++sum;
					break;
				}
				else if (seats_lines.at(row).at(i - 1) == 'L') {
					break;
				}
			}
		}
		else {
			for (size_t i = column + 1; i < columns; ++i) {
				if (seats_lines.at(row).at(i) == '#') {
					++sum;
					break;
				}
				else if (seats_lines.at(row).at(i) == 'L') {
					break;
				}
			}
			for (size_t i = column; i >= 1; --i) {
				if (seats_lines.at(row).at(i - 1) == '#') {
					++sum;
					break;
				}
				else if (seats_lines.at(row).at(i - 1) == 'L') {
					break;
				}
			}
		}
		return sum;
	}

	int count_vertical2(const size_t& row, const size_t& column) const {
		int sum = 0;
		if (row == 0) {
			for (size_t i = row + 1; i < rows; ++i) {
				if (seats_lines.at(i).at(column) == '#') {
					++sum;
					break;
				}
				else if (seats_lines.at(i).at(column) == 'L') {
					break;
				}
			}
		}
		else if (row == rows - 1) {
			for (size_t i = row; i >= 1; --i) {
				if (seats_lines.at(i - 1).at(column) == '#') {
					++sum;
					break;
				}
				else if (seats_lines.at(i - 1).at(column) == 'L') {
					break;
				}
			}
		}
		else {
			for (size_t i = row + 1; i < rows; ++i) {
				if (seats_lines.at(i).at(column) == '#') {
					++sum;
					break;
				}
				else if (seats_lines.at(i).at(column) == 'L') {
					break;
				}
			}
			for (size_t i = row; i >= 1; --i) {
				if (seats_lines.at(i - 1).at(column) == '#') {
					++sum;
					break;
				}
				else if (seats_lines.at(i - 1).at(column) == 'L') {
					break;
				}
			}
		}
		return sum;
	}

	int count_diagonal2(const size_t& row, const size_t& column) const {
		int sum = 0;

		for (size_t col = column , r = row ; col >= 1 && r >= 1; --col, --r) {
			if (seats_lines.at(r-1).at(col-1) == '#') {
				++sum;
				break;
			}
			else if (seats_lines.at(r-1).at(col-1) == 'L') {
				break;
			}
		}
		for (size_t col = column + 1, r = row ; col < columns && r >= 1; ++col, --r) {
			if (seats_lines.at(r-1).at(col) == '#') {
				++sum;
				break;
			}
			else if (seats_lines.at(r-1).at(col) == 'L') {
				break;
			}
		}
		for (size_t col = column , r = row + 1; col >= 1 && r < rows; --col, ++r) {
			if (seats_lines.at(r).at(col-1) == '#') {
				++sum;
				break;
			}
			else if (seats_lines.at(r).at(col-1) == 'L') {
				break;
			}
		}
		for (size_t col = column + 1, r = row + 1; col < columns && r < rows; ++col, ++r) {
			if (seats_lines.at(r).at(col) == '#') {
				++sum;
				break;
			}
			else if (seats_lines.at(r).at(col) == 'L') {
				break;
			}
		}


		return sum;
	}

	int count_seats2(const size_t& row, const size_t& column) const {
		int sum = 0;
		sum += count_horizontal2(row, column);
		sum += count_vertical2(row, column);
		sum += count_diagonal2(row, column);
		return sum;
	}

public:
	Seats() {
		ifstream file("day11_input.txt");
		string line;
		if (file) {
			while (std::getline(file, line)) {
				seats_lines.emplace_back(line);
			}
		}
		columns = seats_lines[0].size();
		rows = seats_lines.size();
		file.close();
	}

	int part01() {
		int adjacents_seats = 0;
		vector<string> copies = seats_lines;
		int changed_seats = 0;
		do {
			changed_seats = 0;
			seats_lines.clear();
			copy(copies.begin(), copies.end(), back_inserter(seats_lines));

			for (size_t row = 0; row < rows; ++row) {
				adjacents_seats = 0;
				for (size_t column = 0; column < columns; ++column) {
					if (seats_lines.at(row).at(column) == 'L') {
						adjacents_seats = count_seats(row, column);
						if (adjacents_seats == 0) {
							copies.at(row).at(column) = '#';
							++changed_seats;
						}
					}

				}
			}
			seats_lines.clear();
			copy(copies.begin(), copies.end(), back_inserter(seats_lines));
			for (size_t row = 0; row < rows; ++row) {
				adjacents_seats = 0;
				for (size_t column = 0; column < columns; ++column) {
					if (seats_lines.at(row).at(column) == '#') {
						adjacents_seats = count_seats(row, column);
						if (adjacents_seats >= 4) {
							copies.at(row).at(column) = 'L';
							++changed_seats;
						}
					}

				}
			}
		} while (changed_seats != 0);
		return count_seats();
	}

	int part02() {
		int adjacents_seats = 0;
		vector<string> copies = seats_lines;
		int changed_seats = 0;
		do {
			changed_seats = 0;
			seats_lines.clear();
			copy(copies.begin(), copies.end(), back_inserter(seats_lines));
			for (size_t row = 0; row < rows; ++row) {
				adjacents_seats = 0;
				for (size_t column = 0; column < columns; ++column) {
					if (seats_lines.at(row).at(column) == 'L') {
						adjacents_seats = count_seats2(row, column);
						if (adjacents_seats == 0) {
							copies.at(row).at(column) = '#';
							++changed_seats;
						}
					}
				}
			}
			seats_lines.clear();
			copy(copies.begin(), copies.end(), back_inserter(seats_lines));
			for (size_t row = 0; row < rows; ++row) {
				adjacents_seats = 0;
				for (size_t column = 0; column < columns; ++column) {
					if (seats_lines.at(row).at(column) == '#') {
						adjacents_seats = count_seats2(row, column);
						if (adjacents_seats >= 5) {
							copies.at(row).at(column) = 'L';
							++changed_seats;
						}
					}
				}
			}
		} while (changed_seats != 0);
		return count_seats();
	}
};

int main() {
	Seats seats1; //part01 and part02 need to run separately
	cout << seats1.part01() << endl;

	Seats seats2;
	cout << seats2.part02() << endl;
}
