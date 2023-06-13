#include "Deck.hpp"

Deck::Deck(void)
{
    for (Iterable<Card::Suit> suit; suit < Card::Suit::end; suit++)
    {
        for (Iterable<Card::Rank> rank = Card::Rank::ACE; rank < Card::Rank::end; rank++)
        {
            cards_.push_back(std::make_unique<Card>(rank.val(), suit.val()));
        }
    }
}

void Deck::shuffledeck(void)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards_.begin(), cards_.end(), g);
}

std::unique_ptr<Card> Deck::drawCard(void)
{
    if (cards_.empty())
    {
        return nullptr;
    }
    std::unique_ptr<Card> card = std::move(cards_.back());
    cards_.pop_back();
    return card;
}