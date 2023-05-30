// PlayerYouth.h - definition for Player Youth template class

//Ibeh Mary-Anne
//20-03-2023

#ifndef PLAYER_YOUTH_
#define PLAYER_YOUTH_

#include "PlayerBase.h"

template <typename T>
class PlayerYouth : public PlayerBase<T>
{
        // The youth player has a list of attack cards which can be integral (regular mode) or decimal (high definition mode).
        std::vector<T> attackCards; // The youth player's attack cards have a value between 1 and 10 inclusive.// The youth player's high definition attack cards will have values to three decimal places.
public:
        PlayerYouth() {}
        // The youth player can be created with no attack cards.
        ~PlayerYouth(){}; // The youth player cleans itself up before destruction.

        PlayerYouth(std::string _name)
        {
                this->setName(_name);
                //        attackCards(0);
        }; // The youth player can be created with a name passed by argument and no attack cards.

        PlayerYouth(const PlayerBase<T> &player2)
        {
            if (typeid(*this) == typeid(player2))
            {
                this->setName(player2.getName());
                this->setCash(player2.getCash());
                this->setDependentCards(player2.getDependentCard());
                attackCards = player2.getAttackCard();

            }  else   std::cout << "Not the same type";
        }; // The youth player can be created from another youth player.

        PlayerYouth &operator=(const PlayerBase<T> &player2)
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
        } // The youth player can be assigned all its data from another youth player through the = operator.

        std::vector<T> getAttackCard() const { return attackCards; };

        void addCard(T _card)
        {
                attackCards.push_back(_card);
        }; // The youth player provides a function to add one attack card to an existing list of attack cards.

        void addCards(std::vector<T> _addCards)
        {
                if (attackCards.size() > 0)
                        attackCards.clear();
                attackCards = {_addCards}; // ASSIGN LOCAL VECTOR TO ARGUMENT VECTOR
        };
        // The youth player provides a function to add attack cards, deleting any existing list of attack cards first.
        void addCash(double _cash)
        {
                this->cash += _cash;
        };

        T sumCards() const
        {
                T sumAttack = 0;
                for (auto &i : attackCards)
                {
                        sumAttack += i;
                };
                return sumAttack;
        }; // The youth player provides a function to sum the attack cards.

        T sumAllCards() const
        {
                T sumAttack = sumCards();
                int sumDependent = this->sumDependentCards();
                T sumALL = sumAttack - T(sumDependent);
                return sumALL;
                // The youth player provides a function to sum all cards (sum the attack cards minus sum the dependent cards).
        };
    bool operator==(const PlayerBase<T> &player2) const
    {
        // player1 ==player2
        if (this->sumAllCards() == (player2.sumAllCards()))      { return true;};
        return false;
    };

        bool operator<(const PlayerBase<T> &player2) const
        {
                // palyer1<player2
                    if (this->sumAllCards() < (player2.sumAllCards()))   {return true;} ;
                return false;
        };
        bool operator>(const PlayerBase<T> &player2) const
        {
                // player1 >player2
                        if (this->sumAllCards() > (player2.sumAllCards())){return true;};
            return false;
        }
        void operator<<(double _cash)
        {
                // ADD CASH
                addCash(_cash);
        };
        void operator>>(double _cash)
        {
                // MINUS CASH
                addCash(-(_cash));
        }
};
#endif // PLAYER_YOUTH_