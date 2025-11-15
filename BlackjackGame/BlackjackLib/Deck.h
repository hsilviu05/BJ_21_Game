#pragma once

#include <vector>
#include <algorithm>
#include <random>

#include "Card.h"

class Deck
{
    private:
		std::vector<Card> cards;

    public:
      Deck();
      void Shuffle();
      Card DrawCard();

};

