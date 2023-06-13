#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <ctime>
#include <algorithm> // for "shuffle"

#include "IterableEnum.hpp"

class Card
{
public:
    ITERABLE_ENUM_BEGIN(Rank)
        ACE = 1,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        QUEEN,
        KING
    ITERABLE_ENUM_END;

    ITERABLE_ENUM_BEGIN(Suit)
        HEARTS,
        DIAMONDS,
        CLUBS,
        SPADES
    ITERABLE_ENUM_END;

    Card(Rank rank, Suit suit);

    Rank getRank() const;
    Suit getSuit() const;

    std::string rank_to_string() const;
    std::string suit_to_string() const;
    std::string to_string() const;

    bool operator==(const Card &other) const;

private:
    Rank rank_;
    Suit suit_;
};
