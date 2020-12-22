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

	int calculate_sum() {
		queue<int> copies = player1.empty() ? player2 : player1;
		int multiplier = static_cast<int>(copies.size());
		unsigned int sum = 0;
		while (!copies.empty())
		{
			sum += multiplier * copies.front();
			copies.pop();
			--multiplier;
		}
		return sum;
	}

	int sub_game(const queue<int>& player1,const queue<int>& player2) const {
		int player1_card = player1.front(), player2_card = player2.front();
		queue<int> copy_player1;
		queue<int> copy_player2;
		queue<int> tmp = player1;
		for(int i = 0; i < player1_card; ++i) {
			tmp.pop();
			copy_player1.emplace(tmp.front());
		}
		tmp = player2;
		for (int i = 0; i < player2_card; ++i) {
			tmp.pop();
			copy_player2.emplace(tmp.front());
		}
		vector<queue<int>> queues_player1;
		vector<queue<int>> queues_player2;
		int winner = 0;
		while (!copy_player1.empty() && !copy_player2.empty()) {
			if(find(queues_player1.begin(),queues_player1.end(),copy_player1) != queues_player1.end() || find(queues_player2.begin(), queues_player2.end(), copy_player2) != queues_player2.end()) {
				winner = 1;
				break;
			}
			queues_player1.emplace_back(copy_player1);
			queues_player2.emplace_back(copy_player2);
			player1_card = copy_player1.front();
			player2_card = copy_player2.front();
			if ( copy_player1.size() > player1_card  &&  copy_player2.size() > player2_card) {
				 winner = sub_game(copy_player1, copy_player2);
				if(winner == 1) {
					copy_player1.emplace(player1_card);
					copy_player1.emplace(player2_card);
				}
				else {
					copy_player2.emplace(player2_card);
					copy_player2.emplace(player1_card);
				}
			}
			else if (player1_card > player2_card) {
				copy_player1.emplace(player1_card);
				copy_player1.emplace(player2_card);
			}
			else {
				copy_player2.emplace(player2_card);
				copy_player2.emplace(player1_card);
			}
			copy_player1.pop();
			copy_player2.pop();
		}
		return copy_player1.empty() ? 2 : 1; //if player1 is empty player2 won
	}
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
		return calculate_sum();;
	}

	int part02() {
		int player1_card, player2_card;
		while (!player1.empty() && !player2.empty()) {
			player1_card = player1.front();
			player2_card = player2.front();
			if( player1.size() > player1_card  &&  player2.size() > player2_card ) {
				int winner = sub_game(player1, player2);
				if (winner == 1) {
					player1.emplace(player1_card);
					player1.emplace(player2_card);
				}
				else {
					player2.emplace(player2_card);
					player2.emplace(player1_card);
				}
			}
			else if (player1_card > player2_card) {
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
		return calculate_sum();
	}
};
int main() {

	Combat combat;
	cout << combat.part01() << endl;
	Combat combat2;
	cout << combat2.part02() << endl;
	return 0;
}