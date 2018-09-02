#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h> 
#include <stdio.h>
#include "Logic.h"


using namespace std;

int main(int argc, char ** argv){
	
	string textfile;
	if(argc == 1){
		textfile = "word.txt";
	}
	else if (argc == 2){
		textfile = argv[1];
	}
	GameData player(textfile);
	player.start();

return 0;
}
