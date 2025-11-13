#include "Hand.h"

void Hand::AddCard(const Card& card)
{
	cards.push_back(card);
}

int Hand::GetValue() const
{
	int total = 0;
	int aceCount = 0;
	for (const auto& card : cards)
	{
		total += card.GetValue();
		if (card.ToData().rank == CardRank::Ace)
		{
			aceCount++;
		}
	}
	while (total > 21 && aceCount > 0)
	{
		total -= 10;
		aceCount--;
	}
	return total;
}


void Hand::Clear()
{
	cards.clear();
}

HandData Hand::ToData() const
{
	HandData data;
	for (const auto& card : cards)
	{
		data.cards.push_back(card.ToData());
	}
	data.value = GetValue();
	return data;
}
