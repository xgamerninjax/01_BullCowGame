#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//Unreal syntax
using FText = std::string;
using int32 = int;

//function prototypes
void Intro();
void IntroWordSizeAndTurnCount();
void PlayGame();
FText GetValidGuess();
bool PlayAgain();
void PrintGameSummary();
int32 GameWins();

// Instantiate a new game
FBullCowGame BCGame; 

//Main entry point for the game
int main()
{
	Intro();
	bool bPlayAgain = false;
	do
	{
		BCGame.Difficulty();
		IntroWordSizeAndTurnCount();
		PlayGame();
		bPlayAgain = PlayAgain();
	}
	while (bPlayAgain);

	//Exit application
	return 0; 
}

// Game introduction
void Intro()
{
	std::cout << std::endl;
	std::cout << "        / /           \\ \\                       \n";
	std::cout << "       ( (__-^^-,-^^-__) )                     \n";
	std::cout << "        `-_---'   '-_---'                      \n ";
	std::cout << "         <__|o' 'o|__>                       \n ";
	std::cout << "            \\  `  /                            \n ";
	std::cout << "             ): :(                             \n   ";
	std::cout << "           :o_o:                              \n  ";
	std::cout << "             '-'                              \n ";
	std::cout << "Welcome to Bulls and Cows, a fun word game!\n";
	std::cout << "The rules are simple, if you get a correct letter in the wrong place, you'll get a cow." << std::endl;
	std::cout << "If you get a correct letter in the correct place, you'll get a bull.\n" << std::endl;
}

//Game Rules
void IntroWordSizeAndTurnCount()
{
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << "\nTry to guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of within " << MaxTries << " tries." << std::endl;
	return;
}

//Turn Loop - Submit guess & print bulls/cows
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//Loop asking for guesses while the game is NOT won and there are still tries remaining 
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTries() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		//Submit Valid Guess
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		//Print number of bulls and cows
		std::cout << "Bulls: " << BullCowCount.Bulls << " Cows: " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	GameWins();
}

//loop until user gives valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	//FText Guess = "";
	FText Guess;

	do
	{
		//get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTries();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: " << std::flush;
		std::getline(std::cin, Guess);

		//Check validity and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Already_Used:
			std::cout << "You've already tried that word. \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters. \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter in all lowercase letters. \n\n";
			break;
		default:
			break;
		}
	}
	while (Status != EGuessStatus::OK); //Keep looping until we get no errors
	return Guess;
}

//Restart the game
bool PlayAgain()
{
	std::cout << "\n Do you want to play again? (Y/N) \n";
	std::cout << "Enter your response: " << std::flush;
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'Y' || Response[0] == 'y');
}

//End of game summary
void PrintGameSummary()
{
	if (BCGame.IsGameWon()) { std::cout << "Congratulations, you won! \n"; }
	else { std::cout << "Sorry, you're out of tries, better luck next time! \n"; }

	return;
}

//Count Game Wins.
int32 GameWins()
{
	//Game Win Counter
	int32 Wins = BCGame.GameWins();
	if (Wins == 1)
	{
		std::cout << "You have won " << Wins << " game." << std::endl;
	}
	else
	{
		std::cout << "You have won " << Wins << " games." << std::endl;
	}

	return Wins;
}
