#include "Deck.h"



Deck::Deck()
{
    CardSuit suits[] = { 
        CardSuit::Hearts, CardSuit::Diamonds, CardSuit::Clubs, CardSuit::Spades 
    };

    CardRank ranks[] = { 
        CardRank::Two, CardRank::Three, CardRank::Four, CardRank::Five, 
        CardRank::Six, CardRank::Seven, CardRank::Eight, CardRank::Nine, 
        CardRank::Ten, CardRank::Jack, CardRank::Queen, CardRank::King, 
        CardRank::Ace 
    };
    for (int deck = 0; deck < DECKS_IN_PLAY; ++deck)
    {
        for (const auto& suit : suits)
        {
            for (const auto& rank : ranks)
            {
                cards.emplace_back(rank, suit); 
            }
        }
    }
}

void Deck::Shuffle()
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto rng = std::default_random_engine(seed);
    std::shuffle(cards.begin(), cards.end(), rng);
}

Card Deck::DrawCard()
{
    if(cards.empty())
    {
        throw std::runtime_error("No cards left in the deck");
    }

    Card cardToDraw = cards.back();
    cards.pop_back();
    return cardToDraw;
}

int Deck::GetCardCount() const
{
    return static_cast<int>(cards.size());
}

void Deck::Reset()
{
    cards.clear();
    CardSuit suits[] = { 
        CardSuit::Hearts, CardSuit::Diamonds, CardSuit::Clubs, CardSuit::Spades 
    };

    CardRank ranks[] = { 
        CardRank::Two, CardRank::Three, CardRank::Four, CardRank::Five, 
        CardRank::Six, CardRank::Seven, CardRank::Eight, CardRank::Nine, 
        CardRank::Ten, CardRank::Jack, CardRank::Queen, CardRank::King, 
        CardRank::Ace 
    };
    
    for (int deck = 0; deck < DECKS_IN_PLAY; ++deck)
    {
        for (const auto& suit : suits)
        {
            for (const auto& rank : ranks)
            {
                cards.emplace_back(rank, suit); 
            }
        }
    }
}