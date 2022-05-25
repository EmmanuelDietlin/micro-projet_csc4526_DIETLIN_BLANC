#include <gtest/gtest.h>
#include <string>
#include "Group.h"


TEST(TestReadXML, TestCircle) {
    std::string s = R"(<?xml version = "1.0"?>
		   <Circle id="0" label="testCircle" x="0" y="1" r="2" color="Black"/>)";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(s.c_str());
    ASSERT_TRUE(result) << result.description(); // Si jamais result est faux, indique que le test est faux *et* affiche la string result.description() (qui contient la raison de l'erreur)
    Circle c(doc.child("Circle"));
    Circle c_ref("testCircle", 0, 1, 2, "Black", 0);
    EXPECT_EQ(c, c_ref);
}

TEST(TestReadXML, TestGroup1) {
    std::string s = R"(<?xml version = "1.0"?>
        <Group id="0" label="testGroup" x="0" y="1">
        <Circle id="1" label="testCircle1" x="2" y="3" r="4" color="Black"/>
        <Circle id="2" label="testCircle2" x="5" y="6" r="7" color="Black"/>
        </Group>)";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(s.c_str());
    ASSERT_TRUE(result) << result.description(); // Si jamais result est faux, indique que le test est faux *et* affiche la string result.description() (qui contient la raison de l'erreur)
    //Circle* c1 = new Circle("testCircle1", 2, 3, 4, "Black");
    //Circle* c2 = new Circle("testCircle2", 5, 6, 7, "Black");
    
    std::vector<std::unique_ptr<Shape>> ptr;
    auto c1 = std::make_unique<Circle>("testCircle1", 2, 3, 4, "Black", 1);
    auto c2 = std::make_unique<Circle>("testCircle2", 5, 6, 7, "Black", 2);
    ptr.push_back(std::move(c1));
    ptr.push_back(std::move(c2));
    Group g_ref("testGroup", 0, 1, (ptr), 0);
    Group g(doc.child("Group"));
    ASSERT_EQ(g_ref, g);
}



TEST(TestReadXML, TestGroup2) {
    std::string s = R"(<?xml version = "1.0"?>
        <Group id="0" label="testGroup1" x="0" y="1">
        <Circle id="1" label="testCircle" x="2" y="3" r="4" color="Black"/>
        <Group id="2" label="testGroup2" x="5" y="6"/>
        </Group>)";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(s.c_str());
    ASSERT_TRUE(result) << result.description(); // Si jamais result est faux, indique que le test est faux *et* affiche la string result.description() (qui contient la raison de l'erreur)

    //Circle* c = new Circle("testCircle", 2, 3, 4, "Black");
    //Group* g2 = new Group("testGroup2", 5, 6, {});
    
    std::vector<std::unique_ptr<Shape>> ptr;
    std::vector<std::unique_ptr<Shape>> empty;

    //auto c = std::make_unique<Circle>("testCircle", 2, 3, 4, "Black");
    //auto g2 = std::make_unique<Group>("testGroup2", 5, 6, empty);

    ptr.push_back(std::make_unique<Circle>("testCircle", 2, 3, 4, "Black", 1));
    ptr.push_back(std::make_unique<Group>("testGroup2", 5, 6, (empty), 2));
    //ptr.push_back(std::make_unique<Group>("testGroup2", 5, 6, std::vector<std::unique_ptr<Shape>> {}));

    Group g_ref("testGroup1", 0, 1, (ptr), 0);
    Group g(doc.child("Group"));
    ASSERT_EQ(g_ref, g);
    
    ASSERT_TRUE(true);

}



TEST(TestAbsoluteCoord, Test1) {
    //Circle* c1 = new Circle("C21", 4, 5, 1, "Black");
    //Circle* c2 = new Circle("C22", 7, 8, 1, "Black");
    //Group* g2 = new Group("G2", 2, 3, { c1, c2 });
    
    std::vector<std::unique_ptr<Shape>> ptr;
    std::vector<std::unique_ptr<Shape>> shapes;

    auto c1 = std::make_unique<Circle>("C21", 4, 5, 1, "Black", 2);
    auto c2 = std::make_unique<Circle>("C22", 7, 8, 1, "Black", 3);

    shapes.push_back(std::move(c1));
    shapes.push_back(std::move(c2));

    auto g2 = std::make_unique<Group>("G2", 2, 3, (shapes), 1);
    ptr.push_back(std::move(g2));

    Group G1("G1", 0, 1, (ptr), 0);

    std::map<std::string, std::pair<int, int>> m;
    G1.computeAbsolute(0,0,m);

    std::map<std::string, std::pair<int, int>> m_ref = { {"G1",{0,1}}, {"G2",{2,4}}, {"C21",{6,9}}, {"C22",{9,12}} };
    ASSERT_EQ(m, m_ref);
}


