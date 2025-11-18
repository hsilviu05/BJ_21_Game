#include "Card.h"

int Card::GetValue() const
{
    switch (m_rank)
    {
        case CardRank::Two:   return 2;
        case CardRank::Three: return 3;
        case CardRank::Four:  return 4;
        case CardRank::Five:  return 5;
        case CardRank::Six:   return 6;
        case CardRank::Seven: return 7;
        case CardRank::Eight: return 8;
        case CardRank::Nine:  return 9;
        case CardRank::Ten:
        case CardRank::Jack:
        case CardRank::Queen:
        case CardRank::King:
            return 10;
        case CardRank::Ace:
            return 11;
    }
    throw std::logic_error("Invalid Card Rank");
}

CardData Card::ToData() const
{
	return CardData{ m_rank, m_suit };
}
