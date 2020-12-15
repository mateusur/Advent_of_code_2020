#include <iostream>
#include <map>
#include <unordered_set>
using namespace std;

class Game
{
	map<int, pair<int, int>> numbers;
	int turn;
	int last_spoken;

	int find_number(const int& number_to_find) {
		pair<int, int> positions{-1, -1};
		int anwser = 0;
		auto itr = numbers.find(number_to_find);
		if (itr != numbers.end()) {
			if (itr->second.first == -1) {
				anwser = 0;
			}
			else {
				anwser = itr->second.second - itr->second.first;
			}
			itr = numbers.find(anwser);
			if (itr != numbers.end()) {
				itr->second.first = itr->second.second;
				itr->second.second = ++turn;
			}
			else {
				numbers.insert({anwser, make_pair(-1, ++turn)});
			}
		}
		last_spoken = anwser;
		return anwser;
	}

	void reset() {
		turn = 0;
		numbers.clear();
		numbers.insert({11, make_pair(-1, ++turn)});
		numbers.insert({0, make_pair(-1, ++turn)});
		numbers.insert({1, make_pair(-1, ++turn)});
		numbers.insert({10, make_pair(-1, ++turn)});
		numbers.insert({5, make_pair(-1, ++turn)});
		numbers.insert({19, make_pair(-1, ++turn)});
	}

public:
	Game() : turn(0), last_spoken(0) {
		reset();
	}

	int part(const int& number = 2020) {
		auto itr = numbers.end()--;
		last_spoken = (--numbers.end())->first;
		do {
			find_number(last_spoken);
		} while (turn < number);
		reset();
		return last_spoken;
	}
};

int main() {
	Game game;
	cout << "Part 1: " << game.part() << endl;
	cout << "Part 2: " << game.part(30000000) << endl;
	return 0;
}
