#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <set>

using namespace std;

// function that checks left and right of current index to build the full number that we discovered
// accepts a visited set and a coordinates
// using visited set to make sure we dont count more that once in checkAdjacent function
// returns an string which is string of either the full number, or zero if we already visited
 
string buildNumber(vector<string>& schematic, set< pair<int, int> >& visited, int r, int c) {
    
    // base case for out of bounds or reach num digit character
    if(r < 0 || r >= schematic.size() || c < 0 || c >= schematic[0].size() || !isdigit(schematic[r][c])) return "";

    if (visited.count(make_pair(r, c))) return "0";

    visited.insert(make_pair(r, c));

    return buildNumber(schematic, visited, r, c - 1) + schematic[r][c] + buildNumber(schematic, visited, r, c + 1);
	
} 

int checkAdjacent(vector<string>& schematic, int r, int c) {
    int rows = schematic.size();
    int cols = schematic[0].size();
    set< pair<int, int> > visited;  
    set<int> adjacentNums;

    // check cardinal

    // up
    if(r - 1 >= 0 && isdigit(schematic[r - 1][c])) adjacentNums.insert(stoi(buildNumber(schematic, visited, r - 1, c)));  //cout << "number found UP: " << schematic[r - 1][c] << endl;
    // down
    if(r + 1 < rows && isdigit(schematic[r + 1][c])) cout << "number found DOWN: " << schematic[r + 1][c] << endl;
    // left
    if(c - 1 >= 0 && isdigit(schematic[r][c - 1])) cout << "number found LEFT: " << schematic[r][c - 1] << endl;
    // right
    if(c + 1 < cols && isdigit(schematic[r][c + 1])) cout << "number found RIGHT: " << schematic[r][c + 1] << endl;

    // check diags

    // up left
    if(r - 1 >= 0 && c - 1 >= 0 && isdigit(schematic[r - 1][c - 1])) cout << "number found UP LEFT: " << schematic[r - 1][c - 1] << endl;
    // up right
    if(r - 1 >= 0 && c + 1 < cols && isdigit(schematic[r - 1][c + 1])) cout << "number found UP RIGHT: " << schematic[r - 1][c + 1] << endl;
    // down left
    if(r + 1 < rows && c - 1 >= 0 && isdigit(schematic[r + 1][c - 1])) cout << "number found DOWN LEFT: " << schematic[r + 1][c - 1] << endl;
    // down right
    if(r + 1 < rows && c + 1 < cols && isdigit(schematic[r + 1][c + 1])) cout << "number found DOWN RIGHT: " << schematic[r + 1][c + 1] << endl;

    return 0;
}

// function to process and return sum of all part numbers in the schematic
int processSchematic(vector<string>& schematic) {

    int sum = 0;
    int rows = schematic.size();
    int cols = schematic[0].size();
    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < cols; c++) { 
		
	// if character is a * , check all 8 directions for a number
	// then build the full number we find using recursive dfs function i think
	// need a way to make sure we dont count the same number twice
	// maybe maintain a visit set of number indexes 
	
	    if (schematic[r][c] == '*') {
		cout << "potential gear found. Checking adjacents: " << endl;
		sum += checkAdjacent(schematic, r, c);
	    }
	
	    // cout << schematic[r][c];
        }
	// cout << endl;
    }

    return sum;
}

int main() {

    string fileName;
    cout << "Enter file name: ";
    cin >> fileName;
    ifstream file(fileName);
    string line;
    vector<string> schematic;

    if(file.is_open()) {
        while(getline(file, line)) {
            schematic.push_back(line);
        }
    } else {
        cout << "Couldn't open file" << endl;
    }

    //  cout << "Sum of part numbers: " << processSchematic(schematic) << endl;

    processSchematic(schematic);

    return 0;
}
