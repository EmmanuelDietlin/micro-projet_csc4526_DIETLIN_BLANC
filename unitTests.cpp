#include <gtest/gtest.h>
#include <string>
#include "Façade.h"

const int maxDay = 47;
const int maxDistance = 6700;
const int playerBaseHp = 100;
const int boatBaseHp = 200;
const int baseMaterials = 100;

TEST(TestFaçade, TestFishing) {
    int token_nb = 2;
    Façade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    int fish_ref = f.getFishCount();
    f.executeFishingAction(2);
    EXPECT_TRUE(f.getFishCount() >= fish_ref);
}

TEST(TestFaçade, TestRowing) {
    int token_nb = 2;
    Façade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    f.executeRowingAction(2);
    EXPECT_TRUE(f.getDistanceTravelled() >= 0);
}

TEST(TestFaçade, TestHealing) {
    int token_nb = 2;
    Façade f(maxDay, maxDistance, playerBaseHp/2, playerBaseHp, boatBaseHp/2, boatBaseHp, baseMaterials);
    f.executeHealingAction(2);
    EXPECT_EQ(f.getPlayerHp(), playerBaseHp/2 + 40);
}

TEST(TestFaçade, TestRepairing) {
    int token_nb = 2;
    Façade f(maxDay, maxDistance, playerBaseHp / 2, playerBaseHp, boatBaseHp / 2, boatBaseHp, baseMaterials);
    f.executeRepairAction(2);
    EXPECT_EQ(f.getBoatHp(), boatBaseHp/2 + 40);
}

TEST(TestFaçade, TestStormEvent) {
    Façade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    int fish_ref = f.getFishCount();
    int boat_HP_ref = f.getBoatHp();
    f.executeStormEventForTest();
    EXPECT_TRUE(f.getFishCount() < fish_ref);
    EXPECT_TRUE(f.getBoatHp() < boat_HP_ref);
}

TEST(TestFaçade, TestWindEvent) {
    Façade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    f.moveBack(-100);
    f.executeWindEventForTest();
    EXPECT_TRUE(f.getDistanceTravelled() < 100);
}

TEST(TestFaçade, TestSeagullEvent) {
    Façade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    int fish_ref = f.getFishCount();
    int player_HP_ref = f.getPlayerHp();
    f.executeSeagullEventForTest();
    EXPECT_TRUE(f.getFishCount() < fish_ref);
    EXPECT_TRUE(f.getPlayerHp() < player_HP_ref);
}

TEST(TestFaçade, TestMaterialEvent) {
    Façade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    int material_ref = f.getMaterials();
    f.executeMaterialEventForTest();
    EXPECT_TRUE(f.getMaterials() > material_ref);
}

TEST(TestFaçade, TestNextDay1) {
    std::map<TokensType, int> tokens;
    tokens[TokensType::fishingsTokens] = 2;
    tokens[TokensType::rowingTokens] = 3;
    Façade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    int d_ref = 0;
    int f_ref = f.getFishCount();
    int mat_ref = f.getMaterials();
    auto s = f.nextDay(tokens);
    EXPECT_TRUE(f.getDistanceTravelled() >= d_ref);
    EXPECT_TRUE(f.getFishCount() >= 0);
    EXPECT_FALSE(f.getFishingUpgradeStatus());
    EXPECT_FALSE(f.getRowingUpgradeStatus());
    EXPECT_EQ(f.getMaterials(), mat_ref);
}

TEST(TestFaçade, TestNextDay2) {
    //faire le test mais cette fois en essayant d'améliorer mais pas assez de matériaux
}

TEST(TestFaçade, TestNextDay3) {
    //Faire le test avec assez de matériaux pour améliorer
}



