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
    std::vector<int> terminalNodeNumber; //будет хранить смещения текущей строки. А количество элементов массива - это кратность подстроки

    BohrNode(char newSymbol, BohrNode *parent)
    {
        symbol = newSymbol;
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

BohrNode *buildBohr(std::vector<std::pair<std::string, int>> &stringArray)
{
    BohrNode *root = new BohrNode('.', nullptr); //символ стартовой вершины
    BohrNode *curNode;
    BohrNode *tmp = nullptr;
    for (auto &current_string : stringArray)
    {
        curNode = root;
        for (int i = 0; i < current_string.first.size(); i++)
        {
            tmp = curNode->findNext(current_string.first[i]);
            if (tmp)
                curNode = tmp;
            else
            {
                tmp = new BohrNode(current_string.first[i], curNode);
                curNode->next.push_back(tmp);
            }
            if (i == current_string.first.size() - 1)
            {
                tmp->terminalNodeNumber.push_back(current_string.second);
            }
            else
            {
                curNode = tmp;
            }
        }
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
    tmp = curNode->findNext(node->symbol);
    while (!tmp)
    {
        if (curNode->symbol == '.')
        {
            tmp = curNode;
            break;
        }
        curNode = curNode->suffixLink;
        tmp = curNode->findNext(node->symbol);
    }
    node->suffixLink = tmp;
    BohrNode *tmp2 = tmp;
    while (tmp2->terminalNodeNumber.empty())
    {
        if (tmp2->symbol == '.')
            break;
        tmp2 = tmp2->suffixLink;
    }
    if (!tmp2->terminalNodeNumber.empty())
    {
        node->suffixLinkEnd = tmp2;
    }
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

std::vector<int> AhoCorasick(BohrNode *root, std::string &text, std::vector<std::pair<std::string, int>> &stringArray, int last_jokers)
{
    BohrNode *curNode = root;
    BohrNode *tmp;
    std::vector<int> result(text.size(), 0);
    for (int i = 0; i < text.length() - last_jokers; i++)
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
        if (!curNode->terminalNodeNumber.empty())
        {
            for (int j = 0; j < curNode->terminalNodeNumber.size(); j++)
            {
                if (i - curNode->terminalNodeNumber[j] + 1 >= 0)
                    result[i - curNode->terminalNodeNumber[j] + 1]++;
            }

            //result.push_back(std::make_pair<int, int>(i - stringArray[curNode->terminalNodeNumber].size() + 1, curNode->terminalNodeNumber + 1));
        }
        BohrNode *tmp2 = curNode->suffixLinkEnd;
        while (tmp2)
        {
            for (int j = 0; j < tmp2->terminalNodeNumber.size(); j++)
            {
                if (i - tmp2->terminalNodeNumber[j] + 1 >= 0)
                    result[i - tmp2->terminalNodeNumber[j] + 1]++;
            }
            // result.push_back(std::make_pair<int, int>(i - stringArray[tmp->terminalNodeNumber].size() + 1, tmp->terminalNodeNumber + 1));
            tmp2 = tmp2->suffixLinkEnd;
        }
        curNode = tmp;
    }
    return result;
}

void printResult(std::vector<int> &result, int length, int wordsNumber)
{
    int resultL = result.size();
    for (int i = 0; i < resultL; i++)
    {
        if (result[i] == wordsNumber)
            std::cout << i + 1 << '\n';
    }
}

int main()
{
    std::string text;
    char separator;
    std::string stringWithJoker;
    std::vector<std::pair<std::string, int>> stringArray;
    std::cin >> text >> stringWithJoker >> separator;
    std::string pattern_separation;
    int last_jokers;
    for (int i = 0; i < stringWithJoker.size(); i++)
    {
        if (stringWithJoker[i] != separator)
        {
            pattern_separation += stringWithJoker[i];
            last_jokers = 0;
        }
        else
        {
            if (!pattern_separation.empty())
            {
                stringArray.emplace_back(pattern_separation, i);
            }
            pattern_separation = "";
            last_jokers++;
        }
    }
    if (!pattern_separation.empty())
    {
        stringArray.emplace_back(pattern_separation, stringWithJoker.size());
    }
    BohrNode *root = buildBohr(stringArray);
    root->suffixLink = root;
    addPrefixes(root);
    std::vector<int> result = AhoCorasick(root, text, stringArray, last_jokers);
    printResult(result, stringWithJoker.length(), stringArray.size());
    delete root;
    return 0;
}