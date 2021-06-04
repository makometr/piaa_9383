#include "bohr.h"
#include <cassert>

std::shared_ptr<BohrNode> BohrNode::root = std::make_shared<BohrNode>();


BohrNode::BohrNode(std::weak_ptr<BohrNode> parent, char symbol_to_parent)
    : parent(std::move(parent)), symbol_to_parent(symbol_to_parent)
{
}

void BohrNode::AddChild(char arc, std::shared_ptr<BohrNode> child) {
    children[arc] = std::move(child);
}

const std::vector<int>& BohrNode::GetOffsets() const {
    return offsets;
}

void BohrNode::AddOffset(int offset) {
    offsets.push_back(offset);
}

std::shared_ptr<BohrNode> BohrNode::GetChild(char arc) {
    return HasChild(arc) ? children.at(arc) : nullptr;
}

const std::shared_ptr<BohrNode>& BohrNode::GetChild(char arc) const {
    return children.at(arc);
}

std::weak_ptr<BohrNode> BohrNode::MakeTransition(char arc) {
    if (go.count(arc) == 0) {
        if (children.count(arc) != 0)
            go[arc] = children.at(arc);
        else if (IsRoot())
            go[arc] = root;
        else
            go[arc] = GetSuffixReference().lock()->MakeTransition(arc);
    }

    return go.at(arc);
}

std::weak_ptr<BohrNode> BohrNode::GetSuffixReference() {
    if (suffix_reference.lock() == nullptr) {
        if (IsRoot())
            suffix_reference = root;
        else if (parent.lock()->IsRoot())
            suffix_reference = parent;
        else
            suffix_reference = parent.lock()->GetSuffixReference().lock()->MakeTransition(symbol_to_parent);
    }

    return suffix_reference;
}

std::weak_ptr<BohrNode> BohrNode::GetFinalReference() {
    if (final_reference.lock() == nullptr) {
        if (GetSuffixReference().lock()->IsFinal())
            final_reference = GetSuffixReference();
        else if (GetSuffixReference().lock()->IsRoot())
            final_reference = GetSuffixReference();
        else
            final_reference = GetSuffixReference().lock()->GetFinalReference();
    }

    return final_reference;
}


bool BohrNode::HasChild(char arc) const {
    return children.count(arc) != 0;
}

bool BohrNode::IsRoot() const {
    return parent.lock() == nullptr;
}

bool BohrNode::IsFinal() const {
    return pattern_index >= 0;
}

void BohrNode::SetPatternIndex(int pattern_index_) {
    pattern_index = pattern_index_;
}

int BohrNode::PatternIndex() const {
    return pattern_index;
}


std::shared_ptr<BohrNode> BohrNode::BuildForest(
    const std::vector<std::string>& patterns
) {
    // assert(!root);

    for (int pattern_index = 0; pattern_index < patterns.size(); ++pattern_index) {
        auto current = root;
        const std::string& pattern = patterns[pattern_index];

        for (int i = 0; i < pattern.size(); ++i) {
            if (!current->HasChild(pattern[i]))
                current->AddChild(pattern[i], std::make_shared<BohrNode>(current, pattern[i]));
            current = current->GetChild(pattern[i]);
        }

        current->SetPatternIndex(pattern_index);
    }

    return root;
}

std::pair<std::shared_ptr<BohrNode>, std::vector<std::string>>
BohrNode::BuildForestWithJoker(
    const std::string& pattern, char joker
) {
    // assert(!root);

    std::vector<std::string> patterns;

    int start = 0;
    for (int i = 0; i < pattern.size(); ++i) {
        if (pattern[i] == joker) {
            auto sub_pattern = pattern.substr(start, i - start);

            if (!sub_pattern.empty()) {
                patterns.push_back(std::move(sub_pattern));
                AppendPatternToForest(patterns.back(), patterns.size() - 1, i - 1);
                start = i + 1;
            } else
                start++;
        }
    }

    if (start < pattern.size()) {
        patterns.push_back(pattern.substr(start, pattern.size() - start));
        AppendPatternToForest(patterns.back(), patterns.size() - 1, pattern.size() - 1);
    }

    return {root, patterns};
}

void BohrNode::AppendPatternToForest(
    const std::string& sub_pattern, int pattern_index, int offset
) {
    auto current = root;

    for (int i = 0; i < sub_pattern.size(); ++i) {
        if (!current->HasChild(sub_pattern[i]))
            current->AddChild(sub_pattern[i], std::make_shared<BohrNode>(current, sub_pattern[i]));
        current = current->GetChild(sub_pattern[i]);
    }

    current->SetPatternIndex(pattern_index);
    current->AddOffset(offset);
}

/*
 * ACTANCA
N$A
$
 */