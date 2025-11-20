#include <gtest/gtest.h>
#include "../BlackjackLib/Hand.h"
#include "../BlackjackLib/Card.h"

// Test: Mână goală
TEST(HandTest, EmptyHandHasZeroValue)
{
    Hand hand;
    EXPECT_EQ(hand.GetValue(), 0);
}

// Test: O singură carte
TEST(HandTest, SingleCardValue)
{
    Hand hand;
    hand.AddCard(Card(CardRank::Five, CardSuit::Hearts));
    EXPECT_EQ(hand.GetValue(), 5);
}

// Test: AS + King = 21 (Blackjack)
TEST(HandTest, AceAndKingEquals21)
{
    Hand hand;
    hand.AddCard(Card(CardRank::Ace, CardSuit::Hearts));
    hand.AddCard(Card(CardRank::King, CardSuit::Spades));
    EXPECT_EQ(hand.GetValue(), 21);
}

// Test: AS + King + 5 = 16 (AS devine 1)
TEST(HandTest, AceAdjustsTo1WhenBust)
{
    Hand hand;
    hand.AddCard(Card(CardRank::Ace, CardSuit::Hearts));
    hand.AddCard(Card(CardRank::King, CardSuit::Spades));
    hand.AddCard(Card(CardRank::Five, CardSuit::Clubs));
    EXPECT_EQ(hand.GetValue(), 16); // AS = 1, King = 10, 5 = 5
}

// Test: AS + AS + 9 = 21 (un AS = 11, altul = 1)
TEST(HandTest, MultipleAcesAdjustment)
{
    Hand hand;
    hand.AddCard(Card(CardRank::Ace, CardSuit::Hearts));
    hand.AddCard(Card(CardRank::Ace, CardSuit::Diamonds));
    hand.AddCard(Card(CardRank::Nine, CardSuit::Spades));
    EXPECT_EQ(hand.GetValue(), 21); // 11 + 1 + 9
}

// Test: AS + AS + AS + 8 = 21 (toți AS-ii = 1)
TEST(HandTest, ThreeAcesAdjustment)
{
    Hand hand;
    hand.AddCard(Card(CardRank::Ace, CardSuit::Hearts));
    hand.AddCard(Card(CardRank::Ace, CardSuit::Diamonds));
    hand.AddCard(Card(CardRank::Ace, CardSuit::Clubs));
    hand.AddCard(Card(CardRank::Eight, CardSuit::Spades));
    EXPECT_EQ(hand.GetValue(), 11); // 1 + 1 + 1 + 8
}

// Test: Bust cu cărți normale
TEST(HandTest, BustOver21)
{
    Hand hand;
    hand.AddCard(Card(CardRank::King, CardSuit::Hearts));
    hand.AddCard(Card(CardRank::Queen, CardSuit::Diamonds));
    hand.AddCard(Card(CardRank::Five, CardSuit::Spades));
    EXPECT_GT(hand.GetValue(), 21); // 10 + 10 + 5 = 25
}

// Test: Clear resetează mâna
TEST(HandTest, ClearResetsHand)
{
    Hand hand;
    hand.AddCard(Card(CardRank::King, CardSuit::Hearts));
    hand.AddCard(Card(CardRank::Queen, CardSuit::Diamonds));
    hand.Clear();
    EXPECT_EQ(hand.GetValue(), 0);
}

// Test: ToData returnează structura corectă
TEST(HandTest, ToDataReturnsCorrectStructure)
{
    Hand hand;
    hand.AddCard(Card(CardRank::Seven, CardSuit::Hearts));
    hand.AddCard(Card(CardRank::Eight, CardSuit::Clubs));

    HandData data = hand.ToData();
    EXPECT_EQ(data.cards.size(), 2);
    EXPECT_EQ(data.value, 15);
    EXPECT_EQ(data.cards[0].rank, CardRank::Seven);
    EXPECT_EQ(data.cards[1].rank, CardRank::Eight);
}

// Test: GetCard cu index valid
TEST(HandTest, GetCardValidIndex)
{
    Hand hand;
    hand.AddCard(Card(CardRank::Jack, CardSuit::Diamonds));

    Card card = hand.GetCard(0);
    EXPECT_EQ(card.GetValue(), 10);
}

// Test: GetCard cu index invalid aruncă excepție
TEST(HandTest, GetCardInvalidIndexThrows)
{
    Hand hand;
    hand.AddCard(Card(CardRank::Jack, CardSuit::Diamonds));

    EXPECT_THROW(hand.GetCard(5), std::out_of_range);
}