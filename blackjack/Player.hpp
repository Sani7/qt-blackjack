#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <random>

#include "Card.hpp"

class Player
{
public:
    void addCard(std::unique_ptr<Card> card);

    Card getLastCard(void) const;
    int getHandValue() const;
    std::string getHandString() const;

private:
    std::vector<std::unique_ptr<Card>> hand_;
};
