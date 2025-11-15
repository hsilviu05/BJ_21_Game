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
    
    for (const auto& suit : suits)
    {
        for (const auto& rank : ranks)
        {
            cards.emplace_back(rank, suit); 
        }
    }
}

void Deck::Shuffle()
{
    auto rng = std::default_random_engine{};
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