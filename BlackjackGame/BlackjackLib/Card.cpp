#include "Card.h"

int Card::GetValue() const
{
    switch (m_rank)
    {
        case CardRank::Jack:
        case CardRank::Queen:
		case CardRank::King:
			return 10;
		default:
			return static_cast<int>(m_rank);

    }
};

CardData Card::ToData() const
{
	return CardData{ m_rank, m_suit };
}
