#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<random>
#include<ctime>
using namespace std;


//If uppercase, turn into lowercase
char checkLetter(char* letter) {
	if (*letter >= 65 && *letter <= 90) {
		*letter = *letter + 32;
	}
	return *letter;

}

int main() {
	ifstream words("words.txt");
	ofstream result("result.txt", fstream::app);
	vector<string> sityvebi;
	string name, word, random_word, covered_word, random2;
	int n = 3000, index, counter, hearts = 4, tries = 0,search;
	char letter;
	cout << "I have chosen random word. You have to find it out in only 5 attempts.Good luck!" << endl;
	cout << "First, enter your name! (NO SPACES! only one word :) )" << endl;
	cin >> name;
	cout << "Here is covered word. You have 5 attempts" << endl;
	cout << "Good luck " << name << "!" << endl;
	for (int i = 1; i <= n; i++)
	{
		words >> word;
		sityvebi.push_back(word);
	}
	srand(time(0));
	index = rand() % 3001; //Generate random index in range [0,3000]
	random_word = sityvebi[index]; //Choose word with above generated random index
	random2 = random_word; //Keep random word, to use in the game process in the next way: compare user's letter to the letters of the random word and decide to change "*"with letter or not
	for (int j = 0; j < random_word.size(); j++)
	{
		random_word[j] = '*';
	}
	cout << endl;
	covered_word = random_word;
	cout << covered_word;
	cout << endl;
	while (true)
	{
		counter = covered_word.size() + 1;
		cin >> letter;
		letter = checkLetter(&letter); //Check if letter is uppercase or not
		tries++;
		search = random2.find(letter); //Check if user made a correct guess or not.
		if (search < 0) { hearts--; cout << "You are mistaken.Think better!" << "You have " << hearts + 1 << " chances" << endl << endl; } //user's guess is incorrect, so their chances is decremented
		if (search >= 0) { cout << "You got it!" << "You have " << hearts + 1 << " chances" << endl << endl; }//User's guess is correct
		for (int g = 0; g < random_word.size(); g++) //If guess is correct, change "*" with an appropirate letter
		{
			if (random2[g] == letter)
			{
				covered_word[g] = letter;
			}
			if (covered_word[g] != '*')
			{
				counter -= 1;
			}
		}

		if (hearts < 0) //User made 5 incorrect guesses, so the game ended. Time to print the word.
		{
			cout << "You lost! No attempts left :("  << endl;
			cout << "My word was " << random2 << endl;
			result << name << " " << "lost!" << endl;
			break;
		}
		if (counter <= 1) //Variable "Counter" keeps info about the quantity of open(guessed) letteers in the word. Game is completed after Counter will be eqaul to the size of word
		{
			cout << "Congrats! You won! :)" << endl;
			cout << "My word was " << random2 << endl;
			cout << "You won in " << tries << " attempts" << endl;
			result << name << " " << "won in " << tries << " attempts!" << endl;
			break;
		}
		cout << covered_word << endl << endl;

	}
}
