#pragma once

#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#include "Card.h"

class Deck
{
    private:
		std::vector<Card> cards;
    const int DECKS_IN_PLAY = 4;

    public:
      Deck();
      void Shuffle();
      Card DrawCard();
      int GetCardCount() const;
      void Reset();
};

