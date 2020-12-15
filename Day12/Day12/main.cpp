#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class Navigation
{
	vector<pair<char, int>> directions_;
	int rotation_ = 0; //east
	pair<int, int> ship_coordinates; //first for east, west, second for south,north
	pair<int, int> waypoint_coordinates;

	enum class Directions { east, south, west, north };

	void rotate(const size_t& row) {
		int angle = directions_.at(row).second;
		switch (directions_.at(row).first) {
		case 'R':
			rotation_ = (rotation_ + angle) % 360;
			break;
		case 'L':
			rotation_ = (rotation_ - angle) < 0 ? 360 + (rotation_ - angle) : (rotation_ - angle) % 360;
			break;
		}
	}

	void move(const size_t& row) {
		int distance = directions_.at(row).second;
		switch (directions_.at(row).first) {
		case 'E':
			ship_coordinates.first += distance;
			break;
		case 'W':
			ship_coordinates.first -= distance;
			break;
		case 'S':
			ship_coordinates.second += distance;
			break;
		case 'N':
			ship_coordinates.second -= distance;
			break;
		}
	}

public:
	Navigation() : waypoint_coordinates({10, -1}) {
		ifstream file("day12_input.txt");
		string tmp;
		char c;
		int i;
		while (file >> tmp) {
			c = tmp.at(0);
			tmp.erase(tmp.begin() + 0);
			i = stoi(tmp);
			directions_.emplace_back(make_pair(c, i));
		}
		file.close();

	}

	int part01() {
		char chr;
		for (size_t i = 0; i < directions_.size(); ++i) {
			chr = directions_.at(i).first;
			if (chr == 'F') {
				int distance = directions_.at(i).second;
				if (rotation_ == 0) {
					ship_coordinates.first += distance;
				}
				else if (rotation_ == 90) {
					ship_coordinates.second += distance;
				}
				else if (rotation_ == 180) {
					ship_coordinates.first -= distance;
				}
				else {
					ship_coordinates.second -= distance;
				}
			}
			else if (chr == 'R' || chr == 'L') {
				rotate(i);
			}
			else {
				move(i);
			}
		}
		return abs(ship_coordinates.first) + abs(ship_coordinates.second);
	}

	int part02() {
		char chr;
		for (size_t i = 0; i < directions_.size(); ++i) {
			chr = directions_.at(i).first;
			if (chr == 'F') {
				int east_waypoint = waypoint_coordinates.first * directions_.at(i).second;
				int south_waypoint = waypoint_coordinates.second * directions_.at(i).second;
				ship_coordinates.first += east_waypoint;
				ship_coordinates.second += south_waypoint;
			}
			else if (chr == 'R' || chr == 'L') {
				int angle = directions_.at(i).second;
				if (chr == 'L') {
					angle = 360 - angle;
				}
				for (int i = 0; i < angle; i += 90) {
					pair<int, int> tmp = waypoint_coordinates;
					waypoint_coordinates.first = -1 * tmp.second;
					waypoint_coordinates.second = tmp.first;
				}
			}
			else {
				switch (chr) {
				case 'E':
					waypoint_coordinates.first += directions_.at(i).second;
					break;
				case 'W':
					waypoint_coordinates.first -= directions_.at(i).second;
					break;
				case 'S':
					waypoint_coordinates.second += directions_.at(i).second;
					break;
				case 'N':
					waypoint_coordinates.second -= directions_.at(i).second;
					break;
				}
			}
		}
		return abs(ship_coordinates.first) + abs(ship_coordinates.second);
	}
};

int main() {
	Navigation navigation;
	cout << navigation.part01() << endl;
	Navigation navigation2;
	cout << navigation2.part02() << endl;
	return 0;
}
