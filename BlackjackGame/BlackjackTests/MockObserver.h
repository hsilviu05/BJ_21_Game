#pragma once
#include <gmock/gmock.h>
#include "../BlackjackLib/IGameObserver.h"

class MockObserver : public IGameObserver
{
public:
    MOCK_METHOD(void, OnGameStarted, (const HandData& playerHand, const HandData& dealerHand), (override));
    MOCK_METHOD(void, OnPlayerHandChanged, (const HandData& playerHand), (override));
    MOCK_METHOD(void, OnDealerHandChanged, (const HandData& dealerHand), (override));
    MOCK_METHOD(void, OnGameEnded, (GameState state, const HandData& finalPlayerData, const HandData& finalDealerData), (override));
    MOCK_METHOD(void, OnPlayerTurnBegan, (), (override));
};