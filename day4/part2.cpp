#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_set>
#include <sstream>
#include <cmath>
#include <cctype>
#include <unordered_map>

using namespace std;

// parse the winning numbers into a hashset
unordered_set<int> winningSet(string& winningNums) {
	unordered_set<int> winning;
	for(int i = 0; i < winningNums.size(); i++) {
		if(!isdigit(winningNums[i])) continue;
		string currDigit;
		while(i < winningNums.size() && isdigit(winningNums[i])) currDigit += winningNums[i++];
		winning.insert(stoi(currDigit));
	}
	return winning;
}

// iterate over rest of the numbers, incrementing a count for each one we find in the winning numbers hashmap
int countWinningNumbers(unordered_set<int>& winningNums, string& yourNums) {
	int count = 0;
	for(int i = 0; i < yourNums.size(); i++) {
		if(!isdigit(yourNums[i])) continue;
		string currDigit;
		while(i < yourNums.size() && isdigit(yourNums[i])) currDigit += yourNums[i++];
		if(winningNums.count(stoi(currDigit))) count++;
		
	}
	return count; 
}


// score for a card is 0 if count = 0, otherwise 2 ^ (count - 1)

void cardScore(string& card, int currCard, unordered_map<int, int>& cardsMap) {
	// getting winning numbers
	int startingIndex = card.find(':') + 2;
	string winningNumbers = card.substr(startingIndex, card.find('|') - startingIndex);
	// cout << winningNumbers << endl;
	startingIndex = card.find('|') + 2;
	string yourNumbers = card.substr(startingIndex, card.size() - startingIndex);

	unordered_set<int> wSet = winningSet(winningNumbers);
	int cardMatches = countWinningNumbers(wSet, yourNumbers);
	cardsMap[currCard]++;
	for(int i = currCard + 1; i <= currCard + cardMatches; i++) {
		cardsMap[i] += cardsMap[currCard];
	}	
}


int main() {
	string fileName;
	cout << "Enter file name: ";
	cin >> fileName;
	ifstream file(fileName);;
	string line;	
	int currCard = 1;
	unordered_map<int, int> cardsMap;
	if(file.is_open()) {
		while(getline(file, line)) {
			//cout << cardS << endl;
			cardScore(line, currCard, cardsMap);	
			currCard++;
		}
		file.close();
	} else {
		cout << "File could not be opened" << endl;
	}
	int totalCards = 0;
	for(const auto& pair : cardsMap) totalCards += pair.second;
	cout << totalCards << endl;
	return 0;
}

