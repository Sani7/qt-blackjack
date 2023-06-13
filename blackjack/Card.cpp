#include "Card.hpp"

Card::Card(Rank rank, Suit suit) : rank_(rank), suit_(suit) {}

Card::Rank Card::getRank() const
{
    return rank_;
}
Card::Suit Card::getSuit() const
{
    return suit_;
}

std::string Card::rank_to_string(void) const
{
    std::string rank;
    switch (rank_)
    {
    case Rank::ACE:
        rank = "Ace";
        break;
    case Rank::TWO:
        rank = "Two";
        break;
    case Rank::THREE:
        rank = "Three";
        break;
    case Rank::FOUR:
        rank = "Four";
        break;
    case Rank::FIVE:
        rank = "Five";
        break;
    case Rank::SIX:
        rank = "Six";
        break;
    case Rank::SEVEN:
        rank = "Seven";
        break;
    case Rank::EIGHT:
        rank = "Eight";
        break;
    case Rank::NINE:
        rank = "Nine";
        break;
    case Rank::TEN:
        rank = "Ten";
        break;
    case Rank::JACK:
        rank = "Jack";
        break;
    case Rank::QUEEN:
        rank = "Queen";
        break;
    case Rank::KING:
        rank = "King";
        break;
    case Rank::end:
    default:
        rank = "Invalid";
        break;
    }

    return rank;
}

std::string Card::suit_to_string() const
{
    std::string suit;
    switch (suit_)
    {
    case Suit::HEARTS:
        suit = "Hearts";
        break;
    case Suit::DIAMONDS:
        suit = "Diamonds";
        break;
    case Suit::CLUBS:
        suit = "Clubs";
        break;
    case Suit::SPADES:
        suit = "Spades";
        break;
    case Suit::end:
    default:
        suit = "Invalid";
        break;
    }
    return suit;
}

std::string Card::to_string() const
{
    return rank_to_string() + " of " + suit_to_string();
}

bool Card::operator==(const Card &other) const
{ return (rank_ == other.getRank()
            && suit_ == other.getSuit());
}
