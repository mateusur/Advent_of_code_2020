#include <iosfwd>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <array>
using namespace std;
void read_from_file(const std::string& filename, std::stringstream& buffer) {
	std::ifstream file(filename);
    if (file) {
        buffer << file.rdbuf();
        file.close();
    }
}
bool is_tree(const string& line, const size_t& pos) {
    return line.at(pos % line.size()) == '#';
}
int part01(const size_t& right=3, bool skip2 = true) {
    stringstream buffer;
    string line;
    size_t offset = 0;
    unsigned trees_count = 0;
    bool every_row = true;
    read_from_file("day03_input.txt", buffer);
    while (buffer >> line) {
	    if(every_row){
		    if (is_tree(line, offset)) {
		    	++trees_count;
		    }
	    	offset += right;
	    }
    	if(!skip2) {
            every_row = !every_row;
    	}
    }
    cout  << trees_count << endl;
    return trees_count;
}
int part02() {
    std::array<size_t,5> offsets{ 1,3,5,7,1 };
    std::array<int, 5> sums{ part01(offsets[0]),part01(offsets[1]),part01(offsets[2]),part01(offsets[3]), part01(offsets[4],false), };
    int anwser=1;
	for(const int& sum : sums) {
        anwser *= sum;
    }
    cout << "Anwser part02: " << anwser << endl;
	return anwser;
}
int main() {
    part01();
    part02();

	return 0;
}