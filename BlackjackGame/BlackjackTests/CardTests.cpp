#include <gtest/gtest.h>
#include "../BlackjackLib/Card.h"

//Cărți numerice au valorile corecte
TEST(CardTest, NumericCardsHaveCorrectValues)
{
    EXPECT_EQ(Card(CardRank::Two, CardSuit::Hearts).GetValue(), 2);
    EXPECT_EQ(Card(CardRank::Five, CardSuit::Diamonds).GetValue(), 5);
    EXPECT_EQ(Card(CardRank::Nine, CardSuit::Clubs).GetValue(), 9);
}

//Figurile au valoarea 10
TEST(CardTest, FaceCardsValueTen)
{
    EXPECT_EQ(Card(CardRank::Jack, CardSuit::Hearts).GetValue(), 10);
    EXPECT_EQ(Card(CardRank::Queen, CardSuit::Diamonds).GetValue(), 10);
    EXPECT_EQ(Card(CardRank::King, CardSuit::Clubs).GetValue(), 10);
    EXPECT_EQ(Card(CardRank::Ten, CardSuit::Spades).GetValue(), 10);
}

//AS are valoarea 11 inițial
TEST(CardTest, AceValueIsEleven)
{
    EXPECT_EQ(Card(CardRank::Ace, CardSuit::Hearts).GetValue(), 11);
}

// ToData returnează structura corectă
TEST(CardTest, ToDataReturnsCorrectData)
{
    Card card(CardRank::Seven, CardSuit::Diamonds);
    CardData data = card.ToData();

    EXPECT_EQ(data.rank, CardRank::Seven);
    EXPECT_EQ(data.suit, CardSuit::Diamonds);
}