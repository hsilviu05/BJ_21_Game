#include "CardFormatter.h"

std::string CardFormatter::RankToString(CardRank rank)
{
    switch (rank)
    {
        case CardRank::Two:   return "2";
        case CardRank::Three: return "3";
        case CardRank::Four:  return "4";
        case CardRank::Five:  return "5";
        case CardRank::Six:   return "6";
        case CardRank::Seven: return "7";
        case CardRank::Eight: return "8";
        case CardRank::Nine:  return "9";
        case CardRank::Ten:   return "10";
        case CardRank::Jack:  return "Jack";
        case CardRank::Queen: return "Queen";
        case CardRank::King:  return "King";
        case CardRank::Ace:   return "Ace";
    }
    return "Unknown";
}

std::string CardFormatter::SuitToString(CardSuit suit)
{
    switch (suit)
    {
        case CardSuit::Hearts:   return "Hearts";
        case CardSuit::Diamonds: return "Diamonds";
        case CardSuit::Clubs:    return "Clubs";
        case CardSuit::Spades:   return "Spades";
    }
    return "Unknown";
}

std::string CardFormatter::CardToString(const CardData& card)
{
    return RankToString(card.rank) + " of " + SuitToString(card.suit);
}