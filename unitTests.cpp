#include <gtest/gtest.h>
#include <string>
#include "GameplayFa�ade.h"

const int maxDay = 47;
const int maxDistance = 6700;
const int playerBaseHp = 100;
const int boatBaseHp = 200;
const int baseMaterials = 100;

/*
Test de la p�che lorsque le joueur est au-dessus de 50% de pv
*/
TEST(TestGameplayFa�ade, TestFishing1) {
    int token_nb = 1;
    GameplayFa�ade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    int fish_ref = f.getFishCount();
    f.executeFishingAction(token_nb);
    EXPECT_TRUE(f.getFishCount() >= fish_ref);
}

/*
Test de la p�che lorsque le joueur est en dessous de 50% de pv
On utilise qu'un seul token, donc normalement aucun poisson ne devrait �tre p�ch�
*/
TEST(TestGameplayFa�ade, TestFishing2) {
    int token_nb = 1;
    GameplayFa�ade f(maxDay, maxDistance, playerBaseHp * 0.25, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    int fish_ref = f.getFishCount();
    f.executeFishingAction(token_nb);
    EXPECT_EQ(f.getFishCount(), fish_ref);
}

/*
Test de la navigation lorsque le bateau est au-dessus de 50% de pv
*/
TEST(TestGameplayFa�ade, TestRowing1) {
    int token_nb = 1;
    GameplayFa�ade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    int dist_ref = f.getDistanceTravelled();
    f.executeRowingAction(token_nb);
    EXPECT_TRUE(f.getDistanceTravelled() >= dist_ref);
}

/*
Test de la navigation lorsque le bateau est en dessous de 50% de pv.
On utilise qu'un seul jeton, donc normalement la distance parcourue ne devrait pas augmenter
*/
TEST(TestGameplayFa�ade, TestRowing2) {
    int token_nb = 1;
    GameplayFa�ade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp*0.25, boatBaseHp, baseMaterials);
    int dist_ref = f.getDistanceTravelled();
    f.executeRowingAction(token_nb);
    EXPECT_EQ(f.getDistanceTravelled(), dist_ref);
}

TEST(TestGameplayFa�ade, TestHealing) {
    int token_nb = 2;
    GameplayFa�ade f(maxDay, maxDistance, playerBaseHp/2, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    f.executeHealingAction(token_nb);
    EXPECT_EQ(f.getPlayerHp(), 80);
}

TEST(TestGameplayFa�ade, TestRepairing) {
    int token_nb = 2;
    GameplayFa�ade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp / 2, boatBaseHp, baseMaterials);
    f.executeRepairAction(token_nb);
    EXPECT_EQ(f.getBoatHp(), 130);
}

TEST(TestGameplayFa�ade, TestUpgradeRowingAction) {
    int token_nb = 1;
    GameplayFa�ade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    f.executeUpgradeRowingAction(token_nb);
    EXPECT_TRUE(f.getRowingUpgradeStatus());
    EXPECT_EQ(f.getMaterials(), baseMaterials - boat_materials_required);
}

TEST(TestGameplayFa�ade, TestUpgradeFishingAction) {
    int token_nb = 1;
    GameplayFa�ade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    f.executeUpgradeFishingAction(token_nb);
    EXPECT_TRUE(f.getFishingUpgradeStatus());
    EXPECT_EQ(f.getMaterials(), baseMaterials - rod_materials_required);
}


TEST(TestGameplayFa�ade, TestStormEvent) {
    GameplayFa�ade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    int fish_ref = f.getFishCount();
    int boat_HP_ref = f.getBoatHp();
    f.executeStormEvent();
    EXPECT_TRUE(f.getFishCount() < fish_ref);
    EXPECT_TRUE(f.getBoatHp() < boat_HP_ref);
}

TEST(TestGameplayFa�ade, TestWindEvent) {
    GameplayFa�ade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    f.moveBack(-100);
    f.executeWindEvent();
    EXPECT_TRUE(f.getDistanceTravelled() < 100);
}

TEST(TestGameplayFa�ade, TestSeagullEvent) {
    GameplayFa�ade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    int fish_ref = f.getFishCount();
    int player_HP_ref = f.getPlayerHp();
    f.executeSeagullEvent();
    EXPECT_TRUE(f.getFishCount() < fish_ref);
    EXPECT_TRUE(f.getPlayerHp() < player_HP_ref);
}

TEST(TestGameplayFa�ade, TestMaterialEvent) {
    GameplayFa�ade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    int material_ref = f.getMaterials();
    f.executeMaterialEvent();
    EXPECT_TRUE(f.getMaterials() > material_ref);
}

/*
Dans ce test, on va tester le fonctionnement de la m�thode nextday de la fa�ade.
On ex�cutera ici 2 actions, p�cher et naviguer.
*/
TEST(TestGameplayFa�ade, TestNextDay1) {
    std::map<TokensType, int> tokens;
    tokens[TokensType::fishingsTokens] = 2;
    tokens[TokensType::rowingTokens] = 3;
    GameplayFa�ade f(maxDay, maxDistance, playerBaseHp, playerBaseHp, boatBaseHp, boatBaseHp, baseMaterials);
    int mat_ref = f.getMaterials();
    auto s = f.nextDay(tokens);
    EXPECT_TRUE(f.getDistanceTravelled() >= 0);
    EXPECT_TRUE(f.getFishCount() >= 0);
    EXPECT_FALSE(f.getFishingUpgradeStatus());
    EXPECT_FALSE(f.getRowingUpgradeStatus());
    EXPECT_TRUE(f.getMaterials() >= mat_ref);
}

/*
Dans ce test, on va tester le fonctionnement de la m�thode nextday de la fa�ade.
On ex�cutera ici 4 actions : se soigner, r�parer, am�liorer le bateau et am�liorer la canne.
*/
TEST(TestGameplayFa�ade, TestNextDay2) {
    std::map<TokensType, int> tokens;
    tokens[TokensType::healingTokens] = 2;
    tokens[TokensType::repairTokens] = 1;
    tokens[TokensType::upgradeFishingToken] = 1;
    tokens[TokensType::upgradeRowingToken] = 1;
    GameplayFa�ade f(maxDay, maxDistance, playerBaseHp*0.5, playerBaseHp, boatBaseHp*0.5, boatBaseHp, baseMaterials*0.5);
    int mat_ref = f.getMaterials();
    auto s = f.nextDay(tokens);
    EXPECT_TRUE(f.getDistanceTravelled() >= 0);
    EXPECT_TRUE(f.getFishCount() >= 0);
    EXPECT_TRUE(f.getFishingUpgradeStatus());
    EXPECT_FALSE(f.getRowingUpgradeStatus());
    EXPECT_TRUE(f.getMaterials() < mat_ref);
    EXPECT_TRUE(f.getPlayerHp() <= playerBaseHp);
    EXPECT_TRUE(f.getBoatHp() <= boatBaseHp);
}




