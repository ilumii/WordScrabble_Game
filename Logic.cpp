#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h> 
#include <stdio.h>
#include "Logic.h"

using namespace std;

	GameData::GameData(const string wordtxt){
		inputFile = wordtxt;
		score = 0;
		correct = 0;
		lifeline = 5;
		cout << "Welcome to: Decipher The Scrambled Word" << endl;
		setBaseLevel();
		remainingGuesses = 0;
		fileRead();
		updateStats();
		displayStats();
		cout << "\n";
		cout << "Game Starting: " <<endl;
		cout << "Enter (S) to save, (D) to display stats, (L) to use lifeline, (Q) to Quit" <<endl;
		remainingGuesses = 3;
	}
	void GameData::setBaseLevel(){ 
		int shortest = 10000;
		string read;
		ifstream wordfile;	
		wordfile.open("words.txt");
		while(!wordfile.eof()){
			while(wordfile >> read){
				if (read.length() < shortest && read.length() >= 3){
					shortest = read.length();
				}				
			}
		}
		difficulty = shortest;
		wordfile.close();			
	}
	void GameData::fileRead(){ 
		srand(time(NULL));
		wordBank.clear(); 
		wordcount = 0;
		string read;
		ifstream wordfile;	
		wordfile.open("words.txt");
		if(wordfile.is_open()){
			while(!wordfile.eof()){
				while(wordfile >> read){
					wordcount += 1;
					if (read.length() == difficulty){
						wordBank.push_back(read);
						usedBank.push_back(read);
					}			
				}
			}
		}
		wordfile.close();
	}
	void GameData::wordGenerate(){ 
		srand(time(NULL));
		if (wordBank.size() == 0){
			cout << "congrats" << endl;
			remainingGuesses = 0;
		}
		else{
			currentWord = wordBank[rand() % (wordBank.size())];
			shuffledWord = currentWord;
			random_shuffle(shuffledWord.begin(), shuffledWord.end());
			cout << "Decipher The Following: " << shuffledWord << endl;
			cout << "Your Guess is: ";
		}
	}
	bool GameData::checkAnswer(string guess){ 
		if (guess == currentWord || guess == newWord){
			remainingGuesses = 3;
			cout << "\n";
			cout << "Good job!" << endl;
			score += 1;
			if (correct != 2){
				correct += 1;
			}
			else {
				difficulty += 1;
				correct = 0;
				fileRead();
			}
			return true;
		}
		else {
			remainingGuesses -= 1;
			cout << "\n";
			cout << "Nice try! You have: " << remainingGuesses << " tries remaining" << endl;
			cout << "Decipher The Following: " << shuffledWord << endl;
			cout << "Your Guess is: ";
			return false;
		}
	}		
	void GameData::reTry(){  
		if (lifeline > 1){
			remainingGuesses = 3;
			lifeline -= 1;
			srand(time(NULL));
			newWord = usedBank[rand() % (usedBank.size())];
			if (newWord != currentWord){
				shuffledWord = newWord;
				currentWord = newWord;
				random_shuffle(shuffledWord.begin(), shuffledWord.end());
				cout << "\n";
				cout << "Lifelines Remaining: " << lifeline << endl;
				cout << "Decipher The Following: " << shuffledWord << endl;
				cout << "Your Guess is: ";
			}
			else{
				newWord = usedBank[rand() % (usedBank.size())];
			}
		}
		else{  
			cout << "\n";
			cout << "No Lifelines Remaining" << endl;
			cout << "Decipher The Following: " << shuffledWord << endl;
			cout << "Your Guess is: ";
		}
	}	
	void GameData::scoreStore(int n1, int n2){
		ofstream highScore;
		highScore.open("highScore.txt");
		if (highScore.is_open()){
			highScore << n1 << endl;
			highScore << n2 << endl;
			highScore << wordcount;
		}
		highScore.close();
	}
	void GameData::updateStats(){
		ifstream highScore;
		highScore.open("highScore.txt");
		if (highScore.is_open()){
			int n1, n2, n3;
			highScore >> n1 >> n2 >> n3;
			if (n3 != wordcount && remainingGuesses > 0){
				scoreStore(0, 0);
				mostWord = 0;
				longWord = 0;
			}
			else if (n3 == wordcount){
				if (score > n1 && difficulty > n2){
					scoreStore(score, difficulty);
					mostWord = score;
					longWord = difficulty;
				}
				else if (score > n1){
					scoreStore(score, n2);
					mostWord = score;
					longWord = n2;
				}
				else if (difficulty > n2){
					scoreStore(n1, difficulty);
					mostWord = n1;
					longWord = difficulty;
				}
				else {
					scoreStore(n1,n2);
					mostWord = n1;
					longWord = n2;
				}
			}
		}
		highScore.close();
	}
	void GameData::displayStats(){
		updateStats();
		cout <<"\n";
		cout << "HighScores:" << endl;
		cout << "Most Words Guessed: " << mostWord << endl;
		cout << "Longest Word Length Guessed: " << longWord << endl;
		cout <<"\n";
		cout << "Current Score:" << endl;
		cout << "Most Words Guessed: " << score << endl;
		if (score == 0){
			cout << "Longest Word Length Guessed: 0" << endl;
		}
		else{
			cout << "Longest Word Length Guessed: " << difficulty << endl;	
		}
		cout << "Remaining Lifelines: " << lifeline <<endl;	
		cout <<"\n";
	}
	int GameData::life(){
		return remainingGuesses;
	}
	void GameData::saveGame(){
		ofstream saveData;
		saveData.open("saveWord.txt");
		if (saveData.is_open()){
			saveData << currentWord << endl;
			saveData << shuffledWord << endl;
		}
		saveData.close();
		ofstream saveData2;
		saveData2.open("saveNum.txt");
		if (saveData2.is_open()){
			saveData2 << score << endl;
			saveData2 << difficulty << endl;
			saveData2 << remainingGuesses << endl;
			saveData2 << lifeline ;
		}
		cout << "\n";
		cout << "Game Saved" << endl;
		saveData2.close();
	}
	void GameData::reloadGame(){
		ifstream saveData;
		saveData.open("saveWord.txt");
		if (saveData.is_open()){
			vector <string> temp;
			string read;
			while(!saveData.eof()){
				while (saveData >> read){
					temp.push_back(read);
				}
			}
			currentWord = temp[0];
			shuffledWord = temp[1];
		}
		saveData.close();
		ifstream saveData2;
		saveData2.open("saveNum.txt");
		if (saveData2.is_open()){
			while(!saveData2.eof()){
				int n1, n2, n3, n4;
				saveData2 >> n1 >> n2 >> n3 >> n4;
				score = n1;
				difficulty = n2;
				remainingGuesses = n3;
				lifeline = n4;
			}
		}	
		saveData2.close();
		cout << "Decipher The Following: " << shuffledWord << endl;
		cout << "Your Guess is: ";
	}
	void GameData::start(){
		string input;
		cout << "Load save data? Y/N: " ;
		do{
  			cin >> input;
   			if (input == "L"){
   				reTry();
			}
			else if (input == "Y"){
				cout <<"\n";
				reloadGame();
			}
			else if (input == "N"){
				cout <<"\n";
				wordGenerate();
			}
			else if (input == "D"){
				displayStats();
				cout << "Decipher The Following: " << shuffledWord << endl;
				cout << "Your Guess is: ";
			}
			else if (input == "S"){
				saveGame();
				cout << "Continue? Y/N: ";
				cin >> input;
				if(input == "Y"){
					cout <<"\n";
					reloadGame();
				}
				else if(input == "N"){
					cout << "Exiting Game" << endl;
					break;
				}
			}
			else if (input == "Q"){
				saveGame();
				cout << "Exiting Game" << endl;
				break;
			}
    		else if(checkAnswer(input) == true){       
				wordGenerate();
			}
 	 	} while(input != "Q" && life() != 0);
		updateStats();
		displayStats();
		cout << "Exiting Game" << endl;

	}
