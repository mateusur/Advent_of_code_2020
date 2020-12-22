#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <sstream>
using namespace std;

class Combat
{
	queue<int> player1;
	queue<int> player2;
public:
	Combat() {
		ifstream file("day22_input.txt");
		stringstream ss;
		ss << file.rdbuf();
		string line;
		bool first_player = false;
		while (ss>>line) {
			if(isdigit(line[0])) {
				if(first_player) {
					player1.push(stoi(line));
				}
				else {
					player2.push(stoi(line));
				}
			}
			else {
				first_player = !first_player;
			}
		}
		file.close();
	}

	int part01() {
		int player1_card, player2_card;
		while (!player1.empty() && !player2.empty()) {
			player1_card = player1.front();
			player2_card = player2.front();
			if(player1_card > player2_card) {
				player1.emplace(player1_card);
				player1.emplace(player2_card);
			}
			else {
				player2.emplace(player2_card);
				player2.emplace(player1_card);
			}
			player1.pop();
			player2.pop();
		}
		queue<int> copies = player1.empty() ? player2 : player1;
		int multiplier =  static_cast<int>(copies.size());
		unsigned int sum = 0;
			while (!copies.empty())
			{
				sum += multiplier * copies.front();
				copies.pop();
				--multiplier;
			}
		
		return sum;
	}
};
int main() {

	Combat combat;
	combat.part01();
	return 0;
}