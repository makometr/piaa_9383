#include <iostream>
#include <algorithm>
#include <queue>

class AhoCorasick {
  struct Node {
    char symbol{};
    int patternId = -1;
    std::vector<int> offset;
    Node *suffixRef{};
    std::vector<Node *> childNodes;

    Node() = default;

    explicit Node(char newSymbol) : symbol(newSymbol) {}

    Node *getChildByChar(char c) {
      for (const auto &child: childNodes)
        if (child->symbol == c)
          return child;
      return nullptr;
    };
  };

 public:
  explicit AhoCorasick(std::istream &is) : m_root(new Node()) {
    m_root->suffixRef = m_root;

    std::string pattern;
    char joker;
    is >> pattern >> joker;
    patternSize = pattern.size();
    add_pattern_with_jokers(pattern, joker);
    makeRefs();
  };

  ~AhoCorasick() {
    std::queue<Node *> allocated;
    std::queue<Node *> row;
    row.push(m_root);
    allocated.push(m_root);
    while (!row.empty()) {
      std::queue<Node *> nextRow;
      while (!row.empty()) {
        for (auto &child: row.front()->childNodes)
          if (child != nullptr) {
            nextRow.push(child);
            allocated.push(child);
          }
        row.pop();
      }
      row = nextRow;
    }
    while (!allocated.empty()) {
      auto tmp = allocated.front();
      allocated.pop();
      delete tmp;
    }
  };

  void add_pattern_with_jokers(const std::string& str, const char joker) {
    std::string substr;
    int offset = 0;
    for (const auto& symbol: str) {
      if (symbol == joker) {
        if (!substr.empty())
          addPattern(substr, offset - 1);
        substr.clear();
      } else
        substr += symbol;
      offset++;
    }
    if (!substr.empty())
      addPattern(substr, offset - 1);
  };

  void addPattern(std::string &str, int offset) {
    Node *curNode = m_root, *child;
    for (const auto &c: str) {
      child = curNode->getChildByChar(c);
      if (child == nullptr) {
        child = new Node(c);
        curNode->childNodes.push_back(child);
      }
      curNode = child;
    }
    curNode->patternId = (int) m_patterns.size();
    curNode->offset.push_back(offset);
    m_patterns.push_back(str);
  };

  void makeRefs() {
    std::queue<Node *> queue;
    for (auto &child: m_root->childNodes) {
      child->suffixRef = m_root;
      queue.push(child);
    }
    while (!queue.empty()) {
      Node *curNode = queue.front();
      queue.pop();
      for (auto &child: curNode->childNodes) {
        bool suffixRefSet = false;
        Node *ref = curNode;
        while (ref != m_root) {
          ref = ref->suffixRef;
          Node *node = ref->getChildByChar(child->symbol);
          if (node != nullptr) {
            if (!suffixRefSet) {
              suffixRefSet = true;
              child->suffixRef = node;
            }
          }
        }
        if (!suffixRefSet) {
          child->suffixRef = m_root;
        }
        queue.push(child);
      }
    }
  };

  std::vector<int> search(const std::string &text) {
    std::vector<int> result;
    Node *curNode = m_root;
    std::vector<int> matches_amount(text.size());
    for (int i = 0; i < text.size(); i++) {
      Node *child = curNode->getChildByChar(text[i]);
      while (child == nullptr) {
        if (curNode == m_root) {
          child = m_root;
          break;
        }
        curNode = curNode->suffixRef;
        child = curNode->getChildByChar(text[i]);
      }
      curNode = child;
      while (child != m_root) {
        for (auto &off: child->offset)
          if (i - off >= 0)
            matches_amount[i - off]++;
        child = child->suffixRef;
      }
    }
    for (int i = 0; (size_t) i < matches_amount.size(); i++) {
      if (matches_amount[i] == (int) m_patterns.size()
          && i + patternSize <= (int) matches_amount.size()) {
        result.emplace_back(i + 1);
      }
    }
    return result;
  };

 private:
  Node *m_root;
  size_t patternSize;
  std::vector<std::string> m_patterns;
};

void print(std::vector<int>& arg, std::ostream& os) {
  for (auto x: arg)
    os << x << '\n';
}

int main() {
  std::string text;
  std::cin >> text;

  AhoCorasick algo(std::cin);
  auto result = algo.search(text);

  print(result, std::cout);
  return 0;
}
