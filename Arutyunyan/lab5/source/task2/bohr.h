#pragma once

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>


class BohrNode {
public:
    BohrNode() = default;
    BohrNode(std::weak_ptr<BohrNode> parent, char symbol_to_parent);

    void AddChild(char arc, std::shared_ptr<BohrNode> child);

    void AddOffset(int offset);
    const std::vector<int>& GetOffsets() const;

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
    static std::pair<std::shared_ptr<BohrNode>, std::vector<std::string>>
    BuildForestWithJoker(const std::string& pattern, char joker);

private:
    static void AppendPatternToForest(const std::string& sub_pattern, int pattern_index, int offset);

    static std::shared_ptr<BohrNode> root;

    char symbol_to_parent = -1;
    int pattern_index = -1;

    std::vector<int> offsets;
    std::weak_ptr<BohrNode> parent = std::weak_ptr<BohrNode>();
    std::weak_ptr<BohrNode> suffix_reference = std::weak_ptr<BohrNode>();
    std::weak_ptr<BohrNode> final_reference = std::weak_ptr<BohrNode>();

    std::unordered_map<char, std::shared_ptr<BohrNode>> children;
    std::unordered_map<char, std::weak_ptr<BohrNode>> go;
};