#include <gtest/gtest.h>
#include <string>
#include "Façade.h"

const int maxDay = 47;
const int maxDistance = 6700;
const int playerBaseHp = 100;
const int boatBaseHp = 200;

TEST(TestFacade, TestFishingAndRowing) {
    int token_nb = 2;
    Façade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp);
    f.executeFishingAction(2);
    f.executeRowingAction(2);
    EXPECT_EQ(f.getFishCount(), 4);
    EXPECT_EQ(f.getDistanceTravelled(), 200);
}

TEST(TestFacade, TestHealingAndRepair) {
    int token_nb = 2;
    Façade f(maxDay, maxDistance, playerBaseHp/2, playerBaseHp, boatBaseHp/2, boatBaseHp);
    f.executeHealingAction(2);
    f.executeRepairAction(2);
    EXPECT_EQ(f.getPlayerHp(), 90);
    EXPECT_EQ(f.getBoatHp(), 140);

}

TEST(TestFacade, TestEvent) {
    EXPECT_TRUE(true);
}



