#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

struct BohrNode
{
    char symbol;
    std::vector<BohrNode *> next;
    BohrNode *suffixLink = nullptr;
    BohrNode *suffixLinkEnd = nullptr;
    BohrNode *parentNode = nullptr;
    int terminalNodeNumber;

    BohrNode(char newSymbol, BohrNode *parent)
    {
        symbol = newSymbol;
        terminalNodeNumber = -1;
        suffixLink = nullptr;
        suffixLinkEnd = nullptr;
        parentNode = parent;
    }

    ~BohrNode()
    {
        for (auto i = next.begin(); i != next.end(); i++)
            delete *i;
    }

    BohrNode *findNext(char nextSymbol)
    {
        for (auto i = next.begin(); i != next.end(); i++)
        {
            if (nextSymbol == (*i)->symbol)
            {
                return *i;
            }
        }
        return nullptr;
    }
};

BohrNode *buildBohr(std::vector<std::string> &stringArray)
{
    BohrNode *root = new BohrNode('.', nullptr); //символ стартовой вершины
    BohrNode *curNode;
    BohrNode *tmp = nullptr;
    for (int i = 0; i < stringArray.size(); i++)
    {
        curNode = root;
        for (int j = 0; j < stringArray[i].size(); j++)
        {
            tmp = curNode->findNext(stringArray[i][j]);
            if (tmp)
                curNode = tmp;
            else
            {
                curNode->next.push_back(new BohrNode(stringArray[i][j], curNode));
                curNode = curNode->next.back();
            }
        }
        curNode->terminalNodeNumber = i;
    }
    return root;
}

void addSinglePrefix(BohrNode *&node)
{
    BohrNode *tmp;
    if (node->symbol == '.')
    {
        node->suffixLink = node;
        return;
    }
    BohrNode *curNode = node->parentNode;
    if (curNode->symbol == '.')
    {
        node->suffixLink = curNode;
        return;
    }
    curNode = curNode->suffixLink;
    do
    {
        tmp = curNode->findNext(node->symbol);
        if (tmp)
        {
            node->suffixLink = tmp;
            while (tmp->terminalNodeNumber == -1)
            {
                if (tmp->symbol == '.')
                    return;
                tmp = tmp->suffixLink;
            }
            node->suffixLinkEnd = tmp;
            return;
        }
        curNode = curNode->suffixLink;
    } while (curNode->symbol != '.');
    node->suffixLink = curNode; //Сейчас curNode - корень
}

void addPrefixes(BohrNode *root)
{
    std::queue<BohrNode *> queue;
    BohrNode *curNode = root;
    for (auto i = curNode->next.begin(); i != curNode->next.end(); i++)
    {
        queue.push(*i);
    }
    curNode = queue.front();
    while (!queue.empty())
    {
        addSinglePrefix(curNode);
        queue.pop();
        for (auto i = curNode->next.begin(); i != curNode->next.end(); i++)
        {
            queue.push(*i);
        }
        curNode = queue.front();
    }
}

std::vector<std::string> readData()
{
    int N;
    std::vector<std::string> stringArray;
    std::cin >> N;
    stringArray.resize(N);
    for (int i = 0; i < N; i++)
        std::cin >> stringArray[i];
    return stringArray;
}

std::vector<std::pair<int, int>> AhoCorasick(BohrNode *root, std::string &text, std::vector<std::string> stringArray)
{
    BohrNode *curNode = root;
    BohrNode *tmp;
    std::vector<std::pair<int, int>> result;
    for (int i = 0; i < text.length(); i++)
    {
        tmp = curNode->findNext(text[i]);
        if (tmp)
        {
            curNode = tmp;
        }
        while (!tmp)
        {
            if (curNode->symbol == '.')
            {
                tmp = curNode;
                break;
            }
            curNode = curNode->suffixLink;
            tmp = curNode->findNext(text[i]);
            if (tmp)
            {
                curNode = tmp;
                break;
            }
        }
        if (curNode->terminalNodeNumber != -1)
        {
            result.push_back(std::make_pair<int, int>(i - stringArray[curNode->terminalNodeNumber].size() + 1, curNode->terminalNodeNumber + 1));
        }
        tmp = curNode->suffixLinkEnd;
        while (tmp)
        {
            result.push_back(std::make_pair<int, int>(i - stringArray[tmp->terminalNodeNumber].size() + 1, tmp->terminalNodeNumber + 1));
            tmp = tmp->suffixLinkEnd;
        }
    }
    return result;
}

bool pairCmp(std::pair<int, int> a, std::pair<int, int> b)
{
    if (a.first == b.first)
        return a.second < b.second;
    return a.first < b.first;
}

void printResult(std::vector<std::pair<int, int>> &result)
{
    sort(result.begin(), result.end(), pairCmp);
    for (auto i = result.begin(); i != result.end(); i++)
    {
        std::cout << i->first + 1 << ' ' << i->second << '\n';
    }
}

int main()
{
    std::string text;

    std::cin >> text;
    std::vector<std::string> stringArray = readData();
    BohrNode *root = buildBohr(stringArray);
    root->suffixLink = root;
    addPrefixes(root);
    std::vector<std::pair<int, int>> result = AhoCorasick(root, text, stringArray);
    printResult(result);
    return 0;
}