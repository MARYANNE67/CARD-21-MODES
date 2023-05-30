// PlayerMain.cpp - main program for the card player


//Ibeh Mary-Anne
//20-03-2023

#include <iostream>
#include "CardGame.h"

int main(void)
{

	CardGameAdapter *playGame = cardGame(); // call adapter function to create objects

	playGame->run(); // runs the game

	delete playGame;

	return 0;
};