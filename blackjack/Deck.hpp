#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <random>

#include "Card.hpp"
#include "IterableEnum.hpp"

class Deck
{
public:
    Deck(void);

    void shuffledeck(void);
    std::unique_ptr<Card> drawCard();

private:
    std::vector<std::unique_ptr<Card>> cards_;
};
