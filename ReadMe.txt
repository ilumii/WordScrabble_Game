This game is a game that asks the user to decipher scrambled words.

You can run the game by compiling it in the command line by typing "make".This will create a executable named game. 
To finally run the game, you can type "./game" in the command line. 

To insert your own word file, you can either replace the base wordfile with one that is also named "words.txt" or type in "./game "textfile" " in the command line.

While playing the game, you can Enter (S) to save, (D) to display stats, (L) to use lifeline, (Q) to Quit the Game. You win by deciphering all words untill the wordfile 
no longer has words of the next length. Make sure to not spam buttons or else the game by glitch and not output correctly. If you insert a new word file, be aware that 
all high scores will be cleared. You can save your progress at any time by entering (S) and restart at the start of the game, however if you try to reload with no saved file
it will just start a new game.

Lifeline serves as a way to give u a pass as it is possible for it to generate a word that is shorter than the current word meaning lifeline can help lower difficulty. 

Errors: Don't insert a textfile with words that are all shorter than 3, the game will proceed to automatically close and display scores.