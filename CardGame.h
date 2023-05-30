// CardGame.h - functions to run adapter for game mode

//Ibeh Mary-Anne
//20-03-2023

#ifndef _CARDGAME_H_
#define _CARDGAME_H_

#include <iostream>
#include <random>
#include <vector>
#include <typeinfo>
#include <iomanip>
#include "CardGameAdapter.h"
#include "PlayerAdult.h"
#include "PlayerYouth.h"

const int MAX = 21; // max number for card values
const int NUM = 2; // number of players
const int RANGE_DEPENDENT_CARDS = 5; // 1-5
const int RANGE_ATTACK_CARDS_YOUTH = 10; // 1-10
const int RANGE_ATTACK_CARDS_ADULT = 15; // 1-15

template <typename T>
class CardGame : public CardGameAdapter
{
    PlayerBase<T> *player[NUM];
    GameMode gameMode;

public:
    CardGame()
    {
        player[0] = new PlayerYouth<T>("Noah");
        player[1] = new PlayerAdult<T>("Kenneth");
    };

   ~CardGame()
{
    for (int i = 0; i < NUM; ++i)
    {
        if (player[i] != nullptr) {
            delete player[i];
        }
    }
}

    void setMode(int mode)
    {
        if (mode == 0)
        {
            gameMode = GameMode::HighDefinition;
        }
        else if (mode == 1)
        {
            gameMode = GameMode::LowDefinition;
        };
    }

    double generateRandomDecimal(int maxValue)
    {
        // reference: https://stackoverflow.com/questions/288739/generate-random-numbers-uniformly-over-an-entire-range
        std::random_device rd;                                              // obtain a random number from hardware
        std::mt19937 gen(rd());                                             // seed the generator
        std::uniform_int_distribution<int> intDistr(1000, maxValue * 1000); // define the range with three decimal places
        double result = static_cast<double>(intDistr(gen)) / 1000.0;        // convert the generated integer to decimal with three decimal places
        return result;
    }

    int generateRandomInt(int maxValue)
    {
        // reference: https://stackoverflow.com/questions/288739/generate-random-numbers-uniformly-over-an-entire-range
        std::random_device rd;                                 // obtain a random number from hardware
        std::mt19937 gen(rd());                                // seed the generator
        std::uniform_int_distribution<int> distr(1, maxValue); // define the range
        return distr(gen);
    }

