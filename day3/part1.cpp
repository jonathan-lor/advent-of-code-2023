#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

bool isValidSymbol(char c) {
    return (!isdigit(c) && c != '.');
}

bool bordersSymbol(vector<string>& schematic, int r, int c) {
    int rows = schematic.size();
    int cols = schematic[0].size();
    
    // check cardinal

    // up
    if(r - 1 >= 0 && isValidSymbol(schematic[r - 1][c])) return true;
    // down
    if(r + 1 < rows && isValidSymbol(schematic[r + 1][c])) return true;
    // left
    if(c - 1 >= 0 && isValidSymbol(schematic[r][c - 1])) return true;
    // right
    if(c + 1 < cols && isValidSymbol(schematic[r][c + 1])) return true;

    // check diags

    // up left
    if(r - 1 >= 0 && c - 1 >= 0 && isValidSymbol(schematic[r - 1][c - 1])) return true;
    // up right
    if(r - 1 >= 0 && c + 1 < cols && isValidSymbol(schematic[r - 1][c + 1])) return true;
    // down left
    if(r + 1 < rows && c - 1 >= 0 && isValidSymbol(schematic[r + 1][c - 1])) return true;
    // down right
    if(r + 1 < rows && c + 1 < cols && isValidSymbol(schematic[r + 1][c + 1])) return true;

    return false;
}

// function to process and return sum of all part numbers in the schematic
int processSchematic(vector<string>& schematic) {
    // can view the schematic as a 2d array / matrix where strings are basically arrays here

    // nested loop to traverse the array from beginning to end since we have to check every char

    // ALL CASES FOR CHARACTERS:

    // Current character is a number
        // init a string to store digits as we traverse forward
        // init a bool to check if we will end up adding the current number to the sum
        // check all cardinal and diag spaces around this number
            // ALL CASES FOR ADJACENT CHARACTERS
                // An adjacent check would be out of bounds
                    // check current position accordingly to handle something like this

                // Adjacent number
                    // nothing i think as we've either already processed this or will process it

                // Adjacent Period
                    // Do nothing here

                // Adjacent Symbol
                    // this means at least one digit in the number borders a symbol
                    // so our eventual number will be added to the sum

    // Current character is a period
        // do nothing and keep going

    // Current charaacter is a symbol
        // do nothing and keep going

    int sum = 0;
    int rows = schematic.size();
    int cols = schematic[0].size();
    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < cols; c++) { 
            if(isdigit(schematic[r][c])) {
                string num = "";
                bool isValidNum = false;
                while(c < cols && isdigit(schematic[r][c])) {
                    num += schematic[r][c];
                    isValidNum = isValidNum || bordersSymbol(schematic, r, c);
                    c++;
                }
                if(isValidNum) sum += stoi(num);
            }
        }
    }

    return sum;
}

int main() {
    ifstream file("input.txt");
    string line;
    vector<string> schematic;

    if(file.is_open()) {
        while(getline(file, line)) {
            schematic.push_back(line);
        }
    } else {
        cout << "Couldn't open file" << endl;
    }

    cout << "Sum of part numbers: " << processSchematic(schematic) << endl;

    return 0;
}