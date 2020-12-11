#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

using namespace std;
#include <algorithm>

template <typename Iterator>
bool next_combination(const Iterator first, Iterator k, const Iterator last)
{
	/* Credits: Mark Nelson http://marknelson.us */
	if ((first == last) || (first == k) || (last == k))
		return false;
	Iterator i1 = first;
	Iterator i2 = last;
	++i1;
	if (last == i1)
		return false;
	i1 = last;
	--i1;
	i1 = k;
	--i2;
	while (first != i1)
	{
		if (*--i1 < *i2)
		{
			Iterator j = k;
			while (!(*i1 < *j)) ++j;
			std::iter_swap(i1, j);
			++i1;
			++j;
			i2 = k;
			std::rotate(i1, j, last);
			while (last != j)
			{
				++j;
				++i2;
			}
			std::rotate(k, i2, last);
			return true;
		}
	}
	std::rotate(first, k, last);
	return false;
}

class Jolts
{
	using Matrix = vector<vector<int>>;
	set<int> jolts_set;
	set<size_t> a;

	bool is_legit(const vector<int>& orgianl) {
		int previous = orgianl.at(0);
		int diffrence = 0;
		bool anwser = true;
		for (size_t i = 1; i < orgianl.size(); ++i) {
			diffrence = orgianl.at(i) - previous;
			if(diffrence>3) {
				anwser = false;
				break;
			}
			else {
				previous = orgianl.at(i);
			}
		}
		return anwser;
	}
public:
	Jolts() {
		ifstream file("day10_input.txt");
		int tmp_number;
		jolts_set.insert(0);
		while (file) {
			file >> tmp_number;
			jolts_set.insert(tmp_number);
		}
		set<int>::const_iterator itr = jolts_set.end();
		--itr;
		jolts_set.insert((*itr) + 3);
	}

	int part01() {
		set<int>::iterator i = jolts_set.begin();
		int previous = *i;
		++i;
		int diffrence = 0;
		int one_jolt_diff = 0;
		int three_jolt_diff = 0;
		for (i; i != jolts_set.end(); ++i) {
			diffrence = *i - previous;
			if (diffrence == 1) {
				++one_jolt_diff;
				previous = *i;
			}
			else if (diffrence == 3) {
				++three_jolt_diff;
				previous = *i;
			}
			else {
				previous = *i;
			}
		}
		return one_jolt_diff * three_jolt_diff;
	}

	void print_jolts(vector<int>& copy_jolts) {
		for (const auto& jolt : copy_jolts) {
			cout << jolt << ' ';
		}
		cout << '\n';
	}

	int part02() {
		Matrix matrix;
		vector<int> copy_jolts;
		copy(jolts_set.begin(), jolts_set.end(), std::back_inserter(copy_jolts));
		for(size_t i=1; i< copy_jolts.size()-1; ++i) {
			copy_jolts.erase(copy_jolts.begin() +next_to_erase(copy_jolts));
			//size_t j = i;
			while(is_legit(copy_jolts)==true) {
				matrix.emplace_back(copy_jolts);
				copy_jolts.erase(copy_jolts.begin() + next_to_erase(copy_jolts));
			}
			copy_jolts.clear();
			copy(jolts_set.begin(), jolts_set.end(), std::back_inserter(copy_jolts));
		}
		print_matrix(matrix);
		sort(matrix.begin(), matrix.end());
		print_matrix(matrix);
		matrix.erase(unique(matrix.begin(), matrix.end()), matrix.end());
		print_matrix(matrix);
		return -1;
	}
	
	void print_matrix(const Matrix& matrix) {
		for(const auto& vec : matrix) {
			for(const auto& i : vec) {
				cout << i << ' ';
			}
			cout << '\n';
		}
		cout << '\n' << '\n';
	}
	
	size_t next_to_erase(const vector<int>& copy_jolts) const{
		size_t position = 0;
		for (size_t i = 1; i < copy_jolts.size() - 1; ++i) {
			if(copy_jolts.at(i)-copy_jolts.at(i-1) == 2 || copy_jolts.at(i) - copy_jolts.at(i - 1) == 1) {
				if(copy_jolts.at(i+1) - copy_jolts.at(i - 1) <=3) {
					position = i;
					break;
				}
			}
		}
		return position;
	}
	
	vector<int> next_to_erase2(const vector<int>& copy_jolts) const {
		size_t position = 0;
		vector<int> anwser;
		for (size_t i = 1; i < copy_jolts.size() - 1; ++i) {
			if (copy_jolts.at(i) - copy_jolts.at(i - 1) == 2 || copy_jolts.at(i) - copy_jolts.at(i - 1) == 1) {
				if (copy_jolts.at(i + 1) - copy_jolts.at(i - 1) <= 3) {
					anwser.emplace_back(copy_jolts.at(i));
				}
			}
		}
		return anwser;
	}

	int part2() {
		
		vector<int> copy_jolts;
		copy(jolts_set.begin(), jolts_set.end(), std::back_inserter(copy_jolts));
		vector<int> num_to_delete = next_to_erase2(copy_jolts);
		Matrix permutations;
		vector<int> tmp;
		int good_counter = 0;
		for (size_t comb_size = 1; comb_size <= num_to_delete.size(); ++comb_size) {
			do
			{
				copy(num_to_delete.begin(), num_to_delete.begin() + comb_size, back_inserter(tmp));
				//permutations.emplace_back(tmp);
				
				copy(jolts_set.begin(), jolts_set.end(), std::back_inserter(copy_jolts));
				for (const auto& number_to_delete : tmp) {
					copy_jolts.erase(std::remove(copy_jolts.begin(), copy_jolts.end(), number_to_delete), copy_jolts.end());
				}
				if (is_legit(copy_jolts) == true) {
					++good_counter;
				}
				copy_jolts.clear();
				tmp.clear();
			} while (next_combination(num_to_delete.begin(), num_to_delete.begin() + comb_size, num_to_delete.end()));
		}
		
		//for(const auto& vec : permutations) {
		//	copy(jolts_set.begin(), jolts_set.end(), std::back_inserter(copy_jolts));
		//	for(const auto& number_to_delete : vec) {
		//		copy_jolts.erase(std::remove(copy_jolts.begin(), copy_jolts.end(), number_to_delete), copy_jolts.end());
		//	}
		//	if(is_legit(copy_jolts)==true) {
		//		++good_counter;
		//	}
		//	copy_jolts.clear();
		//}
		return good_counter;
	}
	unsigned long long silnia(int ile) {
		unsigned long long sum = 1;
		for (int i = ile; i > 0;--i) {
			sum *= i;
		}
		return sum;
	}
	
	int comb(int n, int k) {
		return silnia(n) / (silnia(n - k)*silnia(k));
	}
};



int main() {
	Jolts jolts;
	//cout << jolts.part01();
	cout << "-------------------------------------  " << jolts.part2();
	
}
