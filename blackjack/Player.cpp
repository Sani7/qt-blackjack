#include "Player.hpp"

void Player::addCard(std::unique_ptr<Card> card)
{
    hand_.push_back(std::move(card));
}

Card Player::getLastCard(void) const
{
    return Card(hand_.back()->getRank(), hand_.back()->getSuit());
}

int Player::getHandValue() const
{
    int value = 0;
    int aces = 0;
    for (const auto &card : hand_)
    {
        int cardValue = (int)card->getRank();
        if (cardValue >= 10)
        {
            cardValue = 10;
        }
        else if (cardValue == (int)Card::Rank::ACE)
        {
            aces++;
            cardValue = 11;
        }
        value += cardValue;
    }

    while (value > 21 && aces > 0)
    {
        value -= 10;
        aces--;
    }
    return value;
}

std::string Player::getHandString() const
{
    std::string handString;
    for (const auto &card : hand_)
    {
        handString += card->to_string() + " ";
    }
    return handString;
}
