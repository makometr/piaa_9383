#pragma once

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>


class BohrNode : std::enable_shared_from_this<BohrNode> {
public:
    BohrNode() = default;
    BohrNode(std::weak_ptr<BohrNode> parent, char symbol_to_parent);

    void AddChild(char arc, std::shared_ptr<BohrNode> child);
    std::shared_ptr<BohrNode> GetChild(char arc);

    const std::shared_ptr<BohrNode>& GetChild(char arc) const;
    std::weak_ptr<BohrNode> MakeTransition(char arc);

    std::weak_ptr<BohrNode> GetSuffixReference();
    std::weak_ptr<BohrNode> GetFinalReference();

    bool HasChild(char arc) const;
    bool IsRoot() const;
    bool IsFinal() const;

    void SetPatternIndex(int pattern_index_);
    int PatternIndex() const;

    static std::shared_ptr<BohrNode> BuildForest(const std::vector<std::string>& patterns);

private:
    static std::shared_ptr<BohrNode> root;

    char symbol_to_parent = -1;
    int pattern_index = -1;

    std::weak_ptr<BohrNode> parent = std::weak_ptr<BohrNode>();
    std::weak_ptr<BohrNode> suffix_reference = std::weak_ptr<BohrNode>();
    std::weak_ptr<BohrNode> final_reference = std::weak_ptr<BohrNode>();

    std::unordered_map<char, std::shared_ptr<BohrNode>> children;
    std::unordered_map<char, std::weak_ptr<BohrNode>> go;
};