#include <gtest/gtest.h>
#include "../BlackjackLib/Deck.h"

//Deck inițializat are 208 cărți (4 pachete × 52)
TEST(DeckTest, InitialDeckHas208Cards)
{
    Deck deck;
    EXPECT_EQ(deck.GetCardCount(), 208);
}

//DrawCard reduce numărul de cărți
TEST(DeckTest, DrawCardReducesCount)
{
    Deck deck;
    deck.DrawCard();
    EXPECT_EQ(deck.GetCardCount(), 207);
}

//DrawCard pe deck gol aruncă excepție
TEST(DeckTest, DrawFromEmptyDeckThrows)
{
    Deck deck;
    for (int i = 0; i < 208; i++)
    {
        deck.DrawCard();
    }

    EXPECT_THROW(deck.DrawCard(), std::runtime_error);
}

//Reset restaurează 208 cărți
TEST(DeckTest, ResetRestoresAllCards)
{
    Deck deck;

    // Trage 100 de cărți
    for (int i = 0; i < 100; i++)
    {
        deck.DrawCard();
    }

    EXPECT_EQ(deck.GetCardCount(), 108);

    deck.Reset();
    EXPECT_EQ(deck.GetCardCount(), 208);
}

//Shuffle randomizează ordinea cărților
TEST(DeckTest, ShuffleChangesOrder)
{
    Deck deck1;
    Deck deck2;

    Card card1_first = deck1.DrawCard();
    Card card2_first = deck2.DrawCard();

    // După shuffle, primele cărți ar trebui să fie diferite (probabilitate mare)
    deck1.Reset();
    deck1.Shuffle();

    Card card1_after_shuffle = deck1.DrawCard();

    // Verifică că cel puțin valorile sunt diferite (nu e garantat 100%, dar foarte probabil)
    bool different = (card1_first.GetValue() != card1_after_shuffle.GetValue()) ||
        (card1_first.ToData().suit != card1_after_shuffle.ToData().suit);

    // Acest test poate eșua rar din cauza randomizării, dar e util pentru verificare
     EXPECT_TRUE(different); 
}

// Deck conține toate cele 13 ranguri × 4 culori × 4 pachete
TEST(DeckTest, DeckContainsAllCards)
{
    Deck deck;

    int aceCount = 0;
    int kingCount = 0;
    int heartCount = 0;

    for (int i = 0; i < 208; i++)
    {
        Card card = deck.DrawCard();
        CardData data = card.ToData();

        if (data.rank == CardRank::Ace) aceCount++;
        if (data.rank == CardRank::King) kingCount++;
        if (data.suit == CardSuit::Hearts) heartCount++;
    }

    EXPECT_EQ(aceCount, 16);  // 4 pachete × 4 AS-i
    EXPECT_EQ(kingCount, 16); // 4 pachete × 4 Kingi
    EXPECT_EQ(heartCount, 52); // 4 pachete × 13 cărți Hearts
}