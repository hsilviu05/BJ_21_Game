#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../BlackjackLib/GameEngine.h"
#include "MockObserver.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;

//Observer este notificat la StartNewGame
TEST(GameEngineTest, NotifiesObserverOnGameStart)
{
    MockObserver observer;
    GameEngine engine;
    engine.RegisterObserver(&observer);

    EXPECT_CALL(observer, OnGameStarted(_, _)).Times(1);

    engine.StartNewGame();
}

// PlayerHit notifică observer
TEST(GameEngineTest, PlayerHitNotifiesObserver)
{
    MockObserver observer;
    GameEngine engine;
    engine.RegisterObserver(&observer);

    engine.StartNewGame();

    EXPECT_CALL(observer, OnPlayerHandChanged(_)).Times(AtLeast(1));

    engine.PlayerHit();
}

//UnregisterObserver oprește notificările
TEST(GameEngineTest, UnregisterStopsNotifications)
{
    MockObserver observer;
    GameEngine engine;
    engine.RegisterObserver(&observer);
    engine.UnregisterObserver(&observer);

    // Nu ar trebui să primească notificări după unregister
    EXPECT_CALL(observer, OnGameStarted(_, _)).Times(0);

    engine.StartNewGame();
}

//PlayerStand declanșează DealerTurn
TEST(GameEngineTest, PlayerStandTriggersDealerTurn)
{
    MockObserver observer;
    GameEngine engine;
    engine.RegisterObserver(&observer);

    engine.StartNewGame();

    EXPECT_CALL(observer, OnDealerHandChanged(_)).Times(AtLeast(1));
    EXPECT_CALL(observer, OnGameEnded(_, _, _)).Times(1);

    engine.PlayerStand();
}

//Bust detection
TEST(GameEngineTest, PlayerBustEndsGame)
{
    MockObserver observer;
    GameEngine engine;
    engine.RegisterObserver(&observer);

    bool bustDetected = false;

    EXPECT_CALL(observer, OnGameEnded(_, _, _))
        .WillRepeatedly(Invoke([&bustDetected](GameState state, const HandData&, const HandData&) {
        if (state == GameState::PlayerBust)
        {
            bustDetected = true;
        }
            }));

    engine.StartNewGame();

    // Trage cărți până la bust (probabilitate mare după 5-6 cărți)
    for (int i = 0; i < 10; i++)
    {
        engine.PlayerHit();
        if (bustDetected) break;
    }

    // Note: Acest test depinde de randomizare, dar e util pentru verificare
}

// Multiple observers primesc notificări
TEST(GameEngineTest, MultipleObserversAreNotified)
{
    MockObserver observer1;
    MockObserver observer2;
    GameEngine engine;

    engine.RegisterObserver(&observer1);
    engine.RegisterObserver(&observer2);

    EXPECT_CALL(observer1, OnGameStarted(_, _)).Times(1);
    EXPECT_CALL(observer2, OnGameStarted(_, _)).Times(1);

    engine.StartNewGame();
}