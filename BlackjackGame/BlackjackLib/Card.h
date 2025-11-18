#pragma once

#include "CardRank.h"
#include "CardSuit.h"
#include "CardData.h"

#include <stdexcept>
class Card
{
	private:
	   CardRank m_rank;
	   CardSuit m_suit;
    public:
		Card(CardRank rank, CardSuit suit) : m_rank(rank), m_suit(suit) {}
		int GetValue() const;
		CardData ToData() const;

};

