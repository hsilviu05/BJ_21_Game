#pragma once
#include<vector>
#include "Card.h"
#include "HandData.h"
class Hand
{
	private:
	   std::vector<Card> cards;
	public:
		void AddCard(const Card& card);
		int GetValue() const;
		void Clear();
		HandData ToData() const;



};

