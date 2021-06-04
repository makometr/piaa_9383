#include "bohr.h"

std::shared_ptr<BohrNode> BohrNode::root = std::make_shared<BohrNode>();

BohrNode::BohrNode(std::weak_ptr<BohrNode> parent, char symbol_to_parent)
    : parent(std::move(parent)), symbol_to_parent(symbol_to_parent)
{
}

std::size_t BohrNode::CountStates() const {
    std::size_t result = children.size();
    for (const auto& record : children)
        result += record.second->CountStates();
    return result;
}

void BohrNode::AddChild(char arc, std::shared_ptr<BohrNode> child) {
    children[arc] = std::move(child);
}

std::shared_ptr<BohrNode> BohrNode::GetChild(char arc) {
    return HasChild(arc) ? children.at(arc) : nullptr;
}

const std::shared_ptr<BohrNode>& BohrNode::GetChild(char arc) const {
    return children.at(arc);
}

const std::unordered_map<char, std::shared_ptr<BohrNode>>&
BohrNode::GetChildren() const {
    return children;
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
    root = std::make_shared<BohrNode>();

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