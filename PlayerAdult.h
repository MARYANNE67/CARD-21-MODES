// PlayerAdult.h - definition for Player Adult template class

//Ibeh Mary-Anne
//20-03-2023

#ifndef PLAYER_ADULT_
#define PLAYER_ADULT_

#include "PlayerBase.h"
template <typename T>
class PlayerAdult : public PlayerBase<T>
{
private:
    std::vector<T> attackCards;

public:
    PlayerAdult() {}  // The adult player can be created with no attack cards.
    ~PlayerAdult() {} // The adult player cleans itself up before destruction.
    PlayerAdult(std::string _name)
    {
        this->setName(_name);
        // attackCards(0);
    }; // The adult player can be created with a name passed by argument and no attack cards.

     PlayerAdult(const PlayerBase<T> &player2)
    {
        if (typeid(*this) == typeid(player2))
        {
        this->setName(player2.getName());
        this->setCash(player2.getCash());
        this->setDependentCards(player2.getDependentCard());
        attackCards = player2.getAttackCard();

        }   else   std::cout << "Not the same type";
    } // The adult player can be created from another adult player.

    PlayerAdult &operator=(const PlayerBase<T> &player2)
    {
        if (typeid(*this) == typeid(player2))
        {
            if (this != &player2)
            {
                this->setName(player2.getName());
                this->setCash(player2.getCash());
                this->setDependentCards(player2.getDependentCard());
                attackCards = player2.getAttackCard();
            }
        }  else   std::cout << "Not the same type";

        return *this;
    }; // The adult player can be assigned all its data from another adult player through the = operator.

    std::vector<T> getAttackCard() const { return attackCards; };
    void addCard(T _card)
    {
        attackCards.push_back(_card);
    } // The adult player provides a function to add one attack card to an existing list of attack cards.
    void addCards(std::vector<T> _addAcards)
    {
        if (attackCards.size() > 0)
            attackCards.clear();
        attackCards = {_addAcards};
    }; // The adult player provides a function to add attack cards, deleting any existing list of attack cards first.

    T sumCards() const
    {
        T sumAttack = 0;
        for (auto &i : attackCards)
        {
            sumAttack += i;
        };
        return sumAttack;
    };
    // The adult player provides a function to sum the attack cards.
    T sumAllCards() const
    {
        T sumAttack = sumCards();
        int sumDependent = this->sumDependentCards();
        T sumALL = sumAttack - T(sumDependent);
        return sumALL;
    }; // The adult player provides a function to sum all cards (sum the attack cards minus sum the dependent cards).

    void addCash(double _cash)
    {
        this->cash += _cash;
    };
    bool operator==(const PlayerBase<T> &player2) const
    {
        // player1 ==player2
        if (this->sumAllCards() == (player2.sumAllCards()))       return true;
        return false;
    };

    bool operator<(const PlayerBase<T> &player2) const
    {
        // palyer1<player2
        if (this->sumAllCards() < (player2.sumAllCards()))    {return true;}
        return false;
    };

    bool operator>(const PlayerBase<T> &player2) const
    {
        // player1 >player2
        if (this->sumAllCards() > (player2.sumAllCards()))  {return true;}
        return false;
    };

    void operator<<(double _cash)
    {
        // ADD CASH
        this->addCash(_cash);
    };

    void operator>>(double _cash)
    {
        // MINUS CASH
        this->addCash(-(_cash));
    }
};
#endif // PLAYER_ADULT_