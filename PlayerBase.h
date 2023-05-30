// PlayerBase.h - class declearation for Player Base


//Ibeh Mary-Anne
//20-03-2023

#ifndef PLAYER_BASE_
#define PLAYER_BASE_

#include <iostream>
#include <vector>

#define MAXSIZE 5

template <typename T>

class PlayerBase
{
protected:
    double cash;
    std::string name;                // Each player has a name.                  // // Each player has cash.
    std::vector<int> dependentCards; // Each player has a list of dependent cards which are always integral regardless of the game mode.
    // Each player's dependent cards have a value between 1 and 5 inclusive.
public:
    ~PlayerBase(){}; // // Each player cleans itself up before destruction.
    PlayerBase()
    {
        name = " ";
        cash = 1000.00;
        dependentCards = {0};
    };
    // Each player can be created with name set to an empty string, no dependent cards, and $1000.00 in cash.
    PlayerBase(std::string _name)
    {
        name = _name;
        cash = 1000.00;
        dependentCards = {0};
    }
    // Each player can be created with name passed by argument, no dependent cards, and $1000.00 in cash.

    PlayerBase(const PlayerBase &player2) {
            setName(player2.getName());
            setCash(player2.getCash());
            setDependentCards(player2.getDependentCard());
    }// // Each player can be created from another player.

     PlayerBase &operator=(const PlayerBase<T> &player2) {
        if (this != &player2)
        {
            setName(player2.getName());
            setCash(player2.getCash());
            setDependentCards(player2.getDependentCard());
        }
        return *this;
    };

    void addDependentCard(int _card) { dependentCards.push_back(_card); };
    // Each player provides a function to add one dependent card to an existing list of dependent cards.

    void addDependentCards(std::vector<int> _cards)
    {
        if (dependentCards.size() > 0)
            dependentCards.clear();
        dependentCards = {_cards};
    };
    // Each player provides a function to add dependent cards, deleting any existing list of dependent cards first.

    void setName(std::string _name) { name = _name; }; // Each player provides accessor functions to set name

    std::string getName() const { return name; }; // Each player provides accessor functions or get the name

    int sumDependentCards() const
    {
        int tempSumDependent = 0;
        for (auto &i : dependentCards)
        {
            tempSumDependent += i;
        };
        return tempSumDependent;
    }; // // Each player provides a function to sum the dependent cards.

    std::vector<int> getDependentCard() const { return dependentCards; };
    double getCash() const { return cash; }; // // Each player provides functions to get cash and .
    virtual void addCash(double _cash){};    // Each player provides functions to add cash (could be negative)

    void setCash(double _cash)
    {
        cash = _cash;
    }; // Each player provides functions to set cash;
    void setDependentCards(std::vector<int> _dependentCards)
    {
        dependentCards = _dependentCards;
    };
    // VIRTUAL FUNCTIONS - GOES TO THE DERIVE CLASS DEF
    virtual std::vector<T> getAttackCard() const = 0;

    virtual void addCards(std::vector<T> _attackCards) = 0;

    virtual void addCard(T _card) = 0;
    virtual T sumAllCards() const = 0;

    virtual bool operator==(const PlayerBase<T> &player2) const = 0;
    virtual bool operator<(const PlayerBase<T> &player2) const = 0;
    virtual bool operator>(const PlayerBase<T> &player2) const = 0;
    virtual void operator<<(double _cash) = 0;
    virtual void operator>>(double _cash) = 0;
};
#endif // PLAYER_BASE_
