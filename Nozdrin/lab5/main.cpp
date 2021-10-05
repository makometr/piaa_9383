#include <iostream>
#include <algorithm>
#include <queue>

class AhoCorasick {
  struct Node {
    char symbol{};
    int patternId = -1;
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
  AhoCorasick(int n, std::istream &is) : m_root(new Node()) {
    m_root->suffixRef = m_root;

    for (int i = 0; i < n; i++) {
      std::string pattern;
      is >> pattern;
      this->addPattern(pattern);
    }
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

  void addPattern(std::string &str) {
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
            if (node->patternId > 0) {
              break;
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

  std::vector<std::pair<int, int>> search(const std::string &text) {
    std::vector<std::pair<int, int>> result;
    Node *curNode = m_root;
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
        if (child->patternId >= 0)
          result.emplace_back(
              i - m_patterns[child->patternId].size() + 2,
              child->patternId + 1
          );
        child = child->suffixRef;
      }
    }
    std::sort(
        result.begin(),
        result.end(),
        [](std::pair<int, int> &a, std::pair<int, int> &b) {
          if (a.first != b.first) {
            return a.first < b.first;
          }
          return a.second < b.second;
        }
    );
    return result;
  };

 private:
  Node *m_root;
  std::vector<std::string> m_patterns;
};

void print(std::vector<std::pair<int, int>>& arg, std::ostream& os) {
  for (auto x: arg)
    os << x.first << ' ' << x.second << '\n';
}

int main() {
  int n;
  std::string text;
  std::cin >> text >> n;

  AhoCorasick algo(n, std::cin);
  auto result = algo.search(text);

  print(result, std::cout);
  return 0;
}
