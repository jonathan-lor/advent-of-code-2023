#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

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

// takes line as input, returns game id if the game is possible, and zero otherwise
int possible(string& line, int red, int green, int blue) {
	
	int gameId = stoi(line.substr(5, line.find(":") - 2));

	string results = line.substr(line.find(":") + 2, line.size() - (line.find(":") + 2));

	vector<string> rounds = split(results, ';');
	for(const auto& round : rounds) {
		vector<string> colors = split(round, ',');
		for(const auto& color : colors) {
			
		}
	}
	return 0;
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

	if(file.is_open()) {
		while(getline(file, line)) {

			cout << line << endl;
			// call function to see if game is possible, add add to sum 
			possible(line, red, green, blue);
		}
		file.close();
	} else {
		cout << "File couldn't be opened" << endl;
	}

	return 0;
}
