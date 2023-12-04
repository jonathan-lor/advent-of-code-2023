#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>

using namespace std;

// get calibration value for a single line
int getCalibration(string line) {
	// we observe that string representation of digits are 3-5 characters in length
	// expanding on our two pointer approach, we can first do bounds check, and then substring for next 3-5 characters accordingly to see if we get any numbers from that
	// maintain map of strings as numbers to their actual numbers

	int res = 0;
	int n = line.size();
	int left = 0;
	int right = n - 1;
	bool leftFound = false;
	bool rightFound = false;
	unordered_map<string, int> numbers;
	numbers["one"] = 1;
	numbers["two"] = 2;
	numbers["three"] = 3;
	numbers["four"] = 4;
	numbers["five"] = 5;
	numbers["six"] = 6;
	numbers["seven"] = 7;
	numbers["eight"] = 8;
	numbers["nine"] = 9;

	while (left < n && right >= 0 && !(leftFound && rightFound)) {

		if (!leftFound) {
			if (isdigit(line[left])) {
                        	res += (10 * (line[left] - '0'));
                        	leftFound = true;
                	}

			// check substrings for left
                	if (left + 2 < n && numbers.count(line.substr(left, 3))) {
                        	res += numbers[line.substr(left, 3)] * 10;
                        	leftFound = true;
                	}

                	if (left + 3 < n && numbers.count(line.substr(left, 4))) {
                        	res += numbers[line.substr(left, 4)] * 10;
                        	leftFound = true;
                	}

                	if (left + 4 < n && numbers.count(line.substr(left, 5))) {
                        	res += numbers[line.substr(left, 5)] * 10;
                        	leftFound = true;
                	}
		}

                if (!rightFound) {
		        if (isdigit(line[right])) {
                        	res += (line[right] - '0');
                        	rightFound = true;
                	}

                	// check substrings for right
                	if (right - 2 >= 0 && numbers.count(line.substr(right - 2, 3))) {
                        	res += numbers[line.substr(right - 2, 3)];
                        	rightFound = true;
               		}

                	if (right - 3 >= 0 && numbers.count(line.substr(right - 3, 4))) {
                        	res += numbers[line.substr(right - 3, 4)];
                        	rightFound = true;
                	}

                	if (right - 4 >= 0 && numbers.count(line.substr(right - 4, 5))) {
                        	res += numbers[line.substr(right - 4, 5)];
                        	rightFound = true;
                	}
                }

		left++;
		right--;
	}

	return res;
}

int main() {
	ifstream file("input.txt");
	string line;
	int sum = 0;	

	if(file.is_open()) {
		while (getline(file, line)) {
			sum += getCalibration(line);	
		}
		file.close();
	} else {
		cout << "File couldn't be opened" << endl;
	}

	cout << "Sum of calibrations is: " << sum << endl;
	
	return 0;
}
