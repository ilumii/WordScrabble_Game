#ifndef LOGIC_H
#define LOGIC_H
#include <string>
#include <vector>

using namespace std;

class GameData{
	public:
		GameData(const string wordtxt);
		/*
			Sets all the values to ints and strings in private.
			
			@param argv[1] input file;
		*/
		void setBaseLevel();
		/*
			Sorts through all the words and find the word of the lowest length but longer than 3 letters.
		*/
		void fileRead();
		/*
			Reads the inputfile then insert all words of the games difficulty into a string.
		*/
		void wordGenerate();
		/*
			Randomly chooses a word out of all the words avaliable in the word bank and scrambles it up. This also saves the choosen word and scrambled word into private.
			
		*/
		bool checkAnswer(string guess);
		/*
			It takes in user's input for answer and checks it with the unscrambled version of the word and see if it is correct, if it is correct, user advances a bit closer to the next level.
			
			@param user's guessed word
			@return true if the answer is correct
		*/
		void reTry();
		/*
			This function controls the lifeline, it checks to see if the player has enough lifelines. If the player has at least 1 lifeline, the current word will reset to a word that has been used regardless
			of word length. If there is not enough lifelines left, it will not activate
		*/
		void scoreStore(int n1, int n2);
		/*
			This opens a text file named highScore and writes the current scores into the text file
			
			@param n1 and n2 represent that will be stored if they are higher than the current scores.
		*/
		void updateStats();
		/*
			This reads the text file highScore and compares it with current ingame score to see if any are higher than the documented highscores, if they are, the current values will replace text values.
		*/
		void displayStats();
		/*
			This will cout a highscore table and all current scores including remainging lifelines.
		*/
		int life();
		/*
			Returns the amount of lifelines in the current game.
			
			@return lifeline
		*/
		void saveGame();
		/*
			This will store all current game data including current score, level, and word into a saveNum / saveWord text file.
		*/
		void reloadGame();
		/*
			This will read all data in saveNum/saveWord and change current game values to reflect saved game.
		*/
		void start();
		/*
			This contains the do, while loop that doesnt stop till game over or end of guessable words.
		*/
	private:
		vector<string>wordBank;
		vector<string>usedBank;
		string shuffledWord;
		string currentWord;
		string newWord;
		string inputFile;
		int difficulty;
		int score;
		int correct;
		int remainingGuesses;
		int lifeline;
		int wordcount;
		int mostWord;
		int longWord;
};


#endif
