#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>

using namespace std;

vector<string> split(const string& toSplit, char delim) {
	vector<string> tokens;
	string token;
	istringstream tokenStream(toSplit);

	while(getline(tokenStream, token, delim)) {
		tokens.push_back(token);	
	}
	return tokens;
}

int findAlpha(string s) {
	for(int i = 0; i < s.size(); i++) if(isalpha(s[i])) return i;
	return -1;
}

// takes line as input, returns game id if the game is possible, and zero otherwise
int possible(string& line, int red, int green, int blue) {
	
	int gameId = stoi(line.substr(5, line.find(":") - 2));

	string results = line.substr(line.find(":") + 2, line.size() - (line.find(":") + 2));

	vector<string> rounds = split(results, ';');
	for(const auto& round : rounds) {
		vector<string> colors = split(round, ',');
		for(const auto& color : colors) {
			// split each color into int and string
			int p = findAlpha(color);
			int num = stoi(color.substr(0, p));
			cout << num <<  " " << color[p] << endl;
			if(color[p] == 'r' && num > red) return 0;
			if(color[p] == 'g' && num > green) return 0;
			if(color[p] == 'b' && num > blue) return 0;
		}
	}
	return gameId;
}


int main() {

	ifstream file("input.txt");
	string line;
	int red, green, blue;

	cout << "Enter Red: ";
	cin >> red;

	cout << "Enter Green: ";
	cin >> green;

	cout << "Enter Blue: ";
	cin >> blue;

	int sum = 0;
	if(file.is_open()) {
		while(getline(file, line)) {
			// call function to see if game is possible, add add to sum 
			sum += possible(line, red, green, blue);
		}
		file.close();
	} else {
		cout << "File couldn't be opened" << endl;
	}
	cout << sum << endl;

	return 0;
}
