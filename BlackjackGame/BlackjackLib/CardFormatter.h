#pragma once
#include "CardData.h"
#include <string>

class CardFormatter
{
public:
    static std::string RankToString(CardRank rank);
    static std::string SuitToString(CardSuit suit);
    static std::string CardToString(const CardData& card);
};