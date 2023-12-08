#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <set>

using namespace std;
 
// used in checkAdjacent - checks left and right to build the complete number
string buildNumber(vector<string>& schematic, set< pair<int, int> >& visited, int r, int c) {
    
    // base case for out of bounds or reach num digit character or already visited this index
    if(r < 0 || r >= schematic.size() || c < 0 || c >= schematic[0].size() || !isdigit(schematic[r][c]) || visited.count(make_pair(r, c))) return "";

    visited.insert(make_pair(r, c));

    return buildNumber(schematic, visited, r, c - 1) + schematic[r][c] + buildNumber(schematic, visited, r, c + 1);
	
} 

// used in processSchematic - checks if current '*' has 2 separate adjacent numbers and returns them multiplied if so; zero otherwise
int checkAdjacent(vector<string>& schematic, int r, int c) {
    int rows = schematic.size();
    int cols = schematic[0].size();
    set< pair<int, int> > visited;
    // storing all adjacent numbers in their string form
    set<string> adjacentNumStrings;

    // check cardinal

    // up
    if(r - 1 >= 0 && isdigit(schematic[r - 1][c])) adjacentNumStrings.insert(buildNumber(schematic, visited, r - 1, c));
    // down
    if(r + 1 < rows && isdigit(schematic[r + 1][c])) adjacentNumStrings.insert(buildNumber(schematic, visited, r + 1, c));
    // left
    if(c - 1 >= 0 && isdigit(schematic[r][c - 1])) adjacentNumStrings.insert(buildNumber(schematic, visited, r, c - 1));
    // right
    if(c + 1 < cols && isdigit(schematic[r][c + 1])) adjacentNumStrings.insert(buildNumber(schematic, visited, r, c + 1));

    // check diags

    // up left
    if(r - 1 >= 0 && c - 1 >= 0 && isdigit(schematic[r - 1][c - 1])) adjacentNumStrings.insert(buildNumber(schematic, visited, r - 1, c - 1));
    // up right
    if(r - 1 >= 0 && c + 1 < cols && isdigit(schematic[r - 1][c + 1])) adjacentNumStrings.insert(buildNumber(schematic, visited, r - 1, c + 1));
    // down left
    if(r + 1 < rows && c - 1 >= 0 && isdigit(schematic[r + 1][c - 1])) adjacentNumStrings.insert(buildNumber(schematic, visited, r + 1, c - 1));
    // down right
    if(r + 1 < rows && c + 1 < cols && isdigit(schematic[r + 1][c + 1])) adjacentNumStrings.insert(buildNumber(schematic, visited, r + 1, c + 1));

    // if we added the empty string at any point from buildNumber base case
    adjacentNumStrings.erase("");

    if(adjacentNumStrings.size() == 2) {
        int gearRatio = 1;
        for(const string& adjacentNumString : adjacentNumStrings) gearRatio *= stoi(adjacentNumString);
        return gearRatio;
    }

    return 0;
}

// process the engine schematic and return sum of gear ratios
int processSchematic(vector<string>& schematic) {

    int sum = 0;
    int rows = schematic.size();
    int cols = schematic[0].size();
    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < cols; c++) { 
		
	        // if character is a * , check all 8 directions for a digit
	        // if we hit a digit, check left and right to build the full number recursively
	        // need a way to make sure we dont count the same number twice
	        // maybe maintain a set of visited indexes 
	
	        if (schematic[r][c] == '*') {
		        sum += checkAdjacent(schematic, r, c);
	        }
        }
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

    cout << "Sum of gear ratios: " << processSchematic(schematic) << endl;

    return 0;
}
