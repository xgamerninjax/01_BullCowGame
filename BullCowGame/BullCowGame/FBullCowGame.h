#pragma once

#include <string>

using FString = std::string;
using int32 = int;

//default bull/cow values
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

//Guess validation and error checking outputs
enum EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Already_Used,
	Not_Lowercase
};

//Main Class
class FBullCowGame
{
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTries() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	int32 GameWins();
	EGuessStatus CheckGuessValidity(FString) const;
	void Difficulty();
	void Reset();
	

	// Count Bulls & Cows, increase turn/try number - Assuming valid guess
	FBullCowCount SubmitValidGuess(FString);

private:
	// In constructor 
	int32 MyCurrentTry;
	int32 MyGameWins;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};