#include "task2.hpp"

void addString(Vertex* root, std::string string, int offset)
{
    Vertex* vertex = root;
    std::for_each(string.begin(), string.end(), [&vertex](char c)
        {
            if (!vertex->links[c])
            {
                vertex->links[c] = new Vertex;
            }
            vertex = vertex->links[c];
        });
    vertex->offsets.push_back(offset);
}

void addSuffLinks(Vertex* root)
{
    std::queue<Vertex*> vertexesQueue;

    root->suffixLink = root;
    std::for_each(root->links.begin(), root->links.end(), [&root, &vertexesQueue](auto link)
        {
            link.second->suffixLink = root;
            vertexesQueue.push(link.second);
        });

    while (!vertexesQueue.empty())
    {
        Vertex* current = vertexesQueue.front();
        vertexesQueue.pop();

        for (auto link : current->links)
        {
            char name = link.first;
            Vertex* child = link.second;
            Vertex* suffixLink = current->suffixLink;
            while (suffixLink != root && !suffixLink->links[name])
            {
                suffixLink = suffixLink->suffixLink;
            }
            if (suffixLink == root && !suffixLink->links[name])
            {
                child->suffixLink = suffixLink;
            }
            else
            {
                suffixLink = suffixLink->links[name];
                child->suffixLink = suffixLink;
            }
            vertexesQueue.push(child);
        }
    }
}

void input(std::istream& in, Vertex* root, std::string& Text, std::string& pattern, char& joker)
{
    in >> Text;
    in >> pattern;
    in >> joker;
}

Vertex* nextVertex(Vertex* vertex, Vertex* root, char symb)
{
    while (!vertex->links[symb] && vertex != root)
    {
        vertex = vertex->suffixLink;
    }
    if (vertex->links[symb])
    {
        vertex = vertex->links[symb];
    }
    return vertex;
}



Result findPos(Vertex* root, std::string Text, int count, int patternSize)
{
    Result result;
    std::vector<int> numberMatches(Text.size(), 0);
    Vertex* currentVert = root;
    for (int i = 0; i < Text.length(); i++)
    {
        char currentSymb = Text[i];
        currentVert = nextVertex(currentVert, root, currentSymb);

        Vertex* v = currentVert;
        while (v != root)//переходим по конечным ссылкам
        {
            if (!v->offsets.empty())
            {
                for (auto offset : v->offsets)
                {
                    if(i-offset >=0)
                        numberMatches[i - offset]++;
                }
            }
            v = v->suffixLink;
        }
    }
    for (int i = 0; i < numberMatches.size(); i++)
    {
        if (numberMatches[i] == count && i + patternSize <= numberMatches.size() )
        {
            result.push_back(i + 1);
        }
    }
    return result;
}

void addInstances(Vertex* root, std::string pattern, char joker, int& count)
{
    std::string instance;
    int offset = 0;
    for (auto c : pattern)
    {
        if (c == joker)
        {
            if (!instance.empty())
            {
                addString(root, instance, offset - 1);
                count++;
            }

            instance.clear();
        }
        else
        {
            instance.push_back(c);
        }
        offset++;
    }
    if (!instance.empty())
    {
        addString(root, instance, offset - 1);
        count++;
    }
}

