#include <string>
#include <vector>
#include <memory>
#include <set>

#include "bohr.h"



static std::vector<int> AhoCorasick(
    const std::shared_ptr<BohrNode>& root, const std::vector<std::string>& patterns,
    int pattern_size, const std::string& text
) {
    std::vector<int> result;
    std::vector<int> matches(text.size());
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
            for (int offset : next.lock()->GetOffsets()) {
                if (i - offset >= 0)
                    matches[i - offset]++;
            }

            next = next.lock()->GetSuffixReference();
        }
    }

    for (int i = 0; i < matches.size(); ++i) {
        if (matches[i] == patterns.size() && i + pattern_size <= matches.size())
            result.push_back(i + 1);
    }

    return result;
}


/*
 * ACTANGA
TAN$A
$
 */