#include <iostream>
#include <vector>
#include <algorithm>

struct Vertex
{
    char symb;
    Vertex* suffLink = nullptr;
    Vertex* goodSuffLink = nullptr;
    Vertex* parent;
    std::vector<Vertex*> nextVertices;
    std::vector<std::pair<char, Vertex*>> autoMove;
    bool isWord = false;
    int pattern_num;

    Vertex(char symbV = '@', Vertex* parentV = nullptr)
    {
        this->symb = symbV;
        this->parent = parentV;
    }
};

int cmp(const void* a, const void* b)
{
    int a1 = (*(std::pair<int, int>*)a).first;
    int a2 = (*(std::pair<int, int>*)a).second;

    int b1 = (*(std::pair<int, int>*)b).first;
    int b2 = (*(std::pair<int, int>*)b).second;

    if(a1 == b1)
    {
        return a2 - b2;
    }
    else
    {
        return a1 - b1;
    }
}

void bohrIni(std::vector<Vertex*> &bohr)
{
    Vertex* v = new Vertex;
    bohr.push_back(v);
}

Vertex* findNextVertex(Vertex* &v, char c)
{
    for(int i = 0; i < v->nextVertices.size(); i++)
    {
        if(v->nextVertices[i]->symb == c)
        {
            return v->nextVertices[i];
        }
    }
    return nullptr;
}

void addNextVertex(Vertex* &v1, Vertex* v2)
{
    v1->nextVertices.push_back(v2);
}

int findInBohr(std::vector<Vertex*> &bohr, char c)
{
    for(int i = bohr.size() - 1; i >= 0; i--)
    {
        if(bohr[i]->symb == c)
        {
            return i;
        }
    }
    return -1;
}

void addStringToBohr(std::string &inputStr, std::vector<Vertex*> &bohr,  std::vector<std::string> &pattern)
{
    Vertex* currVertex = bohr[0];
    char ch;
    for(int i = 0; i < inputStr.length(); i++)
    {
        ch = inputStr[i];
        Vertex* nextVertex = findNextVertex(currVertex, ch);
        if(nextVertex == nullptr)
        {
            Vertex* v = new Vertex(ch, currVertex);
            bohr.push_back(v);
            addNextVertex(currVertex, v);
            currVertex = v;
        }
        else
        {
            currVertex = nextVertex;
        }
    }
    currVertex->isWord = true;
    pattern.push_back(inputStr);
    currVertex->pattern_num = pattern.size() - 1;
}

bool isStringInBohr(std::string &potentialStr, std::vector<Vertex*> &bohr)
{
    Vertex* currVertex = bohr[0];
    char ch;
    for(int i = 0; i < potentialStr.length(); i++)
    {
        ch = potentialStr[i];
        Vertex* nextVertex = findNextVertex(currVertex, ch);
        if(nextVertex == nullptr)
        {
            return false;
        }
        currVertex = nextVertex;
    }
    return true;
}

Vertex* getAutoMove(Vertex* v, char c);

Vertex* getSuffLink(Vertex* v)
{
    if(v->suffLink == nullptr)
    {
        if(v->parent == nullptr)
        {
            v->suffLink = v;
        }
        else if(v->parent->parent == nullptr)
        {
            v->suffLink = v->parent;
        }
        else
        {
            v->suffLink = getAutoMove(getSuffLink(v->parent), v->symb);
        }
    }
    return v->suffLink;
}

Vertex* findInAutoMove(Vertex* &v, char c)
{
    for(int i = 0; i < v->autoMove.size(); i++)
    {
        if(v->autoMove[i].first == c)
        {
            return v->autoMove[i].second;
        }
    }
    return nullptr;
}

void addToAutoMove(Vertex* v, char c, Vertex* nextVertex)
{
    v->autoMove.push_back(std::make_pair(c, nextVertex));
}

Vertex* getAutoMove(Vertex* v, char c)
{
    Vertex* nextAuto = findInAutoMove(v,c);
    if(nextAuto == nullptr)
    {
        Vertex* nextVertex = findNextVertex(v, c);
        if(nextVertex != nullptr)
        {
            addToAutoMove(v, c, nextVertex);
        }
        else
        {
            if(v->parent == nullptr)
            {
                addToAutoMove(v, c, v);
            }
            else
            {
                addToAutoMove(v, c, getAutoMove(getSuffLink(v), c));
            }
        }
    }
    return findInAutoMove(v, c);
}

Vertex* getGoodSuffLink(Vertex* v)
{
    if(v->goodSuffLink == nullptr)
    {
        Vertex* u = getSuffLink(v);
        if(u->parent == nullptr)
        {
            v->goodSuffLink = nullptr;
        }
        else if(u->isWord == true)
        {
            v->goodSuffLink = getSuffLink(u);
        }
    }
    return v->goodSuffLink;
}

void addToAnswer(std::vector <std::pair<int, int>> &output, int a, int b)
{
    output.push_back(std::make_pair(a,b));
}

void check(Vertex* v, int i, std::vector<std::string> &pattern, std::vector <std::pair<int, int>> &output)
{

    for(Vertex* u = v; u->parent != nullptr; u = getSuffLink(u))
    {
        if(u->isWord == true)
        {
            addToAnswer(output, i - pattern[u->pattern_num].length() + 1, u->pattern_num + 1);
        }
    }
}

std::vector <std::pair<int, int>> Aho_Corasick(std::string &inputStr, std::vector<Vertex*> &bohr, std::vector<std::string> &pattern)
{
    Vertex* u = bohr[0];
    std::vector <std::pair<int, int>> output;
    for(int i = 0; i < inputStr.length(); i++)
    {
        u = getAutoMove(u, inputStr[i]);
        check(u, i+1, pattern, output);
    }
    return output;
}

void printBohr(std::vector<Vertex*> &bohr)
{
    for(auto i : bohr)
    {
        std::cout<<i->symb<<": \n";
        for(int j = 0; j < i->nextVertices.size(); j++)
        {
            std::cout<<"    "<<i->nextVertices[j]->symb<<"("<<i->nextVertices[j]->parent->symb<<")\n";
        }
    }
}

int main()
{
    int n;
    std::vector <Vertex*> bohr;
    std::vector <std::string> pattern;
    std::vector <std::pair<int, int>> answer;
    std::string inputStr, s;
    bohrIni(bohr);

    std::cin>>inputStr>>n;

    for(int i = 0; i < n; i++)
    {
        std::cin>>s;
        addStringToBohr(s, bohr, pattern);
    }
    answer = Aho_Corasick(inputStr,bohr,pattern);

    std::qsort(&answer[0], answer.size(), sizeof(std::pair<int, int>), cmp);

    for(auto i : answer)
    {
        std::cout<<i.first<<" "<<i.second<<"\n";
    }



    for(int i = 0; i < bohr.size(); i++)
    {
        delete bohr[i];
    }

    return 0;
}