    void run()
    {
        bool gameOver = false;
        double bet = 0;

        do
        {
            // ===========SET GAME BET=================

            // Prompt the players for the amount they want to bet. It has to be between $10 and $300
            std::cout << "How much do you both want to bet? (min $10, max $300): $";
            std::cin >> bet;
            if (bet < 10)
            {
                // If they enter a value below $10, set the amount to $10
                bet = 10;
            }
            else if (bet > 300)
            {
                // If they enter a value above $300, set the amount to $300
                bet = 300;
            };

            std::cout << std::endl;

            // ===========SETTING UP CARDS=================

            for (int i = 0; i < NUM; ++i)
            {

                int numOfCards = 0;
                int numOfAttackCards = 0;
                char addCard;
                char addAttackCard;
                // Prompt the player for the number of dependent cards
                std::cout << player[i]->getName() << ", how many dependent cards do you want? ";
                std::cin >> numOfCards;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // buffer issues

                std::vector<int> insertCards;
                for (int k = 0; k < numOfCards; ++k)
                {
                    insertCards.push_back(generateRandomInt(RANGE_DEPENDENT_CARDS));
                }
                player[i]->addDependentCards(insertCards);
                insertCards.clear(); // clear to reuse

                // Prompt the player for the number of attack cards
                std::cout << player[i]->getName() << ", how many attack cards do you want? ";
                std::cin >> numOfAttackCards;
                std::vector<T> tempAttackCards;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // buffer issues

                PlayerYouth<T> *youthPlayer = dynamic_cast<PlayerYouth<T> *>(player[i]); // dynamic_cast returns null if it is not equal
                PlayerAdult<T> *adultPlayer = dynamic_cast<PlayerAdult<T> *>(player[i]);
                if (youthPlayer != nullptr) // player[i] is a dynamic type of PlayerYouth<T> class
                {
                    if (gameMode == GameMode::HighDefinition)
                    {
                        for (int m = 0; m < numOfAttackCards; m++)
                            tempAttackCards.push_back(generateRandomDecimal(RANGE_ATTACK_CARDS_YOUTH));
                    }
                    else
                    {
                        for (int k = 0; k < numOfAttackCards; k++)
                            tempAttackCards.push_back(generateRandomInt(RANGE_ATTACK_CARDS_YOUTH));
                    }
                }
                else if (adultPlayer != nullptr) // player[i] is a dynamic type of PlayerAdult<T> class
                {
                    if (gameMode == GameMode::HighDefinition)
                    {
                        for (int n = 0; n < numOfAttackCards; n++)
                            tempAttackCards.push_back(generateRandomDecimal(RANGE_ATTACK_CARDS_ADULT));
                    }
                    else
                    {
                        for (int l = 0; l < numOfAttackCards; l++)
                            tempAttackCards.push_back(generateRandomInt(RANGE_ATTACK_CARDS_ADULT));
                    }
                };

                player[i]->addCards(tempAttackCards); // assigning a vector of attack cards

                // Report the player's name and the sum of the player's cards
                std::cout << player[i]->getName() << ", the sum of your cards is " << player[i]->sumAllCards() << std::endl;

                // Ask the player if (s)he wishes to add a dependent card to the existing list of dependent cards
                std::cout << "Do you want to add a dependent card? [Y,N] ";
                std::cin >> addCard;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // buffer issues

                if (addCard == 'Y' || addCard == 'y')
                {
                    player[i]->addDependentCard(generateRandomInt(RANGE_DEPENDENT_CARDS));
                }

                // Report the player's name and the sum of the player's cards
                std::cout << player[i]->getName() << ", the sum of your cards is " << player[i]->sumAllCards() << std::endl;

                // Ask the player if (s)he wishes to add an attack card to the existing list of attack cards
                std::cout << "Do you want to add an attack card? [Y,N] ";
                std::cin >> addAttackCard;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (addAttackCard == 'Y' || addAttackCard == 'y')
                {
                    if (youthPlayer != nullptr)
                    {
                        if (gameMode == GameMode::HighDefinition)
                        {
                            player[i]->addCard(generateRandomDecimal(RANGE_ATTACK_CARDS_YOUTH)); // adding one random attack card
                        }
                        else
                        {
                            player[i]->addCard(generateRandomInt(RANGE_ATTACK_CARDS_YOUTH)); // adding one random attack card
                        }
                    }
                    else if (adultPlayer != nullptr)
                    {
                        if (gameMode == GameMode::HighDefinition)
                        {
                            player[i]->addCard(generateRandomDecimal(RANGE_ATTACK_CARDS_ADULT)); // adding one random attack card
                        }
                        else
                        {
                            player[i]->addCard(generateRandomInt(RANGE_ATTACK_CARDS_ADULT)); // adding one random attack card
                        }
                    };
                }

                // Report the player's name and the sum of the player's cards
                std::cout << player[i]->getName() << ", the sum of your cards is " << player[i]->sumAllCards() << std::endl;

                std::cout << std::endl;
            }

            // ===========SUMMARIZE POINTS=================

            // Report the name and points for each player
            for (int j = 0; j < NUM; ++j)
            {
                std::cout << player[j]->getName() << " has " << player[j]->sumAllCards() << " points." << std::endl;
            };

            std::cout << std::endl;

            // ===========DETERMINING WINNER=================
            // If a player has a sum over the limit of 21, the player is disqualified. Print the player's name,
            // the sum of the player's cards, and a message that states this is over the limit.
            // Apply this test to both players
            for (int j = 0; j < NUM; ++j)
            {
                if (player[j]->sumAllCards() > 21)
                {
                    std::cout << player[j]->getName() << " has a sum of " << player[j]->sumAllCards() << ", which is over the limit." << std::endl;
                }
            };
            // If both players are disqualified, print that both players are over the limit and have been disqualified.
            if (player[0]->sumAllCards() > 21 && player[1]->sumAllCards() > 21)
            {
                std::cout << "Both players are over the limit and have been disqualified." << std::endl;
            }
            else if (player[0]->sumAllCards() > 21)
            {
                // If just player 1 is disqualified, print player 1's name and a message that (s)he has been disqualified
                // for going over the limit. Print player 2's name and indicate that (s)he has won.
                std::cout << player[0]->getName() << " has been disqualified for going over the limit. " << player[1]->getName() << " has won." << std::endl;
                // Move the amount that was bet away from player 1 and towards player 2 using the << and >> operators.
                *player[0] >> bet; // minus bet
                *player[1] << bet; // add bet
            }
            else if (player[1]->sumAllCards() > 21)
            {
                // If just player 2 is disqualified, print player 2's name and a message that (s)he has been disqualified
                // for going over the limit. Print player 1's name and indicate that (s)he has won.
                std::cout << player[1]->getName() << " has been disqualified for going over the limit. " << player[0]->getName() << " has won." << std::endl;
                // Move the amount that was bet away from player 2 and towards player 1 using the << and >> operators.
                *player[1] >> bet; // minus bet
                *player[0] << bet; // add bet
            }
            else if (*player[0] == *player[1])
            {
                // If player 1 and player 2 are tied, print that both players drew the same number of points and that
                // there is no winner. In doing this comparison, use the == operator.
                std::cout << "Both players drew the same number of points. There is no winner" << std::endl;
            }
            else if (*player[0] > *player[1]) // PRINTING WINNER
            {
                // If player 1 has more points than player 2, then print the name of player 1 and that (s)he has won.
                std::cout << player[0]->getName() << " has won!" << std::endl;
                // Move the amount that was bet away from player 2 and towards player 1 using the << and >> operators.
                // In doing this comparison, use the > operator
                *player[1] >> bet; // minus bet
                *player[0] << bet; // add bet
            }
             else if (*player[1] > *player[0]){
                // If player 2 has more points than player 1, then print the name of player 2 and that (s)he has won.
                std::cout << player[1]->getName() << " has won!" << std::endl;
                // Move the amount that was bet away from player 1 and towards player 2 using the << and >> operators.
                // In doing this comparison, use the < operator
                *player[0] >> bet; // minus bet
                *player[1] << bet; // add bet
            };

            std::cout << std::endl;

            // ===========FINAL SUMMARIZATION=================

            // Report the name and cash for each
            for (int k = 0; k < NUM; ++k)
            {
                std::cout << player[k]->getName() << " has $" << player[k]->getCash() << "." << std::endl;
            };

            std::cout << std::endl;

            // ===========CHECK GAME QUIT=================

            // Determine whether it is time to quit by checking to see if one player has run out of cash
            if (player[0]->getCash() <= 0 || player[1]->getCash() <= 0)
            {
                gameOver = true;
            };
        } while (!gameOver);

        std::cout << "The game is over." << std::endl;

        for (int l = 0; l < NUM; ++l)
        {
            std::cout << std::fixed;
            std::cout << std::setprecision(2);
            std::cout << player[l]->getName() << " has $" << player[l]->getCash() << std::endl;
        };
        // Be sure to clean up before finishing the program. - done in main
    };
};

CardGameAdapter *cardGame()
{
    char gameMode;
    std::cout << "Would you like to play in low definition mode? [Y/N] ";
    std::cin >> gameMode;
    CardGameAdapter *playerGr = nullptr;
    if (gameMode == 'Y' || gameMode == 'y')
    {
        std::cout << "You will be playing in low definition mode." << std::endl;
        playerGr = new CardGame<int>(); // low def game
        playerGr->setMode(1);           // set game mode
    }
    else
    {
        std::cout << "You will be playing in high definition mode." << std::endl;
        playerGr = new CardGame<double>(); // high def game
        playerGr->setMode(0);              // set game mode
    };
    return playerGr;
}

#endif //_CardGame_H_
