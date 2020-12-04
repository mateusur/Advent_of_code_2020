#include <algorithm>
#include <iosfwd>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <regex>

using namespace std;
class Person
{

    string byr="", iyr="", eyr="", pid="", cid="";
    string hgt ="", hcl="", ecl="";
public:
	void clear(){
         byr.clear(), iyr.clear(), eyr.clear(), pid.clear(), cid.clear();
        hcl.clear(), ecl.clear(), hgt.clear();
    }
	bool valid() const{
		if(byr.empty() || iyr.empty() || eyr.empty() || hgt.empty() || pid.empty() || hcl.empty() || ecl.empty() ) {
            return false;
		}
		else {
            return true;
		}
	}
	void update( string& line) {
        replace(line.begin(), line.end(), ':', ' ');
        stringstream input(line);
        string field;
        while (input >> field) {
        	if(field=="byr") {
                input >> byr;
        	}
        	else if (field == "iyr") {
                input >> iyr;
        	}
            else if (field == "eyr") {
                input >> eyr;
            }
            else if (field == "hgt") {
                input >> hgt;
            }
            else if (field == "pid") {
                input >> pid;
            }
            else if (field == "hcl") {
                input >> hcl;
            }
            else if (field == "ecl") {
                input >> ecl;
            }
        	else if( field == "cid") {
                input >> cid;
        	}
        }
	}
};
int part01() {
    std::ifstream file("day04_input.txt");
    string line;
    Person person;
    int valid_passports = 0;
    int puste_linie = 0;
	if (file) {
	    while (getline(file,line)) {
            if (line.empty()) {
                if(person.valid()) {
                    valid_passports++;
                }
                person.clear();
                puste_linie++;
            }
			else {
                person.update(line);
			}
                
	    }
        file.close();
    }
    cout << valid_passports << endl;
    return valid_passports;
}

class Passport
{
     const string h_cm = "cm";
     bool cm;
    int byr = 0 , iyr = 0, eyr = 0, cid = 0, hgt = 0;
    string hcl = "", ecl = "", pid = "";
public:
    void clear() {
        byr = 0, iyr = 0, eyr = 0, pid.clear(), cid = 0;
        hcl.clear(), ecl.clear(), hgt=0;
    }
	    bool valid() const {
        if (byr>2002 || byr <1920) {
            return false;
        }
    	if(iyr > 2020 || iyr < 2010) {
    		return false;
    	}
        if (eyr > 2030 || eyr < 2020) {
            return false;
        }
        if ( (cm && (hgt <150  || hgt >193)) || (cm==false && (hgt<59 || hgt>76))) {
            return false;
        }
        if (!regex_match(hcl,regex("^#(?:[0-9a-f]{6})$"))) {
            return false;
        }
        if (ecl != "amb" && ecl != "blu" && ecl != "brn" && ecl != "gry" && ecl != "grn" && ecl != "hzl" && ecl != "oth") {
            return false;
        }
        if (!regex_match(pid, regex("^[0-9]{9}$"))) {
            return false;
        }
        else {
            return true;
        }
    }
    void update(string& line) {
        replace(line.begin(), line.end(), ':', ' ');
        stringstream input(line);
        string field;
        while (input >> field) {
            if (field == "byr") {
                input >> byr;
            }
            else if (field == "iyr") {
                input >> iyr;
            }
            else if (field == "eyr") {
                input >> eyr;
            }
            else if (field == "hgt") {
                string tmp;
                input >> tmp;
            	if(tmp.find(h_cm) != string::npos) {
                    cm = true;
                    hgt = stoi(tmp.substr(0, tmp.size() - 2));
            	}
            	else if(tmp.find("in") != string::npos) {
                    hgt = stoi(tmp.substr(0, tmp.size() - 2));
                    cm = false;
            	}
            	else {
                    hgt = 0;
            	}
                
            }
            else if (field == "pid") {
                input >> pid;
            }
            else if (field == "hcl") {
                input >> hcl;
            }
            else if (field == "ecl") {
                input >> ecl;
            }
            else if (field == "cid") {
                input >> cid;
            }
        }
    }
};

int part02() {
    std::ifstream file("day04_input.txt");
    string line;
    Passport person;
    int valid_passports = 0;
    int puste_linie = 0;
    if (file) {
        while (getline(file, line)) {
            if (line.empty()) {
                if (person.valid()) {
                    valid_passports++;
                }
                person.clear();
                puste_linie++;
            }
            else {
                person.update(line);
            }
        }
        if (person.valid()) {
            valid_passports++;
        }
        file.close();
    }
    cout << valid_passports << endl;
    return valid_passports;
}
int main() {
    //part01();
    part02();

}