#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 6262)
#include "utilities.h"
#include <iostream>
#include <cstring>
using namespace std;

const char WORDFILENAME[] = "C:/Users/karee/Documents/Project_5_CS31_Kareem_Dibs/words.txt";
const int MAXWORDS = 9000;

int playOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum);

int main()
{
	char wordList[MAXWORDS][MAXWORDLEN+1];
	int nWords = getWords(wordList, MAXWORDS, WORDFILENAME); //nWords = 7265
	//cerr << nWords;
	if (nWords < 1) { // nWords must be at least 1 for the game to be played. if not, the program is terminated.
		cout << "No words were loaded, so I can't play the game." << endl;
		return -1;
	}
	int rounds;
	cout << "How many rounds do you want to play? ";
	cin >> rounds; // input number of rounds user wants to play
	cin.ignore(10000, '\n');
	cout << endl;
	if (rounds < 1) { // rounds must be positive, as any rounds less than one would exhibit illogical behavior. if not, the program is terminated.
		cout << "The number of rounds must be positive." << endl;
		return -1;
	}
	double sumTries = 0;
	double average = 0;
	int minimum = 0;
	int maximum = 0;
	for (int i = 1; i <= rounds; i++) { // for loop to iterate through each round i.
		cout << "Round " << i << endl;
		int guessWord = randInt(0, nWords - 1); // obtain random index for hidden word.
		char specialWord[MAXWORDLEN + 1]; // new C string to store hidden word.
		strcpy(specialWord, wordList[guessWord]); // copy hidden word into new specialWord C string.
		for (int k = 0; specialWord[k] != '\0'; k++) {
			cerr << specialWord[k];
		}
		cerr << endl;
		int len = strlen(wordList[0]);
		//cerr << len << endl;
		cout << "The hidden word is " << len << " letters long." << endl; // print this statement to indicate the length of the hidden word.
		int tries = playOneRound(wordList, nWords, guessWord); // int tries is used to store the number of tries it took the user to guess the hidden word in playOneRound.
		if (tries == 1) {
			cout << "You got it in 1 try." << endl;
		}
		if (tries != 1) {
			cout << "You got it in " << tries << " tries." << endl;
		}
		sumTries += tries; // add up all tries from each round to sumTries for average calculations.
		cout.setf(ios::fixed);
		cout.precision(2);
		average = sumTries / i; // average is equal to the sum of all tries divided by i (rounds).
		if (i == 1) { // in the first round, the tries from that round will be the minimum and maximum because only one round had been played.
			minimum = tries;
			maximum = tries;
		}
		if (tries < minimum) { // if tries is less than the current minimum, set tries to minimum.
			minimum = tries; 
		}
		if (tries > maximum) { // if tries is more than the current maximum, set tries to maximum.
			maximum = tries; 
		}
		cout << "Average: " << average << ", minimum: " << minimum << ", maximum: " << maximum << endl; // for each round, output the overall average tries, minimum number of tries, and maximum number of tries.
		cout << endl;
	}
}

// plays one round of the game and returns the number of tries it took the user to guess the hidden word for that round.
int playOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum) {
	if (nWords < 1) // nWords must be positive. if it is, the program is terminated.
		return -1;
	if (wordnum < 0 || wordnum >= nWords) // wordNum cannot be negative or greater than or equal to nWords. if it is, the program is terminated.
		return -1;
	int tries = 0; // int tries will be used to count the number of tries it takes the user to guess the hidden word for a round.
	char probeWord[101];
	for (int i = 0; i < nWords; i++) {
		int golds = 0;
		int silvers = 0;
		cout << "Probe word: ";
		cin.getline(probeWord, 101); // user inputs a probeWord to guess the hidden word.
		//int x = strlen(probeWord);
		if (strcmp(words[wordnum], probeWord) == 0) { // if the hidden word and probeWord are equal, tries becomes 1, and 1 is returned.
			tries++;
			return tries;
		}
		if (strlen(probeWord) < 4 || strlen(probeWord) > 6) { // probeWord cannot be less than 4 or greater than 6 characters. if it is, the following message is printed.
			cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
			continue; // continues to the next iteration of the for loop, allowing the user to enter another probeWord.
		}
		bool isUpper = false;
		for (int k = 0; probeWord[k] != '\0'; k++) {
			if (!islower(probeWord[k])) { // if any character k in probeWord is lowercase, isUpper becomes true.
				isUpper = true;
			}
		}
		if (isUpper) { // if isUpper is true, the probeWord is not valid, and the following message is printed..
			cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
			continue; // continues to the next iteration of the for loop, allowing the user to enter another probeWord.
		}
		bool isThere = false;
		for (int j = 0; j < nWords; j++) {
			if (strcmp(words[j], probeWord) == 0) { // if words at j is equal to the probeWord, isThere becomes true, meaning that the probeWord exists in words.
				isThere = true;
				break; // break out of this for loop if words[j] == probeWord.
			}
		}
		if (!isThere && (strlen(probeWord) >= 4 || strlen(probeWord) <= 6)) { // if isThere is false and the probeWord is between 4 and 6 characters, the probeWord doesn't exist in words, so the following message is printed.
			cout << "I don't know that word." << endl;
			continue; // continues to the next iteration of the for loop, allowing the user to enter another probeWord.
		}
		tries++; // All checks for validity of the probeWord are passed, so increment tries by 1.
		char realWord[MAXWORDLEN + 1];
		strcpy(realWord, words[wordnum]); // copies the hidden word into the realWord C string.
		for (int m = 0; probeWord[m] != '\0'; m++) {
			if (realWord[m] == probeWord[m]) { // if there is a direct match at index m between realWord and probeWord, golds is incremented by 1.
				golds++;
			}
		}
		for (int n = 0; probeWord[n] != '\0'; n++) {
			for (int p = 0; realWord[p] != '\0'; p++) {
				if (realWord[p] == probeWord[n]) { // checks if realWord[p] is equal to probeWord[n]
					if (realWord[p] == probeWord[p] || realWord[n] == probeWord[n]) { // if realWord[p] is equal to probeWord[p] or if realWord[n] is equal to probeWord[n], then the match is a gold, not a silver.
						probeWord[n] = '1'; // arbitrary value to avoid extra silvers.
						realWord[p] = '2'; // arbitrary value to avoid extra silvers.
					}
					else if (realWord[p] != probeWord[p]) { // realWord[p] is not equal to probeWord[p], so a silver match has been found. Increment silvers by 1.
						silvers++;
						probeWord[n] = '3'; // arbitrary value to avoid extra silvers.
						realWord[p] = '4'; // arbitrary value to avoid extra silvers.
					}
				}
			}
		}
		strcpy(realWord, words[wordnum]); // reset realWord.
		cout << "Golds: " << golds << ", Silvers: " << silvers << endl; // output the number of golds and silvers for each probeWord.
	}
	return -1;
}