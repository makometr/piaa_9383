#include "task1.hpp"

void addString(Vertex* root, std::string string, int number)
{
    Vertex* vertex = root;
    int lvl = 1;
    std::for_each(string.begin(), string.end(), [&vertex, &lvl](char c)
        {
            if (!vertex->links[c])
            {
                vertex->links[c] = new Vertex;
            }
            vertex = vertex->links[c];
            vertex->level = lvl++;
        });
    vertex->terminal = number;
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

void input(std::istream& in, Vertex* root, std::string& Text)
{
    in >> Text;

    int quantity;
    in >> quantity;

    int number = 1;
    for (int i = 0; i < quantity; i++)
    {
        std::string currentString;
        in >> currentString;
        addString(root, currentString, number++);
    }
}

Vertex* nextVertex(Vertex*vertex,Vertex*root,char symb)
{
    while(!vertex->links[symb]&&vertex!=root)
    {
        vertex=vertex->suffixLink;
    }
    if(vertex->links[symb])
    {
        vertex=vertex->links[symb];
    }
    return vertex;
}



Result findPos(Vertex* root, std::string Text)
{
    Result result;
    Vertex* currentVert = root;
    for (int i = 0; i < Text.length(); i++)
    {
        char currentSymb = Text[i];
        currentVert = nextVertex(currentVert,root,currentSymb);

        Vertex *v = currentVert;
        while(v!=root)//переходим по конечным ссылкам
        {
            if(v->terminal!=0)
            {
                 result.push_back(std::pair<int, int>(i + 2 - v->level, v->terminal));
            }
            v=v->suffixLink;
        }
    }
    return result;
}