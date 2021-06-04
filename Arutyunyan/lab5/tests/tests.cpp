#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../source/variant/bohr.h"
#include "../source/variant/aho_corasick.hpp"

#include <vector>
#include <string>
#include <iostream>


bool AutomatasAreEqual(
    const std::shared_ptr<BohrNode>& left, const std::shared_ptr<BohrNode>& right
) {
    if (left == nullptr && right == nullptr)
        return true;
    if (left == nullptr && right != nullptr || left != nullptr && right == nullptr)
        return false;
    
    if (left->GetChildren().size() != right->GetChildren().size())
        return false;
    for (const auto& [arc, child] : left->GetChildren()) {
        if (!right->HasChild(arc) || !AutomatasAreEqual(child, right->GetChild(arc)))
            return false;
    }

    return true;
}


TEST_CASE("Building bohr. Test 1") {
    std::vector<std::string> patterns = {
        "TAGT", "TAG", "T"
    };

    auto correct = std::make_shared<BohrNode>();
    correct->AddChild('T', std::make_shared<BohrNode>(correct, 'T'));

    auto t_child = correct->GetChild('T');
    t_child->AddChild('A', std::make_shared<BohrNode>(t_child, 'A'));

    auto a_child = t_child->GetChild('A');
    a_child->AddChild('G', std::make_shared<BohrNode>(a_child, 'G'));

    auto g_child = a_child->GetChild('G');
    g_child->AddChild('T', std::make_shared<BohrNode>(g_child, 'T'));

    auto bohr = BohrNode::BuildForest(patterns);
    REQUIRE(AutomatasAreEqual(correct, bohr));
}

TEST_CASE("Building bohr. Test 2") {
    std::vector<std::string> patterns = {
        "N", "NA", "NG", "NP", "K", "KN"
    };

    auto correct = std::make_shared<BohrNode>();
    correct->AddChild('N', std::make_shared<BohrNode>(correct, 'N'));
    correct->AddChild('K', std::make_shared<BohrNode>(correct, 'K'));

    auto n_child = correct->GetChild('N');
    n_child->AddChild('A', std::make_shared<BohrNode>(n_child, 'A'));
    n_child->AddChild('G', std::make_shared<BohrNode>(n_child, 'G'));
    n_child->AddChild('P', std::make_shared<BohrNode>(n_child, 'P'));

    auto k_child = correct->GetChild('K');
    k_child->AddChild('N', std::make_shared<BohrNode>(k_child, 'N'));


    auto bohr = BohrNode::BuildForest(patterns);
    REQUIRE(AutomatasAreEqual(correct, bohr));
}


TEST_CASE("Counting states. Test 1") {
    std::vector<std::string> patterns = {
        "TAGT", "TAG", "T"
    };

    auto bohr = BohrNode::BuildForest(patterns);
    REQUIRE((bohr->CountStates() == 4));
}

TEST_CASE("Counting states. Test 2") {
    std::vector<std::string> patterns = {
        "N", "NA", "NG", "NP", "K", "KN"
    };

    auto bohr = BohrNode::BuildForest(patterns);
    REQUIRE((bohr->CountStates() == 6));
}


TEST_CASE("Searching") {
    std::string text = "NTAG";
    std::vector<std::string> patterns = {
        "TAGT", "TAG", "T"
    };

    auto bohr = BohrNode::BuildForest(patterns);
    auto set_result = AhoCorasick(bohr, patterns, text);
    auto result = std::vector<AhoPair>{set_result.begin(), set_result.end()};

    REQUIRE((result[0].start_index == 2 && result[0].pattern_index == 2));
    REQUIRE((result[1].start_index == 2 && result[1].pattern_index == 3));
}