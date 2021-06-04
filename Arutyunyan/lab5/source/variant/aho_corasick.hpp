#include <string>
#include <vector>
#include <memory>
#include <set>

#include "bohr.h"


struct AhoPair {
    std::size_t start_index;
    std::size_t pattern_index;

    bool operator<(const AhoPair& other) const {
        return std::tie(start_index, pattern_index) < std::tie(other.start_index, other.pattern_index);
    }
};

static std::set<AhoPair> AhoCorasick(
    const std::shared_ptr<BohrNode>& root, const std::vector<std::string>& patterns,
    const std::string& text
) {
    std::set<AhoPair> result;
    std::weak_ptr<BohrNode> current = root;

    for (int i = 0; i < text.size(); ++i) {
        std::weak_ptr<BohrNode> next = current.lock()->GetChild(text[i]);

        while (!next.lock()) {
            if (current.lock()->IsRoot()) {
                next = current;
                break;
            }

            current = current.lock()->GetSuffixReference();
            next = current.lock()->GetChild(text[i]);
        }

        current = next;

        while (!next.lock()->IsRoot()) {
            if (next.lock()->IsFinal()) {
                result.insert(
                        {i - patterns[next.lock()->PatternIndex()].size() + 2,
                         static_cast<std::size_t>(next.lock()->PatternIndex()) + 1}
                );
            }
            next = next.lock()->GetSuffixReference();
        }
    }

    return result;
}