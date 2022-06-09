#include <gtest/gtest.h>
#include <string>
#include "GameplayFaçade.h"

const int maxDay = 47;
const int maxDistance = 6700;
const int playerBaseHp = 100;
const int boatBaseHp = 200;
const int baseMaterials = 10;

TEST(TestGameplayFaçade, TestFishing) {
    int token_nb = 2;
    GameplayFaçade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    int fish_ref = f.getFishCount();
    f.executeFishingAction(2);
    EXPECT_TRUE(f.getFishCount() >= fish_ref);
}

TEST(TestFaçade, TestRowing) {
    int token_nb = 2;
    GameplayFaçade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    f.executeRowingAction(2);
    EXPECT_TRUE(f.getDistanceTravelled() >= 0);
}

TEST(TestGameplayFaçade, TestHealing) {
    int token_nb = 2;
    GameplayFaçade f(maxDay, maxDistance, playerBaseHp/2, playerBaseHp, boatBaseHp/2, boatBaseHp, baseMaterials);
    f.executeHealingAction(2);
    EXPECT_EQ(f.getPlayerHp(), playerBaseHp/2 + 40);
}

TEST(TestGameplayFaçade, TestRepairing) {
    int token_nb = 2;
    GameplayFaçade f(maxDay, maxDistance, playerBaseHp / 2, playerBaseHp, boatBaseHp / 2, boatBaseHp, baseMaterials);
    f.executeRepairAction(2);
    EXPECT_EQ(f.getBoatHp(), boatBaseHp/2 + 40);
}

TEST(TestGameplayFaçade, TestStormEvent) {
    GameplayFaçade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    int fish_ref = f.getFishCount();
    int boat_HP_ref = f.getBoatHp();
    f.executeStormEvent();
    EXPECT_TRUE(f.getFishCount() < fish_ref);
    EXPECT_TRUE(f.getBoatHp() < boat_HP_ref);
}

TEST(TestGameplayFaçade, TestWindEvent) {
    GameplayFaçade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    f.moveBack(-100);
    f.executeWindEvent();
    EXPECT_TRUE(f.getDistanceTravelled() < 100);
}

TEST(TestGameplayFaçade, TestSeagullEvent) {
    GameplayFaçade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    int fish_ref = f.getFishCount();
    int player_HP_ref = f.getPlayerHp();
    f.executeSeagullEvent();
    EXPECT_TRUE(f.getFishCount() < fish_ref);
    EXPECT_TRUE(f.getPlayerHp() < player_HP_ref);
}

TEST(TestGameplayFaçade, TestMaterialEvent) {
    GameplayFaçade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    int material_ref = f.getMaterials();
    f.executeMaterialEvent();
    EXPECT_TRUE(f.getMaterials() > material_ref);
}

/*
Dans ce test, on va tester le fonctionnement de la méthode nextday de la façade.
On exécutera ici 2 actions, pêcher et naviguer.
*/
TEST(TestGameplayFaçade, TestNextDay1) {
    std::map<TokensType, int> tokens;
    tokens[TokensType::fishingsTokens] = 2;
    tokens[TokensType::rowingTokens] = 3;
    GameplayFaçade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    int d_ref = 0;
    int f_ref = f.getFishCount();
    int mat_ref = f.getMaterials();
    auto s = f.nextDay(tokens);
    EXPECT_TRUE(f.getDistanceTravelled() >= d_ref);
    EXPECT_TRUE(f.getFishCount() >= 0);
    EXPECT_FALSE(f.getFishingUpgradeStatus());
    EXPECT_FALSE(f.getRowingUpgradeStatus());

}

/*
Dans ce test, on va essayer d'améliorer la pêche alors que nous n'avons pas assez de matériaux
On vérifiera donc que l'on à bien pas amélioré la pêche au jour suivant.
*/
TEST(TestGameplayFaçade, TestNextDay2) {
    std::map<TokensType, int> tokens;
    tokens[TokensType::fishingsTokens] = 2;
    tokens[TokensType::rowingTokens] = 2;
    tokens[TokensType::upgradeFishingToken] = 1;
    GameplayFaçade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    int mat_ref = f.getMaterials();
    auto s = f.nextDay(tokens);
    EXPECT_TRUE(f.getDistanceTravelled() >= 0);
    EXPECT_TRUE(f.getFishCount() >= 0);
    EXPECT_FALSE(f.getFishingUpgradeStatus());
    EXPECT_FALSE(f.getRowingUpgradeStatus());
    EXPECT_TRUE(f.getMaterials() >= mat_ref);
}

TEST(TestGameplayFaçade, TestNextDay3) {
    std::map<TokensType, int> tokens;
    tokens[TokensType::fishingsTokens] = 2;
    tokens[TokensType::rowingTokens] = 2;
    tokens[TokensType::upgradeFishingToken] = 1;
    GameplayFaçade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials*10);
    int mat_ref = f.getMaterials();
    auto s = f.nextDay(tokens);
    EXPECT_TRUE(f.getDistanceTravelled() >= 0);
    EXPECT_TRUE(f.getFishCount() >= 0);
    EXPECT_TRUE(f.getFishingUpgradeStatus());
    EXPECT_FALSE(f.getRowingUpgradeStatus());
    EXPECT_EQ(f.getMaterials(), mat_ref - rod_materials_required);
}



