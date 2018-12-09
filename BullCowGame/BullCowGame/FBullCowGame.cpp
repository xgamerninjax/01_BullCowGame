#pragma once

#include "FBullCowGame.h"
#include <iostream>
#include <map>
#include <string>
#define TMap std::map

using int32 = int;
using FText = std::string;

FBullCowGame::FBullCowGame() { Reset(); }


int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
int32 FBullCowGame::GetCurrentTries() const { return MyCurrentTry; }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }




//Scale maximum tries by word length
int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,5},{4,5},{5,6},{6,7},{7,20},{8,25},{9,25},{10,25} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
} 

//Modify the game difficulty
void FBullCowGame::Difficulty()
{
	int32 UserDiff;
	const FString Word_List_Easy[] = { "mad", "raw", "word", "fold", "ring", "gear", "drink", "list"};
	const FString Word_List_Medium[] = { "plane", "stump", "space", "guard", "grain", "cabin", "darwin", "drunk", "venom", "prison", "fiesta", "dispute", "heroic", "combine"};
	const FString Word_List_Hard[] = { "consumed", "baptized", "capsize", "suitable", "creaking", "complain"  };
	do
	{
		std::cout << "\nSelect a difficulty from the list." << std::endl;
		std::cout << "Easy = 1 | Medium = 2 | Hard = 3" << std::endl;
		std::cout << "Easy = 3-5 Letters | Medium = 5-7 Letters | Hard = 7-8 Letters" << std::endl;
		std::cout << "Enter your selection: " << std::flush;
		std::cin >> UserDiff;
		std::cin.clear();
		std::cin.ignore();

		if (UserDiff == 1)
		{
			std::cout << "You have chosen easy difficulty.\n" << std::endl;
			MyHiddenWord = Word_List_Easy[rand() %8];
		}
		else if (UserDiff == 2)
		{
			std::cout << "You have chosen medium difficulty.\n" << std::endl;
			MyHiddenWord = Word_List_Medium[rand() % 14];
		}
		else if (UserDiff == 3)
		{
			std::cout << "You have chosen hard difficulty. Good luck!\n" << std::endl;
			MyHiddenWord = Word_List_Hard[rand() % 6];
		}
		else
		{
			std::cout << "Please select a difficulty listed above.\n" << std::endl;
			std::cin.clear();
			std::cin.ignore();
		}
	}
	while (UserDiff < 1 || UserDiff > 3);

	return;
} 

//Reset function
void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 5;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

//Check game wins 
int32 FBullCowGame::GameWins()
{
	if (IsGameWon()) { MyGameWins++; }
	return MyGameWins;
} 

//Error Checking
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) //if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) //if guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else if (false) //TODO - write already used function
	{
		return EGuessStatus::Already_Used;
	} 
	else { return EGuessStatus::OK; }
}

// Recieves a valid guess, increments turn, and returns bull/cow count.
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	//Loop Through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length(); //Assuming same length

	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar) { BullCowCount.Bulls++; }
				else { BullCowCount.Cows++; }
			}
		}
	}

	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

//Is the guess an isogram check
bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	//setup our map
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter); //handle mixed case
		if (LetterSeen[Letter])
		{ //if the letter is in the map
			return false; //we do NOT have an isogram
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

//Is the guess in all lowercase check
bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter)) //if not a lowercase letter
			return false;
	}
	return true;
}